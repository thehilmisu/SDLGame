#include "Game.hpp"

RenderWindow window("GAME v1.0", WIDTH, HEIGHT);
SDL_Event event;

SDL_Texture *grassTexture = nullptr;
SDL_Texture *cobra = nullptr;
SDL_Texture *playerTex = nullptr;
SDL_Texture *knight = nullptr;
SDL_Texture *bulletTexture = nullptr;
SDL_Texture *backgroundTex = nullptr;

std::unique_ptr<Player> player = nullptr;

float alpha = 0.0f;

Game::Game()
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "FAILED TO INIT SDL : " << SDL_GetError() << std::endl;
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "IMG INIT has failed" << SDL_GetError() << std::endl;
    }

    movement = new PlayerMovement();

    grassTexture = window.loadTexture("../res/gfx/ground_grass_1.png");
    cobra = window.loadTexture("../res/gfx/cobra.png");
    playerTex = window.loadTexture("../res/gfx/player.png");
    knight = window.loadTexture("../res/gfx/hulking_knight.png");
    bulletTexture = window.loadTexture("../res/gfx/bullet.png");
    backgroundTex = window.loadTexture("../res/gfx/bg.png");

    player = std::make_unique<Player>(Vector2f(600, 320), playerTex);
    
    createEnemy();
    
    gameRunning = true;
}

void Game::handleEvents()
{
    while (SDL_PollEvent(&event))
    {
        if (SDL_QUIT == event.type)
        {
            break;
        }

        if (SDL_MOUSEMOTION == event.type)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            movement->mouse_x = x;
            movement->mouse_y = y;
            DEBUG_MSG(movement->mouse_x << " : " << movement->mouse_y);
        }

        if (SDL_MOUSEBUTTONDOWN == event.type)
        {
            if (SDL_BUTTON_LEFT == event.button.button)
            {
                std::cout << "Left mouse button is down" << std::endl;
                int x, y;
                SDL_GetMouseState(&x, &y);

                createBullet(Vector2f(x,y));
                
            }
            else if (SDL_BUTTON_RIGHT == event.button.button)
            {
                DEBUG_MSG("Right mouse button is down");
            }
            else if (SDL_BUTTON_MIDDLE == event.button.button)
            {
                DEBUG_MSG("Middle mouse button is down");
            }
        }

        if (SDL_MOUSEBUTTONUP == event.type)
        {
            if (SDL_BUTTON_LEFT == event.button.button)
            {
                DEBUG_MSG("Left mouse button is up");
            }
            else if (SDL_BUTTON_RIGHT == event.button.button)
            {
                DEBUG_MSG("Right mouse button is up");
            }
            else if (SDL_BUTTON_MIDDLE == event.button.button)
            {
                DEBUG_MSG("Middle mouse button is up");
            }
        }

        if (SDL_MOUSEWHEEL == event.type)
        {
            if (event.wheel.y > 0) // scroll up
            {
                DEBUG_MSG("Mouse wheel is scrolling up");
            }
            else if (event.wheel.y < 0) // scroll down
            {
                DEBUG_MSG("Mouse wheel is scrolling down");
            }

            if (event.wheel.x > 0) // scroll right
            {
                DEBUG_MSG("Mouse wheel is scrolling right");
            }
            else if (event.wheel.x < 0) // scroll left
            {
                DEBUG_MSG("Mouse wheel is scrolling left");
            }
        }

        if (SDL_KEYDOWN == event.type)
        {
            // std::cout << "Key is down" << std::endl;
            if (SDLK_a == event.key.keysym.sym)
            {
                DEBUG_MSG("A is down - Move left");
                movement->move_left = true;
            }
            else if (SDLK_s == event.key.keysym.sym)
            {
                DEBUG_MSG("S is down - Move down");
                movement->move_down = true;
            }
            else if (SDLK_d == event.key.keysym.sym)
            {
                DEBUG_MSG("D is down - Move right");
                movement->move_right = true;
            }
            else if (SDLK_w == event.key.keysym.sym)
            {
                DEBUG_MSG("W is down - Move up");
                movement->move_up = true;
            }
        }
        else if (SDL_KEYUP == event.type)
        {
            // std::cout << "Key is up" << std::endl;
            if (SDLK_a == event.key.keysym.sym)
            {
                DEBUG_MSG("A is up - Stop moving left");
                movement->move_left = false;
            }
            else if (SDLK_s == event.key.keysym.sym)
            {
                DEBUG_MSG("S is up - Stop moving down");
                movement->move_down = false;
            }
            else if (SDLK_d == event.key.keysym.sym)
            {
                DEBUG_MSG("D is up - Stop moving right");
                movement->move_right = false;
            }
            else if (SDLK_w == event.key.keysym.sym)
            {
                DEBUG_MSG("W is up - Stop moving up");
                movement->move_up = false;
            }
        }
    }
}

