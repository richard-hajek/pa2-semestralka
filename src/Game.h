#ifndef PROGTEST_PROJECT_GAME_H
#define PROGTEST_PROJECT_GAME_H

#include <string>
#include <vector>

class Terrain;
class GameStats;
class Fragment;
class Display;
class Player;
class Towers;
class Enemies;
class Rounds;
class Help;

const char KEY_SPEED = '/';
const char KEY_QUIT = 'q';

class Game {

public:
    /// Vector of all Game's fragments
    std::vector<Fragment *> Fragments;

    /// Return Towers system in use
    Towers *GetTowers();

    /// Return GameStats system in use
    GameStats *GetStats();

    /// Return Display system in use
    Display * GetDisplay();
    
    /// Return Terrain system in use
    Terrain * GetTerrain();
    
    /// Return Enemies system in use
    Enemies * GetEnemies();

    /// Return Rounds system in use
    Rounds * GetRounds();

    /// Return Help system in use
    Help * GetHelp();

public:

    /// Default constructor
    Game();

    /**
     * Setup game's properties from setupFile
     * @param setupFile Setupfile to load
     * @return true on success
     */
    bool Setup(const std::string &setupFile);

    /**
     * Start a new game on map mapName
     * @param mapName map to load
     * @return true on success
     */
    bool NewGame(const std::string& mapName);

    /**
     * Load a saved game
     * @param saveFile Location of saved game
     * @return true on success
     */
    bool LoadGame(const std::string& saveFile);
    
    /**
     * Start the main game loop
     */
    void Start();

    /// Default destructor
    ~Game();

private:

    // All of these are just specific pointers to the fragments in Game::Fragments
    Display * _display;
    Terrain * _terrain;
    GameStats * _gameStats;
    Player * _player;
    Towers *_towers;
    Enemies *_enemies;
    Rounds *_rounds;
    Help *_help;
};

#endif //PROGTEST_PROJECT_GAME_H
