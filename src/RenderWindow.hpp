#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"
#include "Utils.hpp"


class RenderWindow
{
    public:
        RenderWindow(const char *p_title, int p_w, int p_h);
        SDL_Texture *loadTexture(const char *p_filePath);
        int getRefreshRate();
        void cleanUp();
        void clear();
        void render(Entity &p_entity);
        void render(int x, int y, SDL_Texture* p_tex);
        void renderCenter(float p_x, float p_y, Entity& p_entity);
        void display();
        void drawRect(SDL_Rect rect);
        void drawRect(Vector2f pos);
        void drawRectFromCenter(Vector2f center, int width, int height);
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;

};