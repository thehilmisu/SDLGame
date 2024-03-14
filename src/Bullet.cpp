#include "Bullet.hpp"

Bullet::Bullet(Vector2f p_pos, SDL_Texture* p_tex)
: Entity(p_pos, p_tex)
{
    pos = p_pos;
    setScale(0.20f, 0.20f);
    setVelocity(Vector2f(1,1));
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

    float SPEED = 8.0f;

    int targetX = direction.x - getCurrentFrame().w / 2;
    int targetY = direction.y - getCurrentFrame().h / 2;

    // Calculate the distance between current and target position
    int dx = targetX - getPos().x;
    int dy = targetY - getPos().y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // Calculate the unit vector for direction
    float unitX = dx / distance;
    float unitY = dy / distance;
    bool isMoving2Target = true;
    // Move the texture towards the target position
    if (isMoving2Target) 
    {
        // if (distance <= SPEED) 
        // {
        //     setPos(targetX, targetY);
        //     isMoving2Target = false;
        // }

        setPos(getPos().x + static_cast<int>(unitX * SPEED), getPos().y 
                          + static_cast<int>(unitY * SPEED));

        distance -= SPEED;

        // Get the angle of the 2D vector
        float angle = rotate(Vector2f(direction.x, direction.y));    
        setAngle(angle);
    }

}