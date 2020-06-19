#include "Rounds.h"
#include "Enemies.h"
#include "../Game.h"
#include "../utils/TSVReader.h"
#include "../utils/TSVWriter.h"

Rounds::Rounds(Game *game) : Fragment(game) {

}

void Rounds::RequestDimensions(int &width, int &height) {

}

bool Rounds::Save(TSVWriter &writer) {

    writer.Write("ROUND");
    writer.Write(m_Round);
    writer.Next();

    writer.Write("PREP_TIMEOUT");
    writer.Write(m_PrepareTimeout);
    writer.Next();

    writer.Write("PREP_STAGE");
    writer.WriteBoolean(m_PrepareStage);
    writer.Next();

    writer.Write("GAME_STAGE");
    writer.WriteBoolean(m_GameStage);
    writer.Next();

    writer.Write("TO_SPAWN");
    writer.Write(m_ToSpawn);
    writer.Next();

    return writer.Good();
}

bool Rounds::Load(TSVReader &reader) {

    if (reader.NextString() != "ROUND")
        return false;
    m_Round = reader.NextInt();

    if (reader.NextString() != "PREP_TIMEOUT")
        return false;
    m_PrepareTimeout = reader.NextDouble();

    if (reader.NextString() != "PREP_STAGE")
        return false;
    m_PrepareStage = reader.NextBoolean();

    if (reader.NextString() != "GAME_STAGE")
        return false;
    m_GameStage = reader.NextBoolean();

    if (reader.NextString() != "TO_SPAWN")
        return false;
    m_ToSpawn = reader.NextInt();

    return true;
}

void Rounds::Render() {

}

Rounds::~Rounds() {

}

void Rounds::Ready() {
    m_PrepareTimeout = 10;
    m_PrepareStage = true;
}

void Rounds::Update(double delta) {

    if (m_PrepareStage){

        m_PrepareTimeout -= delta;

        if (m_PrepareTimeout < 0){
            m_Game->GetEnemies()->RegeneratePaths();
            m_PrepareTimeout = 0;
            m_PrepareStage = false;
            m_GameStage = true;
            m_Round++;
            //m_SpawnTimeout = 1;
            m_ToSpawn = m_Round * m_Round;
        }

    } else /*if (m_GameStage)*/{
        if (m_Game->GetEnemies()->EnemyCount() == 0 && m_ToSpawn == 0){
            m_PrepareStage = true;
            m_GameStage = false;
            m_PrepareTimeout = 30;
        }
    }

    if (m_GameStage){
        if (m_ToSpawn > 0 && m_PrepareTimeout < 0){
            m_PrepareTimeout = 1;
            m_Game->GetEnemies()->SpawnEnemy(m_Round);
            m_ToSpawn--;
        }
        m_PrepareTimeout -= delta;
    }
}

bool Rounds::IsPrepareStage() {
    return m_PrepareStage;
}

double Rounds::GetPrepareTimeout() {
    return m_PrepareTimeout;
}

void Rounds::DebugSkipWait() {
    m_PrepareTimeout = 0;
}

int Rounds::GetRound() {
    return m_Round;
}

int Rounds::GetToSpawn() {
    return m_ToSpawn;
}

