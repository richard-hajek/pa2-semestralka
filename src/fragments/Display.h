#ifndef SEMESTER_PROJECT_DISPLAY_H
#define SEMESTER_PROJECT_DISPLAY_H

#include "Fragment.h"

/**
 * Prepares terminal display
 */
class Display final : public Fragment {
public:
    
    /**
     * Construct a new Display system
     */
    explicit Display(Game * game) : Fragment(game){};
    
    /**
     * Prepares terminal for drawing
     * @return true if success
     */
    bool Setup(TSVReader & reader) final;

    /**
     * Just calls PrepareWindows
     */
    void Ready() final;

    /**
     * Call doupdate on ncurses
     */
     void Render() final;

    /**
     * Reset terminal back to normal
     */
    ~Display() final;
    
    /**
     * Calls RequestDimensions on all of Game's fragments,
     * creates new WINDOWs if RequestDimensions sets x, y != 0,0
     * and passes new WINDOW to the fragments
     */
    void PrepareWindows();

    /**
     * Return a color based on enemy type and enemy variation
     * Both variables should be the same for the same enemy
     * @param base type of the enemy
     * @param variation the variation of the enemy
     * @return the color code of the enemy
     */
    static int GetEnemyColor(int base, int variation);

    /**
     * Return a color based on tower type and tower variation
     * Both variables should be the same for the same tower
     * @param base type of the tower
     * @param variation the variation of the tower
     * @return the color code of the tower
     */
    static int GetTowerColor(int base, int variation);

    /**
     * @return color code of wall tile
     */
    static int GetWallColor();

    /**
     * @return color code of path tile
     */
    static int GetPathColor();
};

#endif //SEMESTER_PROJECT_DISPLAY_H
