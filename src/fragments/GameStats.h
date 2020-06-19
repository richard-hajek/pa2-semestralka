#ifndef PROGTEST_PROJECT_STATUS_H
#define PROGTEST_PROJECT_STATUS_H

#include "Fragment.h"

/**
 * Provide an overhead overview of a current game
 */
class GameStats final : public Fragment{
public:

    /**
     * Construct a new GameStats
     */
    explicit GameStats(Game * game) : Fragment(game){}
    
    /**
     * Does nothing in this particoular System
     * @return true if success
     */
    bool Setup(TSVReader & reader) final;

    /**
     * Sets the preffered diensions of the overview
     * @param width Width of the overview
     * @param height Height of the overview
     */
    void RequestDimensions(int & width, int & height) final;

    /**
     * Loads a saved game from a reader
     * @param reader TSVReader on a start of the file
     */
    bool Load(TSVReader & reader) final;

    /**
     * Save this stats data to TSVWriter
     * @param writer Writer to write to
     * @return true on success
     */
    bool Save(TSVWriter & writer) final;


    /**
     * Render the overview
     */
    void Render() final;

    /**
     * Does nothing
     */
    ~GameStats() final;

    /**
     * Change health
     * @param i the amount to decrease the health by
     */
    void Hurt(int i);

public:

    /// Current health, game will stop when Health <= 0
    int Health = 100;

    /// Current money, is used for currency
    int Money = 200;

    /// Current score
    int Score = 0;

    /// When set, the game will stop
    bool GameOver = false;
};


#endif //PROGTEST_PROJECT_STATUS_H
