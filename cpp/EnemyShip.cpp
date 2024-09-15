#include "EnemyShip.h"

EnemyShip::EnemyShip(const sf::Vector2f& startPosition, const std::string& texturePath)
    : Ship(startPosition, texturePath) {

    sprite.setScale(0.1f, 0.1f);
    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(0)));

    movementDirection = (std::rand() % 2 == 0) ? 1.f : -1.f; // 50% chance to start moving left or right
    movementDirectionY = (std::rand() % 2 == 0) ? 1.f : -1.f; // 50% chance to start moving up or down
    // Randomize initial position
    sprite.setPosition(
        static_cast<float>(std::rand() % 800), // Random x position
        static_cast<float>(std::rand() % 100));     // Random y position on top


}

// Modify the EnemyShip::update method
void EnemyShip::update(sf::Time dt) {
    // Adjust speed and direction
    float speed = 100.f * dt.asSeconds(); // Adjust speed as needed

    sprite.move(movementDirection * speed, 0.4f * movementDirectionY * speed);  //Moving EnemyShip diagonally

    // Check for screen boundaries and bounce back if necessary
    if (sprite.getPosition().x <= 0) {
        // Reverse direction when hitting the left boundary
        movementDirection = 1.f;
    } else if (sprite.getPosition().x + sprite.getGlobalBounds().width >= 1000) {
        // Reverse direction when hitting the right boundary
        movementDirection = -1.f;
    }
    if (sprite.getPosition().y <= 0) {
        // Reverse direction when hitting the top boundary
        movementDirectionY = 1.f;
    } else if (sprite.getPosition().y + sprite.getGlobalBounds().height >= 200) {
        // Reverse direction when hitting the bottom boundary
        movementDirectionY = -1.f;

    }

    // Shooting bullets when shoot interval has passed
    if (shootClock.getElapsedTime() >= shootInterval) {
        shoot();
        shootClock.restart();
    }

    for (auto it = enemybullets.begin(); it != enemybullets.end(); ) {
        it->update(dt);
        if (it->isOffScreen()) {
            it =enemybullets.erase(it); //Remove bullets that are off-screen
        }
        else {
            ++it;
        }
    }

    for(auto& bullet: enemybullets) {
        bullet.update(dt); // Update each bullet to move it downwar
    }
}

void EnemyShip::draw (sf::RenderWindow& window) const {
    Ship::draw(window); // Draw the ship
    // Draw all bullets
    for (const auto& bullet :enemybullets){
        bullet.draw(window);
    }
}

void EnemyShip::shoot() {
    sf::Vector2f bulletStartPosition = sprite.getPosition();   // Get the position of the enemy ship

    // Spawn the bullet
    enemybullets.emplace_back(sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2 - 2.5f, sprite.getGlobalBounds().height));
}

std::vector<EnemyBullet>* EnemyShip:: hantleTheContainerOnEnemyBullets(){
    return &enemybullets;
}

std::vector<EnemyBullet>& EnemyShip::getBullets() {
    return enemybullets;
}
