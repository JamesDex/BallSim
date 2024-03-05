
#include <cmath>
#include "../include/Ball.h"
#include "../include/CollisionManager.h"
#include "../include/Engine.h"


bool CollisionManager::checkCollision(Ball &ball1, Ball &ball2) {

    // Pythagorean theorem
    float distance = std::hypot(ball1.getShape().getPosition().x - ball2.getShape().getPosition().x,
                                ball1.getShape().getPosition().y - ball2.getShape().getPosition().y);

    return distance < ball1.getShape().getRadius() + ball2.getShape().getRadius();
}

void CollisionManager::handleCollision(Ball &ball1, Ball &ball2) {

    sf::Vector2f pos1 = ball1.getPosition();
    sf::Vector2f pos2 = ball2.getPosition();

    // Calculate the normalized collision normal (direction from ball2 to ball1)
    sf::Vector2f collisionNormal = sf::Vector2f(pos1 - pos2);
    float collisionDistance = std::hypot(collisionNormal.x, collisionNormal.y);

    // Ensure collisionDistance is not zero to avoid division by zero
    if (collisionDistance > 0.0f) {
        collisionNormal /= collisionDistance;
    }

    // Calculate the minimum separation distance
    float overlap = ball1.getShape().getRadius() + ball2.getShape().getRadius() - collisionDistance;

    // Separate the balls along the collision normal
    pos1 += 0.5f * overlap * collisionNormal;
    pos2 -= 0.5f * overlap * collisionNormal;

    ball1.setPosition(pos1);
    ball2.setPosition(pos2);

    sf::Vector2f v1 = ball1.getVelocity();
    sf::Vector2f v2 = ball2.getVelocity();

    // Calculate relative velocity
    sf::Vector2f relativeVelocity = v1 - v2;

    // Calculate impulse (change in velocity) based on the collision normal and relative velocity
    float impulse = 2.0f * (relativeVelocity.x * collisionNormal.x + relativeVelocity.y * collisionNormal.y) /
                    (ball1.getMass() + ball2.getMass());

    // Apply the impulse to update the velocities
    v1 -= impulse * ball2.getMass() * collisionNormal;
    v2 += impulse * ball1.getMass() * collisionNormal;

    // Set the new velocities for both balls
    ball1.setVelocity(v1);
    ball2.setVelocity(v2);

//     Apply damping to simulate more realistic physics
    for (int i = 0; i < 100; i++) {
        ball1.setVelocity(ball1.getVelocity() * ball1.getDamping());
        ball2.setVelocity(ball2.getVelocity() * ball2.getDamping());
    }
}


// TODO: The balls stick in the walls. FIX
void CollisionManager::handleBorderCollision(Ball &ball, sf::Vector2u windowSize) {

    sf::Vector2f position = ball.getShape().getPosition();
    sf::Vector2f velocity = ball.getVelocity();
    float radius = ball.getShape().getRadius();
    float diameter = radius + radius;

    // Left boundary
    if (position.x < 0) {
        position.x = 0;
        velocity.x = -velocity.x;
        ball.setVelocity(velocity); // Reverse the horizontal velocity
    }

    // Right boundary
    if (position.x + diameter > windowSize.x) {
        position.x = windowSize.x - diameter;
        velocity.x = -velocity.x;  // Reverse the horizontal velocity
        ball.setVelocity(velocity);
    }

    // Top boundary
    if (position.y < 0) {
        position.y = 0;
        velocity.y = -velocity.y;  // Reverse the vertical velocity
        ball.setVelocity(velocity);
    }

    // Bottom boundary
    if (position.y + diameter > windowSize.y) {
        position.y = windowSize.y -  diameter;
        velocity.y = -velocity.y;  // Reverse the vertical velocity
        ball.setVelocity(velocity);
    }

    ball.setPosition(position);
}
