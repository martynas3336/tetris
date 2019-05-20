#include "functions.h"
template<class T>
void fetch(int x, int y, T c)
{
    // CURSOR AND OUTPUT SETTINGS
    HANDLE s=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;
    ConCurInf.bVisible = false;
    ConCurInf.dwSize = 10;
    SetConsoleCursorInfo(s,&ConCurInf);
    COORD poz;

    poz.X = x;
    poz.Y = y;
    SetConsoleCursorPosition(s, poz);
    std::cout << c;
}

int random(int min, int max) //range : [min, max)
{
   static bool first = true;
   if (first)
   {
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

void generateBorders(int y, int x, int height, int width)
{
    // TOP LEFT CORNER
    if(x > 0 && y > 0)
    {
        fetch(x-1, y-1, (char)201);
    }

    // TOP BORDER
    if(y > 0)
    {
        for(int i = 0; i < width; i++)
        {
            fetch(x + i, y - 1, (char)205);
        }
    }

    // TOP RIGHT CORNER
    if(y > 0)
    {
        fetch(x + width, y-1, (char)187);
    }

    // RIGHT BORDER
    for(int i = 0; i < height; i++)
    {
        fetch(x + width, y+i, (char)186);
    }

    // BOTTOM RIGHT CORNER
    fetch(x + width, y + height, (char)188);

    // BOTTOM BORDER
    for(int i = 0; i < width; i++)
    {
        fetch(x + i, y + height, (char)205);
    }

    // BOTTOM LEFT CORNER
    fetch(x - 1, y + height, (char)200);

    // LEFT BORDER
    if(x > 0)
    {
        for(int i = 0; i < height; i++)
        {
            fetch(x-1, y+i, (char)186);
        }
    }
}
