#ifndef SEMESTER_PROJECT_TERRAIN_H
#define SEMESTER_PROJECT_TERRAIN_H

#include <string>
#include <vector>
#include "../units/Tile.h"
#include "Fragment.h"

/**
 * Implements map's terrain
 */
class Terrain final : public Fragment {
public:

    /**
     * Construct this Terrain
     * @param game Parent game
     */
    explicit Terrain(Game * game) : Fragment(game){}

    /**
     * Read Tower definitions from a setup file
     * @param reader reading from the setup file
     * @return true on success
     */
    bool Setup(TSVReader & reader) final;
    
    /**
     * Request map's size of dimensions for the screen
     * @param width selected map's width
     * @param height selected map's height
     */
    void RequestDimensions(int & width, int & height) final;

    /**
     * Share Terrain's WINDOW with other Fragments
     * @return Terrain's WINDOW
     */
    WINDOW * ShareWindow() final;

    /**
     * Load a saved terrain from a reader
     * @param reader reader of save file
     * @return true on success
     */
    bool Load(TSVReader & reader) final;

    /**
     * Save map name to TSVWriter
     * @param writer Writer to write to
     * @return true on success
     */
    bool Save(TSVWriter & writer) final;


    /**
     * Render current terrain
     */
    void Render() final;
    
    /**
     * Free resources
     */
    ~Terrain() final;
    
    /**
     * Choose a map from mapPool
     * @mapName Map to choose
     * @return true on success (true if map exists)
     */
    bool SetActiveMap(const std::string& mapName);

    /**
     * Find a Tile in a row in a column
     * Safe, will return nullptr on bad coordinates
     * @param row row of the Tile
     * @param column column of the Tile
     * @return nullptr if the Tile doesn't exist, a pointer to the Tile otherwise
     */
    Tile * GetTile(int row, int column) const;

    /**
     * @return current terrain's number of rows
     */
    int GetMapHeight() const;

    /**
     * @return current terrain's number of columns
     */
    int GetMapWidth() const;

private:
    
    /// Currently played terrain name
    std::string _terrainName;
    
    /// Current played terrain data
    std::vector<std::vector<Tile *>> _terrain;
    
    /// All terrains from setup file
    std::vector<std::pair<std::string, std::vector<std::string>>> _terrainPool;

};

#endif //SEMESTER_PROJECT_TERRAIN_H
