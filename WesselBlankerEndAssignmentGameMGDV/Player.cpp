#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 5.0f;
}

void Player::initShape()
{
	this->shape.setOutlineColor(sf::Color::Green);
	this->shape.setOutlineThickness(-2.f);
	this->shape.setFillColor(sf::Color(0, 255, 0, 100));
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

// Constructors & Destructors
Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);
	this->initVariables();
	this->initShape();
}

Player::~Player()
{

}

const sf::RectangleShape Player::getShape() const
{
	return this->shape;
}

void Player::updateInput()
{
	// Move Left (Left Arrow or A)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movementSpeed, 0.f);
	}
	// Move Right (Right Arrow or D)
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}
	// Move Up (Up Arrow or W)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f, -this->movementSpeed);
	}
	// Move Down (Down Arrow or S)
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.f, this->movementSpeed);
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	// Left Check
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	// Right Check
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	// Top Check
	if (this->shape.getGlobalBounds().top <= 100.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 100.f);
	// Bottom Check
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{
	// Keyboard Input Update
	this->updateInput();

	// Window Bounds Collision
	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
