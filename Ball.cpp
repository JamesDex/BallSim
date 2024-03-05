
#include <iostream>
#include "Ball.h"
#include "Engine.h"
#include "CollisionManager.h"

Ball::Ball(float radius, sf::Vector2f position, sf::Vector2u windowSize) {

    shape.setRadius(radius);
    shape.setPosition(position);
    sf::Color color = sf::Color(rand() % 256,rand() % 256,rand() % 256);
    shape.setFillColor(color);
    shape.setOutlineThickness(1.9);
    shape.setOutlineColor(sf::Color::White);

    this->windowSize = windowSize;

    // SetGravity
    setGravity(0);

    // Damping Factor to simulate energy loss
    setDamping(0.999915f);

    // Mass of object relative to radius
    setMass(4.0f / 3.0f * 3.14159265359f * std::pow(radius, 3));

    // Set an initial velocity (you can adjust this)
    setVelocity(sf::Vector2f(1000, 200.0f));

}



Ball::Ball() {

}

Ball::~Ball() {

}

void Ball::update(float dt) {

    if (!grabbed) {

        shape.move(velocity * dt);

        // gravity
        velocity.y += gravity * dt;

        // TODO: damping is losing its effect the more balls put into the system. FIX
        velocity *= damping;
    }

    CollisionManager::handleBorderCollision(*this, windowSize);

}

void Ball::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}

void Ball::grabBall() {
    grabbed = true;
    velocity = sf::Vector2f(0.0f,0.0f);
}

void Ball::releaseBall() {
    grabbed = false;
}


// Getters

float Ball::getMass() const {
    return this->mass;
}

sf::CircleShape Ball::getShape() {
    return this->shape;
}

sf::Vector2f Ball::getPosition() {
    return this->shape.getPosition();
}

sf::Vector2f Ball::getVelocity() {
    return velocity;
}

float Ball::getDamping() const {
    return this->damping;
}

float Ball::getGravity() const {
    return this->gravity;
}

void Ball::getPositionToString() {
    float xPos = this->shape.getPosition().x;
    float yPos = this->shape.getPosition().y;
    std::cout << xPos << " " << yPos << "\n";
}

bool Ball::isGrabbed() {
    return grabbed;
}



// Setters

void Ball::setVelocity(sf::Vector2f newVelocity) {
    this->velocity = newVelocity;
}

void Ball::setPosition(sf::Vector2f position) {
    this->shape.setPosition(position);
}

void Ball::setShape(const sf::CircleShape &shape) {
    Ball::shape = shape;
}

void Ball::setDamping(float damping) {
    Ball::damping = damping;
}

void Ball::setMass(float mass) {
    Ball::mass = mass;
}

void Ball::setGravity(float newGravity) {
    this->gravity = newGravity;
}



