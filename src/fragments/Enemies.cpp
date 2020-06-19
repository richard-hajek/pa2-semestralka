#include "Enemies.h"
#include "../Game.h"
#include "../units/Enemy.h"
#include "Terrain.h"
#include "GameStats.h"
#include "Display.h"
#include "../utils/pathfinding.h"
#include "../utils/TSVReader.h"
#include "../utils/TSVWriter.h"
#include "../utils/Log.h"
#include <chrono>
#include <random>
#include <exception>

Enemies::Enemies(Game *game) : Fragment(game) {

}

bool Enemies::Setup(TSVReader &reader) {

    if (reader.NextString() != "ENEMIES") {
        Log::Warn("Enemies", "[SETUP] Failed to find ENEMIES keyword!");
        return false;
    }

    int count = reader.NextInt();
    for(int i = 0; i < count; i++){

        if (reader.NextString() != "ENEMY") {
            Log::Warn("Enemies", "[SETUP] Failed to find ENEMY keyword!");
            return false;
        }

        _enemyData.push_back(new EnemyTemplate(reader));
    }

    return true;
}

std::pair<int, int> FindNonWall(int x, Terrain const & terrain){
    for(int i = 0; terrain.GetTile(i, x) != nullptr; i++){
        if (terrain.GetTile(i, x)->GetWalkable())
            return std::make_pair(x, i);
    }

    throw std::exception(); // We should always be able to find a walkable tile, if not something bad happened (invalid terrain?)
}

bool Enemies::Save(TSVWriter &writer) {

    writer.Write((int)_enemies.size());
    writer.Next();
    for(auto enemy : _enemies){
        writer.Write("ENEMY");
        writer.Write(enemy->GetID());
        writer.Write(enemy->GetHP());
        writer.Write(enemy->GetX());
        writer.Write(enemy->GetY());
        writer.Next();
    }

    if ( ! writer.Good()){
        Log::Warn("Enemies", "During save, TSVWriter entered a failed state!");
    }

    return writer.Good();
}

bool Enemies::Load(TSVReader &reader) {

    int count = reader.NextInt();

    for (int i = 0; i < count; i++) {


        if (reader.NextString() != "ENEMY")
            return false;

        int id = reader.NextInt();
        int hp = reader.NextInt();
        double x = reader.NextDouble();
        double y = reader.NextDouble();
        _enemies.push_back(new Enemy((int)x, (int)y, hp, *_enemyData[id]));
    }

    return true;
}

void Enemies::Ready() {
    _spawnPoint = FindNonWall(0, *m_Game->GetTerrain());
    _goal = FindNonWall(m_Game->GetTerrain()->GetMapWidth() - 1, *m_Game->GetTerrain());
    RegeneratePaths();
}

void Enemies::Update(double delta) {
    for (Enemy * enemy : _enemies){
        bool reachedEnd = false;
        enemy->UpdateMove(*this, delta, reachedEnd);

        if (reachedEnd){
            m_Game->GetStats()->Hurt(enemy->GetHP());
            enemy->Kill();
        }
    }
}

void Enemies::Render() {
    WINDOW * win = m_Game->GetTerrain()->ShareWindow();
    
    for(const Enemy * enemy : _enemies){
        if (enemy->IsDead())
            continue;

        wattron(win, Display::GetEnemyColor(enemy->GetID(), enemy->GetVariation()));
        mvwaddch(win, enemy->GetY(), enemy->GetX(), enemy->GetChar());
        wattroff(win, Display::GetEnemyColor(enemy->GetID(), enemy->GetVariation()));
    }

    wnoutrefresh(win);
}

Enemies::~Enemies() {

}

std::vector<std::pair<int, int>> const & Enemies::GetPath(int variationSeed) const {
    return _pathVariations[variationSeed % _pathVariations.size()];
}

double inspector(Terrain const & terrain, int x, int y){
    Tile * tile = terrain.GetTile(y, x);

    if (tile == nullptr || ! tile->GetWalkable()){
        return IMPASSABLE;
    }

    std::random_device r;
    std::mt19937 gen{r()};
    std::normal_distribution<> d{10,1};
    return d(gen);
}

void Enemies::RegeneratePaths() {
    _pathVariations.clear();
    for (int i = 0; i < PATH_VARIATIONS; i++){
        std::vector<TPoint> path = astar_search(_spawnPoint, _goal, *m_Game->GetTerrain(), inspector);
        _pathVariations.push_back(path);
    }
}

void Enemies::SpawnEnemy(int maxId) {
    unsigned int id = rand() % (maxId + 1);
    id = id % _enemyData.size();
    _enemies.push_back(new Enemy(_spawnPoint.first, _spawnPoint.second, *_enemyData[id]));
}

bool alive (Enemy * enemy){
    return ! enemy->IsDead();
}

int Enemies::EnemyCount() {
    return std::count_if(_enemies.begin(), _enemies.end(), alive);
}

void Enemies::DebugWipeEnemies() {
    for(auto enemy : _enemies){
        delete enemy;
    }
    _enemies.erase(_enemies.begin(), _enemies.end());
}

double distance(double x, double y, double x2, double y2){
    double dx = x - x2;
    double dy = y - y2;
    return sqrt(dx*dx + dy*dy);
}

std::vector<Enemy *> Enemies::GetEnemiesAround(int x, int y, int range) {
    std::vector<Enemy *> inRange;

    for(auto * en : _enemies){

        if (en->IsDead())
            continue;

        if (distance(x, y, en->GetX(), en->GetY()) <= range){
            inRange.push_back(en);
        }
    }

    return inRange;
}

std::vector<EnemyTemplate *> Enemies::GetAvailableEnemies() const {
    return _enemyData;
}


