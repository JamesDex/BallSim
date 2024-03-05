
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>


#ifndef BOUNCYBALL_BALL_H
#define BOUNCYBALL_BALL_H


class Ball {
private:

// Variables
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float damping;
    float mass;
    float gravity;
    bool grabbed = false;
    sf::Vector2u windowSize;


    // Functions
    void initShape();
    void initVariables();

public:

    // Constructors & Destructors
    Ball(float radius, sf::Vector2f position, sf::Vector2u windowSize);
    Ball();

    virtual ~Ball();

    // Functions
    void update(float dt);
    void render(sf::RenderTarget& target);
    void grabBall();
    void releaseBall();
    bool isGrabbed();



    // Setters and Getters
    void setVelocity(sf::Vector2f Velocity);
    void setPosition(sf::Vector2f position);
    void setShape(const sf::CircleShape &shape);
    void setDamping(float damping);
    void setMass(float mass);
    void setGravity(float newGravity);

    sf::Vector2f getPosition();
    sf::Vector2f getVelocity();
    float getDamping() const;
    float getMass() const;
    float getGravity() const;
    sf::CircleShape getShape();
    void getPositionToString();

};


#endif //BOUNCYBALL_BALL_H
