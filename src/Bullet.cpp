#include "Bullet.hpp"
#include "Utils.hpp"

#define     SCREEN_WIDTH    1280
#define     SCREEN_HEIGHT   720
#define     BULLET_SPEED    8

Bullet::Bullet(Vector2f p_pos, SDL_Texture* p_tex)
: Entity(p_pos, p_tex)
{
    pos = p_pos;
    setScale(0.20f, 0.20f);
    setVelocity(Vector2f(1,1));
}

Bullet::~Bullet()
{
    std::cout << "Bullet deleted" << std::endl;
}

Vector2f Bullet::getVelocity()
{
    return velocity;
}

void Bullet::setVelocity(Vector2f p_velocity)
{
    velocity = p_velocity;
}

void Bullet::setDirection(Vector2f p_direction)
{
    direction = p_direction;
}

void Bullet::setShooting(bool p_shooting)
{
    shooting = p_shooting;
}

bool Bullet::getShooting()
{
    return shooting;
}

void Bullet::setShootingPos(Vector2f p_shootingPos)
{
    shootingPos = p_shootingPos;
}

void Bullet::update(float deltaTime)
{

    if (shooting) 
    {
        float x = ((shootingPos.x - direction.x) / Utils::distance(shootingPos.x, shootingPos.y, direction.x, direction.y)*BULLET_SPEED);
        float y = ((shootingPos.y - direction.y) / Utils::distance(shootingPos.x, shootingPos.y, direction.x, direction.y)*BULLET_SPEED);
        
        float angle = rotate(Vector2f(direction.x, direction.y));    
        setAngle(angle);

        setPos(getPos().x - x, getPos().y - y);

        if(Utils::isOutOfBounds(getPos()))
        {
            shooting = false;
        }

    }

}