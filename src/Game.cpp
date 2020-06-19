#include "Game.h"
#include "fragments/Display.h"
#include "fragments/Terrain.h"
#include "fragments/GameStats.h"
#include "fragments/Player.h"
#include "fragments/Towers.h"
#include "fragments/Enemies.h"
#include "fragments/Rounds.h"
#include "fragments/Help.h"
#include "utils/TSVReader.h"
#include "utils/TSVWriter.h"

template<typename T>
Fragment * FindFragment(std::vector<Fragment *> const & systems){
    for( auto sys : systems){
        if (dynamic_cast<T>(sys) != nullptr)
            return sys;
    }
    return nullptr;
}

Game::Game() : Fragments({new Display(this), new GameStats(this),
                          new Rounds(this),
                          new Terrain(this),
                          new Towers(this), new Enemies(this),
                          new Player(this), new Help(this)}) {

    _display = dynamic_cast<Display *>(FindFragment<Display *>(Fragments));
    _gameStats = dynamic_cast<GameStats *>(FindFragment<GameStats *>(Fragments));
    _terrain = dynamic_cast<Terrain *>(FindFragment<Terrain *>(Fragments));
    _towers = dynamic_cast<Towers *>(FindFragment<Towers *>(Fragments));
    _enemies = dynamic_cast<Enemies *>(FindFragment<Enemies *>(Fragments));
    _player = dynamic_cast<Player *>(FindFragment<Player *>(Fragments));
    _rounds = dynamic_cast<Rounds *>(FindFragment<Rounds *>(Fragments));
    _help = dynamic_cast<Help *>(FindFragment<Help *>(Fragments));
}

bool Game::Setup(const std::string &setupFile) {
    auto reader = TSVReader(setupFile);
    for (auto sys : Fragments)
        if (!sys->Setup(reader))
            return false;

    return true;
}

bool Game::NewGame(const std::string &mapName) {
    return _terrain->SetActiveMap(mapName);
}

bool Game::LoadGame(const std::string &saveFile) {
    auto reader = TSVReader(saveFile);
    for (auto sys : Fragments)
        if (!sys->Load(reader))
            return false;
    return true;
}

std::chrono::nanoseconds GetCurrentTime(){
    return std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch());
}

void Game::Start() {

    for (auto sys : Fragments)
        sys->Ready();

    auto lastUpdate = GetCurrentTime();

    while (true) {
        int c = getch();

        if (c == 'q')
            break;

        if (c == 'n')
        {
            auto * w = new TSVWriter("save.tsv");
            for (auto sys : Fragments)
                sys->Save(*w);
            delete w;
        }

        if (c != -1)
            _player->OnInput(c);

        auto updateAt = GetCurrentTime();
        double delta = (updateAt - lastUpdate).count() / (double)1000000000;

        if (c == '/')
            delta = 1; // Speed up the game

        if (!_gameStats->GameOver){
            for (auto sys : Fragments)
                sys->Update(delta);
        }

        for (auto sys : Fragments)
            sys->Render();

        lastUpdate = updateAt;
    }
}

Game::~Game() {
    for (auto sys : Fragments)
        delete sys;
}

Display *Game::GetDisplay() {
    return _display;
}

Terrain *Game::GetTerrain() {
    return _terrain;
}

Towers *Game::GetTowers() {
    return _towers;
}

GameStats *Game::GetStats() {
    return _gameStats;
}

Enemies *Game::GetEnemies() {
    return _enemies;
}

Rounds *Game::GetRounds() {
    return _rounds;
}

Help *Game::GetHelp() {
    return _help;
}

/*
 *
void Update(){
    for(const auto& row : terrain){
        for (auto * tile : row){
            if (Tower tower = Tower& dynamic_cast<Tower&> (*tile)){
                int x, y, dmg;
                tower.UpdateAttack(terrain, x, y, dmg);
                (Enemy& dynamic_cast<Enemy&> (*terrain[x][y]).OnAttacked(dmg);
            }
        }
    }

    for (const auto & enemy : Enemy){
        if (! Enemy->IsDead() ){
            enemy->UpdateAndMove();
        }
    }
}**/
