#include "Enemy.hpp"

#define         ENEMY_SPEED         2

Enemy::Enemy(Vector2f p_pos, SDL_Texture *p_tex) 
: Entity(p_pos, p_tex)
{
    pos = p_pos;
    setVelocity(Vector2f(1,1));
    setScale(0.4,0.4);
    setMoving(true);
}

Enemy::~Enemy()
{
    std::cout << "Enemy deleted" << std::endl;
}

void Enemy::setVelocity(Vector2f p_velocity)
{
    velocity = p_velocity;
}

Vector2f Enemy::getVelocity()
{
    return velocity;
}

void Enemy::setDirection(Vector2f p_direction)
{
    direction = p_direction;
}

void Enemy::setMoving(bool p_moving)
{
    moving = p_moving;
}

void Enemy::update(float deltaTime)
{
    
    if (moving) 
    {
        float x = ((getPos().x - direction.x) / Utils::distance(getPos().x, getPos().y, direction.x, direction.y)*ENEMY_SPEED);
        float y = ((getPos().y - direction.y) / Utils::distance(getPos().x, getPos().y, direction.x, direction.y)*ENEMY_SPEED);
        
        float angle = rotate(Vector2f(direction.x, direction.y));    
        setAngle(angle);

        setPos(getPos().x - x, getPos().y - y);

        //is bullet already on the target
        // if(abs(getPos().x - direction.x) < 0.5f || abs(getPos().y - direction.y) < 0.5)
        // {
        //     std::cout << "Shooting false" << std::endl;
        //     shooting = false;
        // }
    }
     
}