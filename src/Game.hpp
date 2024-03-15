#pragma once

#include <iostream>
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include <memory>
#include <vector>

class Game
{
    public:
        Game();
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running();

    private:
        bool gameRunning;
        Vector2f generateRandomLocation();
        PlayerMovement *movement;
};