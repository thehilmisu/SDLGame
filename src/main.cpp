#include <iostream>
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include <memory>
#include <vector>

const int WIDTH = 1280, HEIGHT = 720;


std::vector<std::unique_ptr<Entity>> mapItems;

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "FAILED TO INIT SDL : " << SDL_GetError() << std::endl;
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "IMG INIT has failed" << SDL_GetError() << std::endl;
    }

    RenderWindow window("GAME v1.0", WIDTH, HEIGHT);

    SDL_Texture *grassTexture = window.loadTexture("../res/gfx/ground_grass_1.png");
    SDL_Texture *cobra = window.loadTexture("../res/gfx/cobra.png");
    SDL_Texture *knight = window.loadTexture("../res/gfx/hulking_knight.png");
    SDL_Texture *bulletTexture = window.loadTexture("../res/gfx/bullet.png");

    std::unique_ptr<Player> player = std::make_unique<Player>(Vector2f(600, 320), cobra);
    std::unique_ptr<Bullet> bullet = nullptr;
    //Player player(Vector2f(600,320), cobra);
        
    bool gameRunning = true;
    SDL_Event event;

    const float deltaTime = 0.01f;
    float accumulator = 0.0f;
    float currentTime = Utils::hireTimeInSeconds();

    while (gameRunning)
    {
        int startTicks = SDL_GetTicks();
        float newTime = Utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;

        accumulator += frameTime;

        PlayerMovement movement;

        while (accumulator >= deltaTime)
        {
            while (SDL_PollEvent(&event))
            {
                if (SDL_QUIT == event.type)
                {
                    break;
                }

                if (SDL_MOUSEMOTION == event.type)
                {
                    SDL_GetMouseState(&movement.mouse_x, &movement.mouse_y);

                    std::cout << movement.mouse_x << " : " << movement.mouse_y << std::endl;
                }

                if (SDL_MOUSEBUTTONDOWN == event.type)
                {
                    if (SDL_BUTTON_LEFT == event.button.button)
                    {
                        std::cout << "Left mouse button is down" << std::endl;
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        
                        
                        bullet = std::make_unique<Bullet>(player.get()->getPos(), bulletTexture);
                        bullet.get()->setDirection(Vector2f(x,y));
                        bullet.get()->setShooting(true);
                        
                        
                    }
                    else if (SDL_BUTTON_RIGHT == event.button.button)
                    {
                        std::cout << "Right mouse button is down" << std::endl;
                    }
                    else if (SDL_BUTTON_MIDDLE == event.button.button)
                    {
                        std::cout << "Middle mouse button is down" << std::endl;
                    }
                }

                if (SDL_MOUSEBUTTONUP == event.type)
                {
                    if (SDL_BUTTON_LEFT == event.button.button)
                    {
                        std::cout << "Left mouse button is up" << std::endl;
                        
                    }
                    else if (SDL_BUTTON_RIGHT == event.button.button)
                    {
                        std::cout << "Right mouse button is up" << std::endl;
                    }
                    else if (SDL_BUTTON_MIDDLE == event.button.button)
                    {
                        std::cout << "Middle mouse button is up" << std::endl;
                    }
                }

                if (SDL_MOUSEWHEEL == event.type)
                {
                    if (event.wheel.y > 0) // scroll up
                    {
                        std::cout << "Mouse wheel is scrolling up" << std::endl;
                    }
                    else if (event.wheel.y < 0) // scroll down
                    {
                        std::cout << "Mouse wheel is scrolling down" << std::endl;
                    }

                    if (event.wheel.x > 0) // scroll right
                    {
                        std::cout << "Mouse wheel is scrolling right" << std::endl;
                    }
                    else if (event.wheel.x < 0) // scroll left
                    {
                        std::cout << "Mouse wheel is scrolling left" << std::endl;
                    }
                }

                if (SDL_KEYDOWN == event.type)
                {
                    // std::cout << "Key is down" << std::endl;
                    if (SDLK_a == event.key.keysym.sym)
                    {
                        std::cout << "A is down - Move left" << std::endl;
                        movement.move_left = true;
                    }
                    else if (SDLK_s == event.key.keysym.sym)
                    {
                        std::cout << "S is down - Move down" << std::endl;
                        movement.move_down = true;
                    }
                    else if (SDLK_d == event.key.keysym.sym)
                    {
                        std::cout << "D is down - Move right" << std::endl;
                        movement.move_right = true;
                    }
                    else if (SDLK_w == event.key.keysym.sym)
                    {
                        std::cout << "W is down - Move up" << std::endl;
                        movement.move_up = true;
                    }
                }
                else if (SDL_KEYUP == event.type)
                {
                    // std::cout << "Key is up" << std::endl;
                    if (SDLK_a == event.key.keysym.sym)
                    {
                        std::cout << "A is up - Stop moving left" << std::endl;
                        movement.move_left = false;
                    }
                    else if (SDLK_s == event.key.keysym.sym)
                    {
                        std::cout << "S is up - Stop moving down" << std::endl;
                        movement.move_down = false;
                    }
                    else if (SDLK_d == event.key.keysym.sym)
                    {
                        std::cout << "D is up - Stop moving right" << std::endl;
                        movement.move_right = false;
                    }
                    else if (SDLK_w == event.key.keysym.sym)
                    {
                        std::cout << "W is up - Stop moving up" << std::endl;
                        movement.move_up = false;
                    }
                }
            }

            accumulator -= deltaTime;
        }

        const float alpha = accumulator / deltaTime;

        window.clear();

        player.get()->update(alpha, movement);
        window.render(*player.get());
        window.render(*std::make_unique<Entity>(Vector2f(0,0),grassTexture));
        if(bullet != nullptr && bullet.get()->getShooting())
        {
            bullet.get()->update(alpha);
            window.render(*bullet.get());
        }
        
        window.display();

        int frameTicks = SDL_GetTicks() - startTicks;
        if (frameTicks < 1000 / window.getRefreshRate())
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
    }

    window.cleanUp();
    SDL_Quit();
}
