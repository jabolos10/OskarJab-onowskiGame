#include "EnemyShip2.h"

EnemyShip2::EnemyShip2(const sf::Vector2f& startPosition, const std::string& texturePath)
    : Ship(startPosition, texturePath) {

    sprite.setScale(0.2f, 0.2f);
    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(0)));

    movementDirection2 = (std::rand() % 2 == 0) ? 1.f : -1.f; // 50% chance to start moving left or right

    // Randomize initial position
    sprite.setPosition(
        static_cast<float>(std::rand() % 1000), // Random x position
        static_cast<float>(std::rand() % 100)   // Random y position on top
        );
}

void EnemyShip2::update(sf::Time dt) {
    // Adjust speed and direction
    float speed = 50.f * dt.asSeconds(); // Adjust speed as needed

    // Move the enemy ship based on its current direction
    sprite.move(movementDirection2 * speed, 0.f);

    // Check for screen boundaries and bounce back if necessary
    if (sprite.getPosition().x <= 0) {
        // Reverse direction when hitting the left boundary
        movementDirection2 = 1.f;
    }
    else if (sprite.getPosition().x + sprite.getGlobalBounds().width >= 1000) {
        // Reverse direction when hitting the right boundary
        movementDirection2 = -1.f;
    }

    if (shootClock.getElapsedTime() >= shootInterval) {
        shoot();
        shootClock.restart();
    }

    for(auto& bullet: enemybullets2) {
        bullet.update(dt); // Update each bullet to move it diagonally
    }

    for(auto& bulletR: enemybullets2Reverse) {
        bulletR.update(dt); // Update each bullet to move it diagonally
    }


}

void EnemyShip2::draw(sf::RenderWindow& window) const {
    Ship::draw(window); // Draw the ship
    // Draw all bullets
    for (const auto& bullet :enemybullets2){
        bullet.draw(window);
    }

    for (const auto& bullet2 :enemybullets2Reverse){
        bullet2.draw(window);
    }
}

void EnemyShip2::shoot() {
    // Spawn the bullet
    enemybullets2.emplace_back(sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2 + 2.5f, sprite.getGlobalBounds().height));
    enemybullets2Reverse.emplace_back(sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2 - 2.5f, sprite.getGlobalBounds().height));

}


std::vector<EnemyBullet2>* EnemyShip2:: hantleTheContainerOnEnemyBullets2(){
    return &enemybullets2;
}

std::vector<EnemyBullet2Reverse>* EnemyShip2:: hantleTheContainerOnEnemyBullets2Reverse(){
    return &enemybullets2Reverse;
}

std::vector<EnemyBullet2>& EnemyShip2::getBullets() {
    return enemybullets2;
}

std::vector<EnemyBullet2Reverse>& EnemyShip2::getBulletsReverse() {
    return enemybullets2Reverse;
}


void EnemyShip2::takeDamage() {
    if (hitCount < maxHits) {
        hitCount++; // Increment the hit counter when the ship is hit
    }
}

bool EnemyShip2::isDestroyed() const {
    return hitCount >= maxHits; // Return true if the ship is hit three times
}

