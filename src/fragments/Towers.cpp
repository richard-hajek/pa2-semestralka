#include "../units/Tower.h"
#include "../Game.h"
#include "Display.h"
#include "Towers.h"
#include "Terrain.h"
#include "GameStats.h"
#include "../utils/TSVReader.h"
#include "../utils/TSVWriter.h"
#include "../units/Enemy.h"

Towers::Towers(Game *game) : Fragment(game) {

}

bool Towers::Setup(TSVReader &reader) {

    if (reader.NextString() != "TOWERS")
        return false;

    int towerCount = reader.NextInt();
    for(int i = 0; i < towerCount; i++){

        if (reader.NextString() != "TOWER")
            return false;

        _towerData.push_back(new TowerTemplate(reader));
    }

    return true;
}

bool Towers::Save(TSVWriter &writer) {

    writer.Write((int)_towers.size());
    writer.Next();
    for(auto tower : _towers){
        writer.Write("TOWER");
        writer.Write(tower->GetID());
        writer.Write(tower->GetX());
        writer.Write(tower->GetY());
        writer.Next();
    }

    return writer.Good();
}

bool Towers::Load(TSVReader &reader) {

    int count = reader.NextInt();

    for (int i = 0; i < count; i++) {

        if (reader.NextString() != "TOWER")
            return false;

        int id = reader.NextInt();
        int x = (int)reader.NextDouble();
        int y = (int)reader.NextDouble();
        _towers.push_back(new Tower((int)x, (int)y, _towerData[id]));
        m_Game->GetTerrain()->GetTile(y, x)->Obstruct();
    }

    return true;
}

void Towers::Update(double delta) {
    for (Tower * tower : _towers){
        Enemy * target = nullptr;
        int damage = 0;
        tower->UpdateAttack(*m_Game->GetEnemies(), delta, target, damage);

        if ( target ){
            m_Game->GetStats()->Score += damage;
            m_Game->GetStats()->Money += damage;
        }
    }
}


void Towers::Render() {
    WINDOW * win = m_Game->GetTerrain()->ShareWindow();
    for(const Tower * tower : _towers){

        bool shooting = (tower->GetEffects() & 1u) == 1u;

        wattron(win, shooting ? A_BOLD : Display::GetTowerColor(tower->GetID(), tower->GetVariation()));

        mvwaddch(win, tower->GetY(), tower->GetX(), tower->GetChar());

        wattroff(win, shooting ? A_BOLD : Display::GetTowerColor(tower->GetID(), tower->GetVariation()));
    }

    wattroff(win, COLOR_PAIR(1u));

    wnoutrefresh(win);
}

Towers::~Towers() {

}

bool Towers::BuildTower(int x, int y, char key) {
    TowerTemplate * data = nullptr;

    for (auto towerData : _towerData){
        if (towerData->Key == key){
            data = towerData;
            break;
        }
    }

    if (data == nullptr)
        return false;

    if (m_Game->GetStats()->Money < data->Price)
        return false;

    m_Game->GetStats()->Money -= data->Price;
    _towers.push_back(new Tower(x, y, data));
    return true;
}

std::vector<TowerTemplate *> Towers::GetAvailableTowers() const {
    return _towerData;
}