void Game::update()
{
    int startTicks = SDL_GetTicks();

    player.get()->update(alpha, *movement);
    
    for(auto& i : bullets)
    {
        if(i->getShooting())
            i->update();
    }

    for (auto& i : enemies)
    {
        if(i->getMoving())
        {
            i->setDirection(player.get()->getPos());
            i->update(alpha);
        }
    }
    
    int frameTicks = SDL_GetTicks() - startTicks;
    if (frameTicks < 1000 / window.getRefreshRate())
        SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
    
}

void Game::render()
{

    int startTicks = SDL_GetTicks();

    const float deltaTime = 0.01f;
    float accumulator = 0.0f;
    float currentTime = Utils::hireTimeInSeconds();
   
    
    float newTime = Utils::hireTimeInSeconds();
    float frameTime = newTime - currentTime;

    currentTime = newTime;

    accumulator += frameTime;

    while (accumulator >= deltaTime)
    {
        accumulator -= deltaTime;
    }

    alpha = accumulator / deltaTime;

    window.clear();

    window.render(0,0,backgroundTex);

    window.createText("Hello", { 255, 0, 0, 255});

    window.drawRectFromCenter(Vector2f(movement->mouse_x, movement->mouse_y),25,25);

    window.render(*std::make_unique<Entity>(Vector2f(0, 0), grassTexture));
    for(auto& i : bullets)
    {
        if(i->getShooting())
            window.render(*i);
    }

    window.render(*player.get());

    for (auto& i : enemies)
    {
        if(i->getMoving())
        {
            window.render(*i);
        }
    }

    window.display();
    int frameTicks = SDL_GetTicks() - startTicks;
    if (frameTicks < 1000 / window.getRefreshRate())
        SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
    
}

void Game::clean()
{
    window.cleanUp();
    delete movement;
    SDL_Quit();
}

bool Game::running()
{
    return gameRunning;
}

void Game::setScreenSize(Vector2f p_screenSize)
{
    screenSize = p_screenSize;
}

Vector2f Game::getScreenSize()
{
    return screenSize;
}

void Game::createEnemy()
{
    enemies.push_back(new Enemy(Utils::generateRandomLocation(), cobra));
}

void Game::createBullet(Vector2f pos)
{

    // std::cout << "Player width:" << player.get()->getCurrentFrame().w * player.get()->getScale().x
    //           << "Player height:" << player.get()->getCurrentFrame().h * player.get()->getScale().y;


    Bullet* bullet = new Bullet(Utils::getTextureCenter(player.get()->getTextureRect()), bulletTexture);
    bullet->setDirection(pos);
    bullet->setShootingPos(Utils::getTextureCenter(player.get()->getTextureRect()));
    bullet->setShooting(true);

    bullets.push_back(bullet);

    for (int i=0;i<bullets.size();++i) 
    {
        if (!bullets.at(i)->getShooting()) 
        {
            delete bullets.at(i); // Free memory allocated for the Bullet object
            bullets.erase(bullets.begin() + i); // Remove the element from the vector
            --i; // Update the loop variable as the vector size decreases
        }
    }
    
}