#include "EnemyBullet2.h"


sf::Texture EnemyBullet2::texture; // Initialize static member

void EnemyBullet2::loadTexture() {
    if (!texture.loadFromFile("C:\\Users\\jablo\\Desktop\\enemybullet2.png")) {
        std::cerr << "Error loading enemy bullet texture" << std::endl;
    }
}

EnemyBullet2::EnemyBullet2(const sf::Vector2f& startPosition){

    if (texture.getSize().x == 0) { // Ensure texture is loaded
        loadTexture();
    }

    sprite.setTexture(texture); // Set texture using static method
    sprite.setPosition(startPosition);
    sprite.setScale(0.06f, 0.06f); // Adjust scale as needed
}

void EnemyBullet2::update(sf::Time dt){
    // Check the speed value and the delta time to ensure no anomalies
    if (dt.asSeconds() <= 0.f) {
        std::cerr << "Error: dt is zero or negative!" << std::endl;
        return;
    }

    float bulletSpeed = 50.f;

    sprite.move( bulletSpeed * dt.asSeconds(), 2* bulletSpeed * dt.asSeconds()); // Move the bullet diagonally
}

void EnemyBullet2::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool EnemyBullet2::isOffScreen() const {
    return sprite.getPosition().y > 800; // Assuming screen height is 800
}

const sf::FloatRect EnemyBullet2::getBounds() const {
    return sprite.getGlobalBounds();
}
