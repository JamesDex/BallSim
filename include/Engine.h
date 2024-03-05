
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "Ball.h"
#include <iostream>
#include "sstream"

#ifndef BOUNCYBALL_ENGINE_H
#define BOUNCYBALL_ENGINE_H


class Engine {
private:
    // Variables
    sf::RenderWindow* window;
    sf::Event event;

    sf::VideoMode videoMode;
    sf::Clock clock;
    sf::Font textFont;
    sf::Text fpsText;


    float dt;
    bool isGravityEnabled = false;
    float gravity = 1000.0f;

    // Container
    std::vector<Ball> balls;

    // Functions
    void initVariables();
    void initWindow();
    void renderFPSToScreen();
    void initText();

public:
    // Constructors & Destructors
    Engine();
    virtual ~Engine();

    // Getters
    bool isRunning() const;

    // Functions
    void update();
    void render();
    void pollEvents();
    void updateBalls(float dt);
    void renderBalls();
    void spawnBall();
    void clearBalls();
    void toggleGravity();

    // Setters and Getters
    sf::RenderWindow& getWindow();
    sf::Vector2u getWindowSize();
};


#endif //BOUNCYBALL_ENGINE_H
