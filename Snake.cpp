#include "Snake.h"
#include <iostream>
#include <string>

// PRIVATE

// PUBLIC

Snake::Snake(Point2D position, Point2D direction, short length)
{
    for (short i = 0; i < length; i++)
    {
        m_segments.push_back({
            position.x - direction.x * i,
            position.y - direction.y * i,
        });
    }

    m_direction = direction;
}

size_t Snake::get_length() const
{
    return m_segments.size();
}

bool Snake::TryMove(const Renderer& renderer)
{
    if (m_direction.x == 0 && m_direction.y != 0)
    {
        m_direction.x = ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0) - ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0);

        if (m_direction.x != 0)
            m_direction.y = 0;
    }
    else if (m_direction.y == 0 && m_direction.x != 0)
    {
        m_direction.y = ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0) - ((GetAsyncKeyState(VK_UP) & 0x8000) != 0);

        if (m_direction.y != 0)
            m_direction.x = 0;
    }

    for (size_t i = m_segments.size() - 1; i > 0; i--)
    {
        if (i != 0 && m_segments[0].x == m_segments[i].x && m_segments[0].y == m_segments[i].y)
            return false;

        m_segments[i].x = m_segments[i - 1].x;
        m_segments[i].y = m_segments[i - 1].y;
    }

    m_segments[0].x += m_direction.x;
    m_segments[0].y += m_direction.y;

    if (m_segments[0].x == -1 || m_segments[0].x == renderer.get_width() || m_segments[0].y == -1 || m_segments[0].y == renderer.get_height())
        return false;

    return true;
}

void Snake::TryEat(const Renderer& renderer, Fruit& fruit)
{
    if (m_segments[0].x == fruit.get_x() && m_segments[0].y == fruit.get_y())
    {
        m_segments.push_back(m_segments.back());
        fruit.Reposition(renderer);
    }
}

void Snake::Render(Renderer& renderer)
{
    for (size_t i = 0; i < m_segments.size(); i++)
    {
        renderer.SetAttribute(m_segments[i].x, m_segments[i].y, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        renderer.SetCharacter(m_segments[i].x, m_segments[i].y, i == 0 ? '+' : 'H');
    }
}
