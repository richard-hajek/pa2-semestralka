#include "Tower.h"
#include "../utils/TSVReader.h"

TowerTemplate::TowerTemplate(TSVReader &reader) {
    ID = reader.NextInt();
    Name = reader.NextString();
    Symbol = reader.NextChar();
    Key = reader.NextChar();
    Price = reader.NextInt();
    Damage = reader.NextInt();
    Range = reader.NextInt();
}

std::string TowerTemplate::Describe() const {
    return Name + ": " + Symbol + ", " +
            Key + ", " +
            std::to_string(Price) + "$, " +
            "DMG: " + std::to_string(Damage) + ", " +
            "RAN: " + std::to_string(Range);
}

Tower::Tower(int x, int y, const TowerTemplate *source) : Drawable(x, y), _source(source), m_Variation(rand()){

}

void Tower::UpdateAttack(Enemies &enemies, double delta, Enemy *&pEnemy, int & damage) {
    if (m_Cooldown <= 0){
        std::vector<Enemy *> targets = enemies.GetEnemiesAround(m_X, m_Y, _source->Range);

        if ( ! targets.empty()){
            targets[0]->OnAttacked(_source->Damage, damage);
            pEnemy = targets[0];
            m_Cooldown = 1;
            m_Effects = 1;
        }
    }
    else {
        m_Cooldown -= delta;
        if (m_Cooldown < 0.5)
            m_Effects = 0;
    }
}

char Tower::GetChar() const {
    return _source->Symbol;
}

uint8_t Tower::GetEffects() const {
    return m_Effects;
}

int Tower::GetID() const {
    return _source->ID;
}

int Tower::GetVariation() const {
    return m_Variation;
}
