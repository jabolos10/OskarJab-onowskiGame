#include "Healthbar.h"

HealthBar::HealthBar(float x, float y, float width, float height)
    : maxHealth(100.0f), currentHealth(100.0f) {
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color::Red);
    background.setPosition(x, y);

    foreground.setSize(sf::Vector2f(width, height));
    foreground.setFillColor(sf::Color::Green);
    foreground.setPosition(x, y);
}

void HealthBar::setHealthPoints(float healthPoints) {
    currentHealth = healthPoints;
    float width = background.getSize().x * (currentHealth / maxHealth);
    foreground.setSize(sf::Vector2f(width, foreground.getSize().y));
}

void HealthBar::draw(sf::RenderWindow& window) const {
    window.draw(background);
    window.draw(foreground);
}
