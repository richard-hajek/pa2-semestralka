#ifndef SEMESTER_PROJECT_TOWERS_H
#define SEMESTER_PROJECT_TOWERS_H

#include "Fragment.h"
#include <vector>
#include <string>

class TowerTemplate;
class Tower;

/**
 * Prepare and update towers system
 */
class Towers final : public Fragment {
public:

    /**
     * Construct this system
     * @param game Parent game
     */
    explicit Towers(Game * game);

    /**
     * Load definitions of towers from setup file
     * @param reader reader of the setup file, ready to read tower definitions
     * @return true on success
     */
    bool Setup(TSVReader & reader) final;

    /**
     * Load towers' positions and ids from a save file
     * @param reader reader of the save file, ready to read saved towers
     * @return true on success
     */
    bool Load(TSVReader & reader) final;

    /**
     * Save tower data to TSVWriter
     * @param writer Writer to write to
     * @return true on success
     */
    bool Save(TSVWriter & writer) final;

    /**
     * Update & shoot all towers
     */
    void Update(double delta) final;

    /**
     * Render all towers
     */
    void Render() final;

    /**
     * Free resources
     */
    ~Towers() final;
    
    /**
     * Build a tower
     * @param x Column coordinate to build it on
     * @param y Row coordinate to build it on
     * @param key A key pressed by the user that identifies the tower
     * @return true on success (key exists)
     */
    bool BuildTower(int x, int y, char key);

    /**
     * Return all available data sources
     */
     std::vector<TowerTemplate *> GetAvailableTowers() const;

private:

    /// All tower definitions
    std::vector<TowerTemplate *> _towerData;
    
    /// All current towers
    std::vector<Tower *> _towers;

    /// Currently loaded map
    std::string _terrainName;
};

#endif //SEMESTER_PROJECT_TOWERS_H
