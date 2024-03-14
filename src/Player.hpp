#pragma once

#include <math.h>  
#include "Entity.hpp"


struct PlayerMovement
{
    int mouse_x, mouse_y;
    bool move_right = false;
    bool move_left = false;
    bool move_up = false;
    bool move_down = false;
};


class Player : public Entity
{
    public:
        Player(Vector2f p_pos, SDL_Texture* p_tex);
        Vector2f getVelocity();
        void setVelocity(Vector2f p_velocity);

        void update(float deltaTime, PlayerMovement movement);
        
    private:
        Vector2f pos;
        Vector2f velocity;
        float rotate(Vector2f p2);


};