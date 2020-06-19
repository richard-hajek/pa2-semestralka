#include "GameStats.h"
#include "../utils/TSVReader.h"
#include "../utils/TSVWriter.h"
#include "Enemies.h"
#include "Rounds.h"
#include "../Game.h"

#define STATS_WIDTH 80
#define STATS_HEIGHT 3

bool GameStats::Setup(TSVReader &reader) {
    return true;
}

void GameStats::RequestDimensions(int &width, int &height) {
    width = STATS_WIDTH;
    height = STATS_HEIGHT;
}

bool GameStats::Save(TSVWriter &writer) {

    writer.Write("HEALTH");
    writer.Write(Health);
    writer.Next();

    writer.Write("MONEY");
    writer.Write(Money);
    writer.Next();

    writer.Write("SCORE");
    writer.Write(Score);
    writer.Next();

    return writer.Good();
}

bool GameStats::Load(TSVReader & reader) {
    if (reader.NextString() != "HEALTH")
        return false;
    Health = reader.NextInt();

    if (reader.NextString() != "MONEY")
        return false;
    Money = reader.NextInt();

    if (reader.NextString() != "SCORE")
        return false;
    Score = reader.NextInt();

    return true;
}

void GameStats::Render() {

    int x = 0;

    mvwprintw(m_Window, 1, 0, std::string(STATS_WIDTH, ' ').c_str());

    auto printVal = [&](const std::string& label, int value, const std::string & unit = "") {
        std::string text = "| " + label + ": " + std::to_string(value) + unit + " ";
        mvwprintw(m_Window, 1, x, (text).c_str());
        x += text.length();
    };

    if (!GameOver) {
        printVal("HEALTH", Health);
        printVal("MONEY", Money);
        printVal("SCORE", Score);
        printVal("WAVE", m_Game->GetRounds()->GetRound());

        if (m_Game->GetRounds()->IsPrepareStage()) {
            printVal("PREPARE", (int) m_Game->GetRounds()->GetPrepareTimeout(), "s");
        } else {
            printVal("REMAINING", m_Game->GetEnemies()->EnemyCount() + m_Game->GetRounds()->GetToSpawn());
        }
    } else {
        printVal("MONEY", Money);
        printVal("SCORE", Score);
        printVal("WAVE", m_Game->GetRounds()->GetRound());
        mvwprintw(m_Window, 1, x, std::string("| GAME OVER").c_str());
    }

    box(m_Window, 0, 0);
    wnoutrefresh(m_Window);
}

void GameStats::Hurt(int damage) {
    Health -= damage;
    if (Health < 0)
        Health = 0;
    if (Health == 0)
        GameOver = true;
}

GameStats::~GameStats() = default;
