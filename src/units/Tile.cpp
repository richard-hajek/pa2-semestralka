#include "Tile.h"

Tile::Tile(int x, int y, char c) : Drawable(x, y), m_Symbol(c) {
    m_Walkable = c == ' ' || c == '.';
    m_Buildable = c == ' ';
}

char Tile::GetChar() const {
    return m_Symbol;
}

bool Tile::GetWalkable() {
    return m_Walkable;
}

void Tile::Obstruct() {
    m_Walkable = false;
    m_Buildable = false;
}

bool Tile::GetBuildable() {
    return m_Buildable;
}
