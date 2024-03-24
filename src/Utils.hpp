#pragma once

#include <SDL2/SDL.h>
#include <math.h>  
#include "Math.hpp"
#include <time.h>


const int WIDTH = 1280, HEIGHT = 720;


namespace Utils
{
    inline float hireTimeInSeconds()
    {
        float t = SDL_GetTicks();

        t *= 0.001f;

        return t;
    }

    inline bool oneSecondFlag()
    {
        static int32_t lastTime = 0;
        int32_t currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= 1000) {
            lastTime = currentTime;
            return true;
        }
        return false;
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

    inline bool isOutOfBounds(Vector2f pos) 
    {
        return (pos.x < 0 || pos.x > WIDTH || pos.y < 0 || pos.y > HEIGHT);
    }

    inline Vector2f getTextureCenter(SDL_Rect rect) 
    {
        Vector2f center;
        center.x = rect.x + rect.w / 2;
        center.y = rect.y + rect.h / 2;

        return center;
    }

}