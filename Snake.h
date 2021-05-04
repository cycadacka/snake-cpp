#pragma once
#include <vector>
#include <string>
#include "Renderer.h"
#include "Fruit.h"
#include "Point2D.h"

class Snake {
private:
    std::vector<Point2D> m_segments;
    Point2D m_direction;
    
public:
    Snake(Point2D position, Point2D direction, short length=1);

    size_t get_length() const;

    bool TryMove(const Renderer& renderer);
    void TryEat(const Renderer& renderer, Fruit& fruit);

    void Render(Renderer& renderer);
};
