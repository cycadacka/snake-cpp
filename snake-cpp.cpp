#include <string>
#include <time.h>
#include "Renderer.h"
#include "Snake.h"
#include "Fruit.h"

#define X_SIZE 40
#define Y_SIZE 20

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    Renderer* renderer = new Renderer({ X_SIZE, Y_SIZE });
    Snake* snake = new Snake({ rand() % (X_SIZE - 1), rand() % (Y_SIZE - 1) }, { 1, 0 }, 3U);
    Fruit* fruit = new Fruit({ rand() % X_SIZE, rand() % Y_SIZE });

    while (1)
    {
        if (!snake->TryMove(*renderer))
            break;

        // Might fail to eat or not
        snake->TryEat(*renderer, *fruit);

        fruit->Render(*renderer);
        snake->Render(*renderer);

        renderer->Render();
        
        Sleep(100);
    }

    const size_t bufSize = 11 + std::to_string(snake->get_length()).length();

    wchar_t* text = new wchar_t[bufSize];
    swprintf_s(text, bufSize, L"You lost!\n%d", snake->get_length());
    MessageBox(NULL, text, L"", MB_OK);

    delete[] text;
    delete renderer;
    delete snake;
    delete fruit;
}
