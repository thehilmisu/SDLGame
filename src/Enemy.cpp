#include "Enemy.hpp"

Enemy::Enemy(Vector2f p_pos, SDL_Texture *p_tex) 
: Entity(p_pos, p_tex)
{
    pos = p_pos;
    setVelocity(Vector2f(1,1));
    setScale(1,1);
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
        int dx = direction.x - getPos().x;
        int dy = direction.y - getPos().y;
        float distance = std::sqrt(dx * dx + dy * dy);

        float unitX = dx / distance;
        float unitY = dy / distance;

        float _x = getPos().x + static_cast<int>(unitX * ENEMY_SPEED);
        float _y = getPos().y + static_cast<int>(unitY * ENEMY_SPEED);

        float angle = rotate(Vector2f(direction.x, direction.y));    
        setAngle(angle);

        setPos(_x,_y);

        //is bullet already on the target
        // if(abs(getPos().x - direction.x) < 0.5f || abs(getPos().y - direction.y) < 0.5)
        // {
        //     std::cout << "Shooting false" << std::endl;
        //     shooting = false;
        // }
    }
     
}