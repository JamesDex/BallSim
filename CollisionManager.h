//
// Created by Henry Cowsert on 3/4/24.
//

#ifndef BOUNCYBALL_COLLISIONMANAGER_H
#define BOUNCYBALL_COLLISIONMANAGER_H

#include "Ball.h"
#include <vector>

class CollisionManager {
private:


public:
    static void Balls();
    static bool checkCollision(Ball& ball1, Ball& ball2);
    static void handleCollision(Ball& ball1, Ball& ball2);
    static void handleBorderCollision(Ball &ball, sf::Vector2u windowSize);
};


#endif //BOUNCYBALL_COLLISIONMANAGER_H
