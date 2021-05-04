#include "Renderer.h"

// PRIVATE

// PUBLIC

Renderer::Renderer(Point2D size) : m_size(size)
{
    m_charactersToBeWritten = std::vector<CHAR_INFO>(size.x * size.y);
    
    for (unsigned short i = 0; i < size.x * size.y; i++)
    {
        m_charactersToBeWritten[i].Attributes = 0xF0;
        m_charactersToBeWritten[i].Char.UnicodeChar = ' ';
    }
}

const short Renderer::get_width() const
{
    return m_size.x;
}

const short Renderer::get_height() const
{
    return m_size.y;
}

void Renderer::SetCharacter(short x, short y, WCHAR character)
{
    m_charactersToBeWritten[x + y * m_size.x].Char.UnicodeChar = character;
}

void Renderer::SetAttribute(short x, short y, WORD attributes)
{
    m_charactersToBeWritten[x + y * m_size.x].Attributes = attributes | 0xF0;
}

void Renderer::Render()
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    if (output == INVALID_HANDLE_VALUE)
        throw std::exception("GetStdHandle failed.");

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(output, &csbi))
        throw std::exception("GetConsoleScreenBufferInfo failed.");

    if (!WriteConsoleOutput(output, m_charactersToBeWritten.data(), { m_size.x, m_size.y }, { 0, 0 }, &csbi.srWindow))
        throw std::exception("WriteConsoleOutput failed");

    for (unsigned short i = 0; i < m_size.x * m_size.y; i++)
    {
        m_charactersToBeWritten[i].Attributes = 0xF0;
        m_charactersToBeWritten[i].Char.UnicodeChar = ' ';
    }
}
