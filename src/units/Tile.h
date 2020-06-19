#ifndef PROGTEST_PROJECT_TILE_H
#define PROGTEST_PROJECT_TILE_H

#include "Drawable.h"

/**
 * Basic tile, goes on the map
 */
class Tile : public Drawable
{
public:
    /**
     * Must be constructed with initial coordinates and symbol to draw on the map
     */
    Tile(int x, int y, char c);

    /**
     * Use this to get Tile's chracter
     * @return Symbol to draw
     */
    char GetChar() const final;

    /**
     * Use this method if program needs to know if Tile can be walked upon by enemies
     * @return true if walkable
     */
    bool GetWalkable();

    /**
     * Use this method to make tile unwalkable
     */
    void Obstruct();

    /**
     * Returns true if this tile is buildable upon
     * @return true if buildable
     */
    bool GetBuildable();
protected:
    /// Symbol to draw on the map
    char m_Symbol;

    /// Whether the Tile can be walked upon
    bool m_Walkable;

    /// Whether the Tile can be build upon
    bool m_Buildable;
};

#endif //PROGTEST_PROJECT_TILE_H
