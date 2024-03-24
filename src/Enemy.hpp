#pragma once

#include "Entity.hpp"
#include "Utils.hpp"

#define         ENEMY_SPEED         2

class Enemy : public Entity
{
    public:
        Enemy(Vector2f p_pos, SDL_Texture* p_tex);
        ~Enemy();
        Vector2f getVelocity();
        void setVelocity(Vector2f p_velocity);
        void setDirection(Vector2f p_direction);
        void setMoving(bool p_moving);
        bool getMoving(){return moving;}
        void update(float deltaTime);
        
    private:
        Vector2f pos;
        Vector2f velocity;
        Vector2f direction;
        bool moving;


};