#include "Help.h"
#include "Towers.h"
#include "Enemies.h"
#include "../units/Tower.h"
#include "../units/Enemy.h"
#include "../Game.h"

void Help::RequestDimensions(int &width, int &height) {
    height = 7;

    height += 1 + m_Game->GetTowers()->GetAvailableTowers().size();
    height += 1 + m_Game->GetEnemies()->GetAvailableEnemies().size();

    width = 50;
}

void Help::Render() {

    if ( ! m_Redraw)
        return;

    box(m_Window, 0, 0);
    m_Redraw = false;

    int row = 1;
    auto printLine = [&](const std::string& text) {
        mvwprintw(m_Window, row, 1, (text).c_str());
        row++;
    };

    printLine("Move: WASD");
    printLine("Speed up time: /");
    printLine("Save: n");
    //printLine("Skip: *");

    row++;
    printLine("Available towers:");
    for(auto * data : m_Game->GetTowers()->GetAvailableTowers()){
        printLine(data->Describe());
    }

    row++;
    printLine("Available enemies:");
    for(auto * data : m_Game->GetEnemies()->GetAvailableEnemies()){
        printLine(data->Describe());
    }

    wnoutrefresh(m_Window);
}

Help::~Help() {

}
