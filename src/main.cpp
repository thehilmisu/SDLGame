#include "Game.hpp"


std::unique_ptr<Game> game = nullptr;

int main(int argc, char *argv[])
{
    game = std::make_unique<Game>();

    while(game.get()->running())
    {
     
        game.get()->handleEvents();
        game.get()->update();
        game.get()->render();
        
    }

    game.get()->clean();
    

    return 0;
}
