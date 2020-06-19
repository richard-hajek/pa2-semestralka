#ifndef SEMESTER_PROJECT_PLAYER_H
#define SEMESTER_PROJECT_PLAYER_H

#include "Fragment.h"

/**
 * This class shall implement a method of controlling the game
 */
class Player final : public Fragment {
public:
    
    /**
     * Construct this System
     */
    explicit Player(Game * game);

    /**
     * Render a Player's cursor
     */
    void Render() final;

    /**
     * Dispose of resources
     */
    ~Player() final;
    
    /**
     * Process user input
     * @param c Key the user pressed
     */
    void OnInput(int c);
private:

    /// Cursor location
    int _cursorX = 0;
    /// Cursor location 
    int _cursorY = 0;
};

#endif //SEMESTER_PROJECT_PLAYER_H
