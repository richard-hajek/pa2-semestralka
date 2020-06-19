#ifndef SEMESTER_PROJECT_FRAGMENT_H
#define SEMESTER_PROJECT_FRAGMENT_H

#include <ncurses.h>

class Game;
class TSVReader;
class TSVWriter;

/***
 * Provides abstract interface for individual game mechanics
 */
class Fragment {

public:

    /**
     * Does little more than set the reference to the game
     * @param game Reference to the parent game
     */
    explicit Fragment(Game * game) : m_Game(game){}

    /**
     * Read from data from setup file
     * @param reader of SETUP.tsv file
     * @return file read successfully
     */
    virtual bool Setup(TSVReader & reader)  { return true; };

    /**
     * Fragments that require a WINDOW request it here
     * @param width will be set
     * @param height will be set
     */
    virtual void RequestDimensions(int & width, int & height) { };

    /**
     * This method will load data from a save
     * @param reader of SAVE.tsv file
     * @return file read successfully
     */
    virtual bool Load(TSVReader & reader) { return true; }

    /**
     * This methods saves this fragment's data to a writer
     * @param writer of SAVE.tsv file
     * @return data saved successfully
     */
     virtual bool Save(TSVWriter & writer) {return true;}

    /**
     * Gets called before Render and Update
     */
    virtual void Ready() { }

    /**
     * Draw fragment on screen
     */
    virtual void Render() { };

    /**
     * Perform update
     * @param delta Second passed since last update
     */
    virtual void Update(double delta) { }

    /// Destroy fragment
    virtual ~Fragment() = default;
    
    /**
     * Set System's window to use
     * @param window Newly created window for this System
     */
    void SetWindow(WINDOW * window){
        m_Window = window;
    }
    
    /**
     * Fragments may share their drawing space, if they do,
     * they will share it here
     * @return System's m_Window or nullptr
     */
    virtual WINDOW * ShareWindow(){
        return nullptr;
    }

protected:
    /// Pointer to parent Game
    Game * m_Game;
    /// Pointer to System's WINDOW
    WINDOW * m_Window;
    /// A "screen changed" flag, subsystem shall only redraw if this is true
    bool m_Redraw = true;
};


#endif //SEMESTER_PROJECT_FRAGMENT_H
