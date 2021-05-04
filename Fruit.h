#pragma once
#include <Windows.h>
#include "Renderer.h"
#include "Point2D.h"

class Fruit
{
    Point2D m_position;

public:
    Fruit(Point2D position);

    short get_x() const;
    short get_y() const;

    void Reposition(const Renderer& renderer);
    void Render(Renderer& renderer);
};


