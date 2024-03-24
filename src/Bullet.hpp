#pragma once 

#include <cmath>
#include "Entity.hpp"

class Bullet : public Entity
{
    public:
        Bullet(Vector2f p_pos, SDL_Texture* p_tex);
        ~Bullet();
        Vector2f getVelocity();
        void setVelocity(Vector2f p_velocity);
        void setDirection(Vector2f p_direction);
        void setShooting(bool p_shooting);
        void setShootingPos(Vector2f p_shootingPos);
        bool getShooting();
        void update();
        
    private:
        Vector2f pos;
        Vector2f velocity;
        Vector2f direction;
        Vector2f shootingPos;
        bool shooting;
};