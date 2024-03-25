#include "RenderWindow.hpp"
#include <iostream>


RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                p_w, p_h,SDL_WINDOW_SHOWN);


    if(window == NULL)
    {
        std::cout << "Window Failed to open" << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );


}

SDL_Texture* RenderWindow::loadTexture(const char *p_filePath)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if(texture == NULL)
        std::cout << "Failed to load texture" << SDL_GetError() << std::endl;

    return texture;
}

int RenderWindow::getRefreshRate()
{
    int displayindex = SDL_GetWindowDisplayIndex(window);

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayindex, 0, &mode);

    return mode.refresh_rate;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::createText(const char* Message)
{
    
    const char* FONT_NAME = "../fonts/PressStart2P-Regular.ttf";
    const int FONT_SIZE = 25;
    TTF_Font* Font; // The font to be loaded from the ttf file.
    SDL_Surface* TextSurface; // The surface necessary to create the font texture.
    SDL_Texture* TextTexture; // The font texture prepared for render.
    SDL_Color TextColor = { 255, 0, 0, 255}; // Red SDL color.

    TTF_Init();
    
    TTF_Font *font = TTF_OpenFont(FONT_NAME, FONT_SIZE);
    
    if (!font)
        std::cout << "Couldn't find/init open ttf font." << std::endl;
    
    TextSurface = TTF_RenderText_Solid(font, Message, TextColor);
    TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
    
    render(10, HEIGHT - FONT_SIZE - 5, TextTexture);
    
    // After you create the texture you can release the surface memory allocation because we actually render the texture not the surface.
    SDL_FreeSurface(TextSurface);
    
    TTF_Quit();

}

void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src; 
	src.x = p_entity.getCurrentFrame().x;
    src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
    dst.x = p_entity.getPos().x;
    dst.y = p_entity.getPos().y;
    dst.w = p_entity.getCurrentFrame().w * p_entity.getScale().x;
    dst.h = p_entity.getCurrentFrame().h * p_entity.getScale().y;

	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, p_entity.getAngle(), 0, SDL_FLIP_NONE);
}

void RenderWindow::renderCenter(float p_x, float p_y, Entity& p_entity)
{
    SDL_Rect src; 
	src.x = 0;
    src.y = 0;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
    dst.x = WIDTH / 2 - p_entity.getCurrentFrame().w / 2 + p_x;
    dst.y = HEIGHT /2 - p_entity.getCurrentFrame().h / 2 + p_y;
    dst.w = p_entity.getCurrentFrame().w * p_entity.getScale().x;
    dst.h = p_entity.getCurrentFrame().h * p_entity.getScale().y;

	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, p_entity.getAngle(), 0, SDL_FLIP_NONE);
}

void RenderWindow::render(int x, int y, SDL_Texture* p_tex)
{
    SDL_Rect src; 
	src.x = 0;
    src.y = 0;
	src.w;
	src.h;

    SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = src.w;
    dst.h = src.h;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void RenderWindow::drawRect(SDL_Rect rect)
{
    //SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderDrawRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //SDL_RenderPresent(renderer);

}

void RenderWindow::drawRect(Vector2f pos)
{
    SDL_Rect dst;
    dst.x = pos.x;
    dst.y = pos.y;
    dst.w = 25;
    dst.h = 25;

    //SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_RenderDrawRect(renderer, &dst);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //SDL_RenderPresent(renderer);
}

void RenderWindow::drawRectFromCenter(Vector2f center, int width, int height) {
    SDL_Rect rectangle;

    // Calculate top-left corner coordinates
    rectangle.x = center.x - width / 2;
    rectangle.y = center.y - height / 2;

    // Set dimensions
    rectangle.w = width;
    rectangle.h = height;

    drawRect(rectangle);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}