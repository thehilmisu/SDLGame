#pragma once

#include <SDL2/SDL.h>
#include <math.h>  
#include "Math.hpp"
#include <time.h>


const int WIDTH = 1280, HEIGHT = 720;


namespace Utils
{
    //
    inline float hireTimeInSeconds()
    {
        float t = SDL_GetTicks();

        t *= 0.001f;

        return t;
    }

    inline Vector2f generateRandomLocation()
    {
        srand(time(NULL)); // Seed the time
        int x = rand() % (WIDTH - 5 + 1) + 5;
        int y = rand() % (HEIGHT - 5 + 1) + 5;

        return Vector2f(x, y);
    }

    inline float distance(int x1, int y1, int x2, int y2)
    {
        return sqrt( pow( x2 - x1, 2 ) + pow( y2 - y1, 2 ) );
    }
}