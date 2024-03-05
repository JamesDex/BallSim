
#include "../include/Engine.h"
#include "../include/CollisionManager.h"

// Constructor & Destructor
Engine::Engine() {
    this->initVariables();
    this->initWindow();
    this->initText();
}

Engine::~Engine() {
    delete this->window;
}

// Functions
void Engine::update() {

    this->dt = clock.restart().asSeconds();

    pollEvents();
    updateBalls(this->dt);
    checkBallCollisions();

}

void Engine::render() {

    this->window->clear();
    //

    renderFPSToScreen();
    renderBalls();

    //
    this->window->display();
}

void Engine::pollEvents() {

    while (this->window->pollEvent(this->event)) {

        switch (this->event.type) {
            case sf::Event::Closed:
                this->window->close();
                break;

            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Space) {
                    this->spawnBall();
                } else if (this->event.key.code == sf::Keyboard::Q) {
                    this->clearBalls();
                } else if (this->event.key.code == sf::Keyboard::G) {
                    toggleGravity();
                }
                break;

            case sf::Event::MouseButtonPressed:
                if (this->event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*this->window));

                }
        }
    }
}

void Engine::updateBalls(float time) {
    for (auto& ball : this->balls) {
        ball.update(time);
    }
}

void Engine::renderBalls() {
    for (auto& ball : this->balls) {
        ball.render(*this->window);
    }
}

void Engine::spawnBall() {

    float radius = std::rand() % 10 + 15;
    //std::rand() %  int
    this->balls.emplace_back(Ball(radius, sf::Vector2f(100, 200), getWindowSize()));
}

void Engine::clearBalls() {
    this->balls.clear();
}

void Engine::toggleGravity() {

    if (isGravityEnabled) {
        // Disable gravity for all balls
        for (auto& ball : this->balls) {
            ball.setGravity(0);
        }
        isGravityEnabled = false;
    } else {
        // Enable gravity for all balls
        for (auto& ball : this->balls) {
            ball.setGravity(gravity);
        }
        isGravityEnabled = true;
    }
}

// TODO: Move this to Collision Manager
void Engine::checkBallCollisions() {
    for (int i = 0; i < balls.size(); ++i) {
        for (int j = i + 1; j < balls.size(); ++j) {
            if (CollisionManager::checkCollision(balls[i], balls[j])) {
                // Handle collision (e.g., swap velocities)
                CollisionManager::handleCollision(balls[i], balls[j]);
            }
        }
    }
}

bool Engine::isRunning() const {
    return this->window->isOpen();
}

void Engine::initVariables() {
    this->window = nullptr;
}

void Engine::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "BouncyBall", sf::Style::Titlebar | sf::Style::Close);
}

void Engine::initText() {
    if (!textFont.loadFromFile("Assets/Fonts/arial.ttf")) {
        // Handle font loading error
        std::cerr << "Check file path";
    }
    fpsText.setFont(textFont);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::White);
}

void Engine::renderFPSToScreen() {
    std::ostringstream oss;
    float fps = 1 / dt;
    oss << "FPS: " << static_cast<int>(fps);
    fpsText.setString(oss.str());
    this->window->draw(fpsText);
}

sf::RenderWindow& Engine::getWindow() {
    return *this->window;
}

sf::Vector2u Engine::getWindowSize() {
    return getWindow().getSize();
}




