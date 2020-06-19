#include "Terrain.h"
#include "Display.h"
#include "../utils/TSVReader.h"
#include "../utils/TSVWriter.h"
#include <ncurses.h>

bool Terrain::Setup(TSVReader &reader) {
    if (reader.NextString() != "MAPS")
        return false;

    int maps = reader.NextInt();

    for (int i = 0; i < maps; i++){
        if (reader.NextString() != "MAP")
            return false;
        std::string name = reader.NextString();
        reader.NextInt(); // Skip width
        int height = reader.NextInt();
        auto lines = reader.NextLines(height + 1);
        lines.erase(lines.begin());
        _terrainPool.emplace_back(name, lines);
    }

    return true;
}

bool Terrain::SetActiveMap(const std::string& mapName) {

    std::vector<std::string> terrain;
    for (const auto& tuple : _terrainPool){
        if (mapName == tuple.first) {
            _terrainName = tuple.first;
            terrain = tuple.second;
            break;
        }
    }

    if (mapName != _terrainName) {
        return false;
    }

    _terrainName = mapName;

    for (size_t row = 0; row < terrain.size(); row++){
        std::vector<Tile *> tileRow;
        tileRow.resize(terrain[row].size());
        for (size_t tile = 0; tile < terrain[row].size(); tile++){
            tileRow[tile] = new Tile(tile, row, terrain[row][tile]);
        }
        _terrain.push_back(tileRow);
    }

    return true;
}

bool Terrain::Save(TSVWriter &writer) {
    writer.Write("TERRAIN");
    writer.Write(_terrainName);
    writer.Next();
    return true;
}

bool Terrain::Load(TSVReader &reader) {

    if (reader.NextString() != "TERRAIN"){
        return false;
    }

    return SetActiveMap(reader.NextString());
}

void Terrain::RequestDimensions(int &width, int &height) {
    width = _terrain[0].size();
    height = _terrain.size();
}

WINDOW *Terrain::ShareWindow() {
    return m_Window;
}

void Terrain::Render() {

    wmove(m_Window, 0, 0);
    for(const auto& row : _terrain){
        for (const auto * tile : row){

            if (tile->GetChar() == '.')
                wattron(m_Window, Display::GetPathColor());

            if (tile->GetChar() == '#')
                wattron(m_Window, Display::GetWallColor());

            waddch(m_Window, tile->GetChar());

            if (tile->GetChar() == '#')
                wattroff(m_Window,Display::GetWallColor());

            if (tile->GetChar() == '.')
                wattroff(m_Window,Display::GetPathColor());
        }
    }

    wnoutrefresh(m_Window);
}

Tile *Terrain::GetTile(int row, int column) const {
    if (row < 0 || column < 0)
        return nullptr;
    if ((size_t)row >= _terrain.size() || (size_t)column >= _terrain[row].size())
        return nullptr;
    return _terrain[row][column];
}

int Terrain::GetMapHeight() const {
    return _terrain.size();
}

int Terrain::GetMapWidth() const {
    return _terrain.empty() ? 0 : _terrain[0].size();
}


Terrain::~Terrain() {
    for(const auto& row : _terrain){
        for(auto tile : row){
            delete tile;
        }
    }
}
