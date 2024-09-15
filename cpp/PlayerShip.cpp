#include "PlayerShip.h"

PlayerShip::PlayerShip(const sf::Vector2f& startPosition)
    : Ship(startPosition, "C:\\Users\\jablo\\Desktop\\premiumspaceship.png"), health(100.0f), maxHealth(100.0f), healthBar(startPosition.x, startPosition.y + 50, 100, 10) { // Initial position just below the ship {
    sprite.setScale(0.2f, 0.2f);
    // Initialize health bar
    healthBarBackground.setSize(sf::Vector2f(healthBarlength, healthBarHeight)); // Size of the red  healthbar
    healthBarBackground.setFillColor(sf::Color::Red);

    healthBarForeground.setSize(sf::Vector2f(healthBarlength, healthBarHeight)); // Size of the green healthbar
    healthBarForeground.setFillColor(sf::Color::Green);
}

void PlayerShip::update(sf::Time dt) {


    // Get the current position of the sprite
    sf::Vector2f currentPosition = sprite.getPosition();

    // Movement handling with boundary checks using &&
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && currentPosition.x > 0) {
        sprite.move(-800.f * dt.asSeconds(), 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && currentPosition.x + sprite.getGlobalBounds().width < 1000) {
        sprite.move(800.f * dt.asSeconds(), 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && currentPosition.y > 0) {
        sprite.move(0.f, -800.f * dt.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currentPosition.y + sprite.getGlobalBounds().height < 800) {
        sprite.move(0.f, 800.f * dt.asSeconds());
    }


    // Shooting bullets when spacebar is pressed and shoot interval has passed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootClock.getElapsedTime() >= shootInterval) {
        shoot();
        shootClock.restart();
    }

    // Update all bullets
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->update(dt);
        if (it->isOffScreen()) {
            it = bullets.erase(it); // Remove bullets that are off-screen
        }
        else {
            ++it;
        }
    }
    updateHealthBar();
}

void PlayerShip::draw(sf::RenderWindow& window) const {
    Ship::draw(window); // Draw the ship
    // Draw all bullets
    for (const auto& bullet : bullets) {
        bullet.draw(window);
    }

    window.draw(healthBarBackground);
    window.draw(healthBarForeground);
}

void PlayerShip::shoot() {
    // Create a new bullet at the current position of the ship
    bullets.emplace_back(sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2, 0));
}

std::vector<Bullet>* PlayerShip::handleToContainerOnBullets() {
    return &bullets;
}

void PlayerShip::increaseHealth(float healthPoints){
    health += healthPoints;  // Add health points


    if (health > maxHealth) {  // Ensure health does not exceed maximum health
        health = maxHealth;
    }
    updateHealthBar();
}

void PlayerShip::takeDamage(float damage) {

    health -= damage;
    if (health < 0) {
        health = 0;
    }

}

bool PlayerShip::isDestroyed() const {
    return health <= 0;
}

float PlayerShip::getHealth() const {
    return health;
}

float PlayerShip::getMaxHealth() const {
    return maxHealth;
}

void PlayerShip::updateHealthBar() {
    // Get the current position of the sprite
    sf::Vector2f currentPosition = sprite.getPosition();

    // Position the health bar just below the ship
    healthBarBackground.setPosition(
        currentPosition.x + (sprite.getGlobalBounds().width / 2) - (healthBarBackground.getSize().x / 2),
        currentPosition.y + sprite.getGlobalBounds().height + 10.0f
        );
    healthBarForeground.setPosition(healthBarBackground.getPosition());

    // Adjust the green bar to match the current health percentage
    float healthPercentage = health / maxHealth;
    healthBarForeground.setSize(sf::Vector2f(healthBarlength * healthPercentage, healthBarHeight));
}
