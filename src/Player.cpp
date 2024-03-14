#include "Player.hpp"

Player::Player(Vector2f p_pos, SDL_Texture *p_tex) 
: Entity(p_pos, p_tex)
{
    pos = p_pos;
    setVelocity(Vector2f(1,1));
    setScale(1,1);
}

void Player::setVelocity(Vector2f p_velocity)
{
    velocity = p_velocity;
}

Vector2f Player::getVelocity()
{
    return velocity;
}

float Player::rotate(Vector2f p2)
{
    int DeltaX;
    int DeltaY;

    DeltaX = getPos().x - p2.x;
    DeltaY = getPos().y - p2.y;

    return  (std::atan2(-DeltaX, DeltaY) * 180.00000) / 3.141592;
}

void Player::update(float deltaTime, PlayerMovement movement)
{
    
    float speed = 3.0f;
    
    if(movement.move_up)
    {
        setPos(getPos().x, getPos().y - getVelocity().y * speed);
    }
    if(movement.move_right)
    {
        setPos(getPos().x + getVelocity().x * speed, getPos().y);
    }
    if(movement.move_left)
    {
        setPos(getPos().x - getVelocity().x * speed, getPos().y);
    }
    if(movement.move_down)
    {
        setPos(getPos().x, getPos().y + getVelocity().y * speed);
    }
    
    // Get the angle of the 2D vector
    float angle = rotate(Vector2f(movement.mouse_x, movement.mouse_y));    
    setAngle(angle);
     
}