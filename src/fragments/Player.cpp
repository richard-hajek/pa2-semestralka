#include "Player.h"

#include "../Game.h"
#include "Terrain.h"
#include "Towers.h"
#include "Enemies.h"
#include "Rounds.h"

#include <ncurses.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

Player::Player(Game *game) : Fragment(game) {

}

void Player::Render() {
    WINDOW * terrain = m_Game->GetTerrain()->ShareWindow();
    wmove(terrain, _cursorY, _cursorX);
    wnoutrefresh(terrain);
}

Player::~Player() {

}

void Player::OnInput(int c) {
    int maxX, maxY;

    getmaxyx(m_Game->GetTerrain()->ShareWindow(), maxY, maxX);

    if (c == 'w'){
        _cursorY = MAX(_cursorY - 1, 0);
    }
    else if (c == 's'){
        _cursorY = MIN(_cursorY + 1, maxY - 1);
    }
    else if (c == 'a'){
        _cursorX = MAX(_cursorX - 1, 0);
    }
    else if (c == 'd'){
        _cursorX = MIN(_cursorX + 1, maxX - 1);
    }
    else if (c == '*'){
        m_Game->GetRounds()->DebugSkipWait();
        m_Game->GetEnemies()->DebugWipeEnemies();
    }
    else if (m_Game->GetTerrain()->GetTile(_cursorY, _cursorX)->GetBuildable() && m_Game->GetRounds()->IsPrepareStage()){
        if (m_Game->GetTowers()->BuildTower(_cursorX, _cursorY, c)){
            m_Game->GetTerrain()->GetTile(_cursorY, _cursorX)->Obstruct();
        }
    }
}
