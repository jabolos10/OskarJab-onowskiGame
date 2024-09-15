#include "Bullet.h"

// Define the static texture variable
sf::Texture Bullet::texture;

// Load the texture once for all bullets
void Bullet::loadTexture() {
    if (!texture.loadFromFile("C:\\Users\\jablo\\Desktop\\bullet1.png")) { // Path to bullet image
        // Handle error
        std::cerr << "Error loading bullet texture" << std::endl;
    }
}

Bullet::Bullet(const sf::Vector2f& startPosition) {
    if (texture.getSize().x == 0) { // Check if texture is loaded only once
        loadTexture();
    }

    sprite.setTexture(texture);
    sprite.setPosition(startPosition);
    sprite.setScale(0.05f, 0.05f); // Adjust scale to make the bullet smaller
}

void Bullet::update(sf::Time dt) {
    // Move the bullet upwards
    sprite.move(0.f, -speed * dt.asSeconds());
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Bullet::isOffScreen() const {
    // Check if the bullet has moved off the screen
    return sprite.getPosition().y + sprite.getGlobalBounds().height < 0;
}

const sf::FloatRect Bullet::getBounds() const {
    return sprite.getGlobalBounds();
}
