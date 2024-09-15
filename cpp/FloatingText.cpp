#include "FloatingText.h"

FloatingText::FloatingText(const sf::Vector2f& position, const std::string& text, sf::Font& font, sf::Color color, float direction)
    : lifetime(sf::seconds(1.0f)), elapsedTime(sf::Time::Zero), direction(direction) { // Text disappears after 1 second
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setCharacterSize(22);
    this->text.setFillColor(color);
    this->text.setPosition(position);
}

void FloatingText::update(sf::Time dt) {
    elapsedTime += dt;
    // Move the text slightly over time
    text.move(0, direction * dt.asSeconds());
}

void FloatingText::draw(sf::RenderWindow& window) const {
    window.draw(text);
}

bool FloatingText::isExpired() const {
    return elapsedTime >= lifetime;
}
