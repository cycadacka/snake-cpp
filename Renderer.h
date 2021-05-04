#pragma once
#include <Windows.h>
#include <vector>
#include "Point2D.h"

class Renderer
{
    std::vector<CHAR_INFO> m_charactersToBeWritten;
    const Point2D m_size;

public:
    Renderer(Point2D size);

    const short get_width() const;
    const short get_height() const;

    void SetCharacter(short x, short y, WCHAR character);
    void SetAttribute(short x, short y, WORD attributes);

    void Render();
};

