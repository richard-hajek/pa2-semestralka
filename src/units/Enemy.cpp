#include "Enemy.h"
#include "../utils/TSVReader.h"
#include "../fragments/Enemies.h"

EnemyTemplate::EnemyTemplate(TSVReader &reader) {
    ID = reader.NextInt();
    Name = reader.NextString();
    Char = reader.NextChar();
    HP = reader.NextInt();
    Speed = reader.NextInt();
}

std::string EnemyTemplate::Describe() const {
    return Name + ": " + Char + "( " + std::to_string(HP) + " HP, " + std::to_string(Speed) + " m/s )";
}


Enemy::Enemy(int x, int y, const EnemyTemplate &source) : Drawable(x, y),
    _source(&source), _hp(source.HP), _variation(rand()), _pathProgress(0) {
}

void Enemy::UpdateMove(const Enemies &enemies, double delta, bool & reachedEnd) {

    if (IsDead())
        return;

    _pathProgress += delta * _source->Speed;

    if ((size_t)_pathProgress >= enemies.GetPath(_variation).size()){
        reachedEnd = true;
        return;
    }

    m_X = enemies.GetPath(_variation)[(int)_pathProgress].first;
    m_Y = enemies.GetPath(_variation)[(int)_pathProgress].second;
}

void Enemy::OnAttacked(int damage, int & dealt) {
    _hp -= damage;
    if (_hp >= 0)
        dealt = damage;
    else{
        dealt = damage + _hp;
        _hp = 0;
    }
}

bool Enemy::IsDead() const {
    return _hp <= 0;
}

char Enemy::GetChar() const {
    return _source->Char;
}

int Enemy::GetHP() const {
    return _hp;
}

void Enemy::Kill() {
    _hp = 0;
}

int Enemy::GetID() const {
    return _source->ID;
}

Enemy::Enemy(int x, int y, int hp, const EnemyTemplate &source) : Enemy(x, y, source) {
    _hp = hp;
}

int Enemy::GetVariation() const {
    return _variation;
}

Enemy::~Enemy() = default;
