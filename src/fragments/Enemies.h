#ifndef SEMESTER_PROJECT_ENEMIES_H
#define SEMESTER_PROJECT_ENEMIES_H

#include <vector>
#include <chrono>
#include "Fragment.h"

class Enemy;
class EnemyTemplate;

#define PATH_VARIATIONS 5

/**
 * Makes Enemies move and die
 */
class Enemies final : public Fragment {
public:
    
    /**
     * Construct Enemies
     */
    explicit Enemies(Game * game);
    
    /**
     * Expects a reader ready to reader enemy definitions
     * Will read a definitions of enemies from this reader
     * @param reader Reader to read enemy definitions from
     * @return true on success
     */
    bool Setup(TSVReader & reader) final;

    /**
     * Find enemy spawn point and goal
     * Generate paths
     */
    void Ready() final;

    /**
     * Expects a reader ready to read enemy positions and IDs
     * Loads enemies from reader
     * @param reader Reader to read from
     * @return true on success
     */
    bool Load(TSVReader & reader) final;

    /**
     * Save this Enemy data to TSVWriter
     * @param writer Writer to write to
     * @return true on success
     */
    bool Save(TSVWriter & writer) final;

    /**
     * Draw enemies on screen
     */
    void Render() final;

    /**
     * Update all enemies
     */
    void Update(double delta) final;

    /**
     * Clear memory, etc...
     */
    ~Enemies() final;

    /**
     * Select and return a variation of a Enemy path
     * @param variationSeed Any number, will be used to select a path
     * @return A path variation
     */
    std::vector<std::pair<int, int>> const & GetPath(int variationSeed) const;

    /**
     * Return all enemies around a certian point in a certain radius
     * @param x the x-coordinate of the point
     * @param y the y-coordinate of the point
     * @param range the radius of the search
     */
    std::vector<Enemy *> GetEnemiesAround(int x, int y, int range);

    /**
     * Prepare a new set of paths
     */
    void RegeneratePaths();

    /**
     * Spawn enemy
     * @param maxId maximum enemy id to spawn
     */
     void SpawnEnemy(int maxId);

     /**
      * Count how many alive enemies are on the screen
      * @return number of live enemies
      */
     int EnemyCount();

      /**
       * Return all available enemy data
       */
      std::vector<EnemyTemplate *> GetAvailableEnemies() const;

      /**
        * DEBUG
        * Wipe all enemies
        */
      void DebugWipeEnemies();

private:

    /// All enemy definitions
    std::vector<EnemyTemplate *> _enemyData;

    /// All currently alive enemies
    std::vector<Enemy *> _enemies;

    /// Path variations for enemies
    std::vector<std::vector<std::pair<int, int>>> _pathVariations;

    /// Cached enemy spawn point
    std::pair<int, int> _spawnPoint;

    /// Cached enemy goal
    std::pair<int, int> _goal;
};

#endif //SEMESTER_PROJECT_ENEMIES_H
