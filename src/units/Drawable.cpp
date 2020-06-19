#include "Drawable.h"

Drawable::Drawable(int x, int y): m_X(x), m_Y(y) {

}

double Drawable::GetX() const {
    return m_X;
}

double Drawable::GetY() const {
    return m_Y;
}
