#include "Bullet.hpp"

#define     SCREEN_WIDTH    1280
#define     SCREEN_HEIGHT   720
#define     BULLET_SPEED    6

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

float Bullet::rotate(Vector2f p2)
{
    int DeltaX;
    int DeltaY;

    DeltaX = getPos().x - p2.x;
    DeltaY = getPos().y - p2.y;

    return  (std::atan2(-DeltaX, DeltaY) * 180.00000) / 3.141592;
}

void Bullet::update(float deltaTime)
{
    if (shooting) 
    {
        int dx = direction.x - getPos().x;
        int dy = direction.y - getPos().y;
        float distance = std::sqrt(dx * dx + dy * dy);

        float unitX = dx / distance;
        float unitY = dy / distance;

        float _x = getPos().x + static_cast<int>(unitX * BULLET_SPEED);
        float _y = getPos().y + static_cast<int>(unitY * BULLET_SPEED);

        float angle = rotate(Vector2f(direction.x, direction.y));    
        setAngle(angle);

        setPos(_x,_y);

        //is bullet out of bounds?
        if (getPos().x < 0 || getPos().x > SCREEN_WIDTH || getPos().y < 0 || getPos().y > SCREEN_HEIGHT) 
        {
            shooting = false;
        }

        //is bullet already on the target
        if(abs(getPos().x - direction.x) < 0.5f || abs(getPos().y - direction.y) < 0.5)
        {
            std::cout << "Shooting false" << std::endl;
            shooting = false;
        }
    }

}