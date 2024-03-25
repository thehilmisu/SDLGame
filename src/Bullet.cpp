#include "Bullet.hpp"
#include "Utils.hpp"

#define     BULLET_SPEED    15

Bullet::Bullet(Vector2f p_pos, SDL_Texture* p_tex)
: Entity(p_pos, p_tex)
{
    pos = p_pos;
    setScale(0.10f, 0.10f);
    setVelocity(Vector2f(1,1));
    setShooting(false);
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
       
    setAngle(rotate(Vector2f(direction.x, direction.y)));
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

Vector2f Bullet::getShootingPos()
{
    return shootingPos;
}

void Bullet::update()
{
    
    if (shooting) 
    {
        float x = ((shootingPos.x - direction.x) / Utils::distance(shootingPos.x, shootingPos.y, direction.x, direction.y)*BULLET_SPEED);
        float y = ((shootingPos.y - direction.y) / Utils::distance(shootingPos.x, shootingPos.y, direction.x, direction.y)*BULLET_SPEED);
        
        setPos(getPos().x - x, getPos().y - y);

        if(Utils::isOutOfBounds(getPos()))
        {            
            static int deltaTime = 0;
            if(Utils::oneSecondFlag())
            {
                //setAngle(rotate(Vector2f(direction.x, direction.y)));
                //std::cout << "-" << std::endl;
                deltaTime++;
                if(deltaTime >= 1.0f)
                {
                    //std::cout << "it has been 3 seconds" << std::endl; 
                    deltaTime = 0;
                    shooting = false;
                }
                
            }
        }

    }

}