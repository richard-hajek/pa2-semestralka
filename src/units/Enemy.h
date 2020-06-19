#ifndef PROGTEST_PROJECT_ENEMY_H
#define PROGTEST_PROJECT_ENEMY_H

#include <string>
#include "Drawable.h"
#include "../fragments/Enemies.h"

class TSVReader;
class Terrain;

/**
 * A template structure for enemies
 */
struct EnemyTemplate{

    /// Unique ID of the enemy type
    int ID;

    /// Name of the enemy type
    std::string Name;

    /// Symbol that represent the enemy on the map
    char Char;

    /// Starting HP of the enemy
    int HP;

    /// How many tiles per second the enemy moves
    int Speed;

    /**
     * Fill this EnemyTemplate with whatever is next in this reader
     */
    explicit EnemyTemplate(TSVReader & reader);

    /**
     * Return a text description of this enemy type
     */
    std::string Describe() const;
};

/**
 * Single enemy unit
 */
class Enemy final : public Drawable{
public:
    
    /**
     * Create a new Enemy based on x,y and template
     * @param x Initial x coordinate
     * @param y Initial y coordinate
     * @param source Template for this enemy
     */
    Enemy(int x, int y, const EnemyTemplate & source);

    /**
     * Alternate constructor for loading saved game
     * @param x Current x coordinate
     * @param y Current y coordinate
     * @param hp Current HP
     * @param source Template for this enemy
     */
    Enemy(int x, int y, int hp, const EnemyTemplate & source);

    /**
     * Update and move this enemy
     * @param Terrain Current terrain of the current map
     * @delta Amount of seconds since the last update
     */
    void UpdateMove(const Enemies &enemies, double delta, bool & reachedEnd);

    /**
     * Decrease Enemy's health, report how much it was decreased
     */
    void OnAttacked(int damage, int & dealt);

    /**
     * @return Whether Enemy is dead
     */
    bool IsDead() const;

    /**
     * @return Enemy's symbol to draw on map
     */
    char GetChar() const final;

    /**
     * @return Current HP
     */
    int GetHP() const;

    /**
     * Set current HP to 0
     */
    void Kill();

    /**
     * Tidy any data left over
     */
    ~Enemy() final;

    /**
     * Get enemy ID
     */
    int GetID() const;

    /**
     * Return random number associated with this enemy
     */
    int GetVariation() const;

private:
    /// Source of properties of this Enemy
    EnemyTemplate const * const _source;
    /// Current HP
    int _hp;
    /// Which path variation this enemy takes
    int _variation;
    /// Remember this enemy's path location
    double _pathProgress;
};

#endif //PROGTEST_PROJECT_ENEMY_H
