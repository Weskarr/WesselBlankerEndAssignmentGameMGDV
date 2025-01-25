#include "Orb.h"

void Orb::initShape(sf::RenderWindow& window)
{
	this->shape.setRadius(static_cast<float>(rand() % 5 + 10));
	sf::Color color(0, rand() % 25 + 50, 0);
	this->shape.setFillColor(color);

	float shapePosX = static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width);
	float shapePosY = static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height);
	
	if (shapePosX < 0.f) {
		shapePosX = 0.f;
	}

	if (shapePosY < 100.f) {
		shapePosY += 200.f;
	}

	this->shape.setPosition(sf::Vector2f(shapePosX, shapePosY));
}

Orb::Orb(sf::RenderWindow& window)
{
	this->initShape(window);
}

Orb::~Orb()
{

}

const sf::CircleShape Orb::getShape() const
{
	return this->shape;
}

void Orb::update()
{

}

void Orb::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}