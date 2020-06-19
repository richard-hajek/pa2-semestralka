#ifndef PROGTEST_PROJECT_TOWER_H
#define PROGTEST_PROJECT_TOWER_H

#include <string>
#include <utility>
#include "Tile.h"
#include "Enemy.h"

class Enemies;
class TSVReader;
class Game;

/**
 * A template structure for towers
 */
struct TowerTemplate{
    int ID;
    char Symbol;
    char Key;
    std::string Name;
    int Price;
    int Damage;
    int Range;
    explicit TowerTemplate(TSVReader & reader);

    std::string Describe() const;
};

/**
 * Single tower unit
 */
class Tower : public Drawable{
public:
    
    /**
     * Construct a new Tower using coordinates and properties structure
     */
    Tower(int x, int y, const TowerTemplate * source);

    /**
     * Ask tower if it wants to attack anything
     */
    void UpdateAttack(Enemies &enemies, double delta, Enemy *&pEnemy, int & i);
    
    /**
     * @return Tower's character to draw
     */
    char GetChar() const override;

    /**
     * @return 8-bit word representing the current effects
     */
    uint8_t GetEffects() const;

    /**
     * @return this tower's type's ID
     */
    int GetID() const;

    /**
     * @return this tower's unique and constant variation
     */
    int GetVariation() const;

private:
    ///Source of properties of this Tower
    TowerTemplate const * const _source;

    /// Time in between shots
    double m_Cooldown = 0;

    /// Effect mask
    uint8_t m_Effects = 0;

    /// Variation
    int m_Variation;
};


#endif //PROGTEST_PROJECT_TOWER_H
