#include "EnemyBullet.h"

// Initialize member
sf::Texture EnemyBullet::texture;

void EnemyBullet::loadTexture() {
    if (!texture.loadFromFile("C:\\Users\\jablo\\Desktop\\enemybullet.png")) {
        std::cerr << "Error loading enemy bullet texture" << std::endl;
    }
}

EnemyBullet::EnemyBullet(const sf::Vector2f& startPosition){

    if (texture.getSize().x == 0) { // Ensure texture is loaded
        loadTexture();
    }

    sprite.setTexture(texture); // Set texture using static method
    sprite.setPosition(startPosition);
    sprite.setScale(0.03f, 0.03f); // Adjust scale as needed
}

void EnemyBullet::update(sf::Time dt){
    // Check the speed value and the delta time to ensure no anomalies
    if (dt.asSeconds() <= 0.f) {
        std::cerr << "Error: dt is zero or negative!" << std::endl;
        return;
    }

    float bulletSpeed = 400.f;

    sprite.move(0.f, bulletSpeed * dt.asSeconds()); // Move the bullet downwards

    // Boundary check to ensure the bullet stays within the screen limits
    if (sprite.getPosition().y > 1000) { // Adjust screen height
        std::cerr << "Bullet went off-screen!" << std::endl;
        // Code to handle bullet removal or reset
    }
}

void EnemyBullet::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool EnemyBullet::isOffScreen() const {
    return sprite.getPosition().y > 800; // Assuming screen height is 800
}

const sf::FloatRect EnemyBullet::getBounds() const {
    return sprite.getGlobalBounds();
}
