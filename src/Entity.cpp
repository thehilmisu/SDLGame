#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

void Entity::update(double deltaTime)
{

}

float Entity::rotate(Vector2f p2)
{
    int DeltaX;
    int DeltaY;

    DeltaX = getPos().x - p2.x;
    DeltaY = getPos().y - p2.y;

    return  (std::atan2(-DeltaX, DeltaY) * 180.00000) / 3.141592;
}

void Entity::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void Entity::setAngle(float p_angle)
{
	angle = p_angle;
}

void Entity::setScale(float w, float h)
{
	scale.x = w;
	scale.y = h;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

void Entity::setCurrentFrame(SDL_Rect p_frame)
{	
	currentFrame = p_frame;

	SDL_QueryTexture(getTex(), NULL, NULL, &currentFrame.w, &currentFrame.h);
}