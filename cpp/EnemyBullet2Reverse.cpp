#include "EnemyBullet2Reverse.h"

sf::Texture EnemyBullet2Reverse::texture; // Initialize member

void EnemyBullet2Reverse::loadTexture() {
    if (!texture.loadFromFile("C:\\Users\\jablo\\Desktop\\enemybullet2reverse.png")) {
        std::cerr << "Error loading enemy bullet texture" << std::endl;
    }

}

EnemyBullet2Reverse::EnemyBullet2Reverse(const sf::Vector2f& startPosition){

    if (texture.getSize().x == 0) { // Ensure texture is loaded
        loadTexture();
    }

    sprite.setTexture(texture); // Set texture using static method
    sprite.setPosition(startPosition);
    sprite.setScale(0.06f, 0.06f); // Adjust scale as needed
}

void EnemyBullet2Reverse::update(sf::Time dt){
    // Check the speed value and the delta time to ensure no anomalies
    if (dt.asSeconds() <= 0.f) {
        std::cerr << "Error: dt is zero or negative!" << std::endl;
        return;
    }

    float bulletSpeed = 50.f;

    sprite.move( -bulletSpeed * dt.asSeconds(), 2* bulletSpeed * dt.asSeconds()); // Move the bullet diagonally
}

void EnemyBullet2Reverse::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool EnemyBullet2Reverse::isOffScreen() const {
    return sprite.getPosition().y > 800; // Assuming screen height is 800
}

const sf::FloatRect EnemyBullet2Reverse::getBounds() const {
    return sprite.getGlobalBounds();
}
