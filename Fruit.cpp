#include "Fruit.h"

// PRIVATE

// PUBLIC

Fruit::Fruit(Point2D position)
{
    m_position = position;
}

short Fruit::get_x() const
{
    return m_position.x;
}

short Fruit::get_y() const
{
    return m_position.y;
}

void Fruit::Reposition(const Renderer& renderer)
{
    m_position.x = rand() % renderer.get_width();
    m_position.y = rand() % renderer.get_height();
}

void Fruit::Render(Renderer& renderer)
{
    renderer.SetAttribute(m_position.x, m_position.y, FOREGROUND_RED | FOREGROUND_INTENSITY);
    renderer.SetCharacter(m_position.x, m_position.y, '8');
}
