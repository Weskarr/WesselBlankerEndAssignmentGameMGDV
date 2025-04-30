
/*
	File Type: "Source"
	Made by: "Wessel Blanker"
	Started on: "07-12-2024"
	About: "This is the Player itself, that dodges Enemies and collects hackable Data Orbs."	
*/

/*
	Second Iteration Changes:
	1.
	2.
	3.
*/

// Included Header File:
#include "Player.h"



// -------------------------------------------------------------------------------
// CONSTRUCTOR
// -------------------------------------------------------------------------------

// (Public)
Player::Player(float x, float y)
{
	// Initialize this.
	this->shape.setPosition(x, y);
	this->initVariables();
	this->initShape();
}

// -------------------------------------------------------------------------------
// DESTRUCTOR
// -------------------------------------------------------------------------------

// (Public)
Player::~Player()
{
	// Empty for now..
}

// -------------------------------------------------------------------------------
// INITIAL
// -------------------------------------------------------------------------------

// (Public)
void Player::initVariables()
{
	// Set Movement Related Variables:
	this->movementSpeed = 5.0f;
}

// (Public)
void Player::initShape()
{
	// Create the Player.
	this->shape.setOutlineColor(sf::Color::Green);
	this->shape.setOutlineThickness(-2.f);
	this->shape.setFillColor(sf::Color(0, 255, 0, 100));
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

// -------------------------------------------------------------------------------
// ACCESORS
// -------------------------------------------------------------------------------

// (Public)
const sf::RectangleShape Player::getShape() const
{
	// Returns the Player Shape.
	return this->shape;
}

// -------------------------------------------------------------------------------
// UPDATING
// -------------------------------------------------------------------------------

// (Public)
void Player::update(const sf::RenderTarget* target)
{
	// Keyboard Input Update.
	this->updateInput();

	// Window Bounds Collision.
	this->updateWindowBoundsCollision(target);
}

// (Private)
void Player::updateInput()
{
	// Horizontal Axis:
	// Move Left (Left Arrow or A).
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// Move the Player Shape Left.
		this->shape.move(-this->movementSpeed, 0.f);
	}
	// Move Right (Right Arrow or D).
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// Move the Player Shape Right.
		this->shape.move(this->movementSpeed, 0.f);
	}

	// Vertical Axis:
	// Move Up (Up Arrow or W).
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		// Move the Player Shape Up.
		this->shape.move(0.f, -this->movementSpeed);
	}
	// Move Down (Down Arrow or S).
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// Move the Player Shape Down.
		this->shape.move(0.f, this->movementSpeed);
	}
}

// (Private)
void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	// Left Side Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);

	// Right Side Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);

	// Top Side Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().top <= 100.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 100.f);

	// Bottom Side Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}

// -------------------------------------------------------------------------------
// RENDERING
// -------------------------------------------------------------------------------

// (Public)
void Player::render(sf::RenderTarget* target)
{
	// Draw the Player Shape.
	target->draw(this->shape);
}
