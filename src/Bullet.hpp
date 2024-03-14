#pragma once 

#include <math.h>  
#include "Entity.hpp"

class Bullet : public Entity
{
    public:
        Bullet(Vector2f p_pos, SDL_Texture* p_tex);
        Vector2f getVelocity();
        void setVelocity(Vector2f p_velocity);
        void setDirection(Vector2f p_direction);

        void update(float deltaTime);
        
    private:
        Vector2f pos;
        Vector2f velocity;
        Vector2f direction;
        float rotate(Vector2f p2);
};