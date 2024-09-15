#include "Ship.h"


Ship::Ship(const sf::Vector2f& startPosition, const std::string& texturePath)
    : position(startPosition) {
    if (!texture.loadFromFile(texturePath)) {
        // Handle error
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);

}

void Ship::update(sf::Time dt) {

}

void Ship::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Ship::setPosition(const sf::Vector2f& pos) {
    position = pos;
    sprite.setPosition(position);
}

const sf::Vector2f& Ship::getPosition() const {
    return position;
}

bool Ship::collidesWith(const Bullet& bullet) const {
    // Get the bounding boxes once
    sf::FloatRect shipBounds = sprite.getGlobalBounds();
    sf::FloatRect bulletBounds = bullet.getBounds();

    // Check for intersection
    return shipBounds.intersects(bulletBounds);
}

bool Ship::collidesWithE(const EnemyBullet& enemybullet) const {
    // Get the bounding boxes once
    sf::FloatRect shipBounds = sprite.getGlobalBounds();
    sf::FloatRect enemybulletBounds = enemybullet.getBounds();


    // Check for intersection
    return shipBounds.intersects(enemybulletBounds);
}

bool Ship::collidesWithE2(const EnemyBullet2& enemybullet2) const {
    // Get the bounding boxes once
    sf::FloatRect shipBounds = sprite.getGlobalBounds();
    sf::FloatRect enemybullet2Bounds = enemybullet2.getBounds();

    // Check for intersection
    return shipBounds.intersects(enemybullet2Bounds);
}


bool Ship::collidesWithE2Reverse(const EnemyBullet2Reverse& enemybullet2Reverse) const {
    // Get the bounding boxes once
    sf::FloatRect shipBounds = sprite.getGlobalBounds();
    sf::FloatRect enemybullet2ReverseBounds = enemybullet2Reverse.getBounds();

    // Check for intersection
    return shipBounds.intersects(enemybullet2ReverseBounds);
}
