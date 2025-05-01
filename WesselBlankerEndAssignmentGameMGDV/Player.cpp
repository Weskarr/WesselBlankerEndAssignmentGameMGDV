
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
Player::Player(float x, float y, World* world)
	: rigidbody(world, MathVector2(x, y)), world(world)
{
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
	this->movementSpeed = 0.6f;
	this->movementSpeedMax = 3.5f;
	rigidbody.SetMass(1.0f);
}

// (Public)
void Player::initShape()
{
	// Create the Player.
	this->shape.setOutlineThickness(-2.f);
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

// (Public)
void Player::SetNewFillTransparency(float newTransparency) 
{
	this->shape.setFillColor(sf::Color(0, 255, 0, 5.0f + newTransparency));
	this->shape.setOutlineColor(sf::Color(0, 255, 0, 50.0f + newTransparency));
}

// -------------------------------------------------------------------------------
// UPDATING
// -------------------------------------------------------------------------------

// (Public)
void Player::update(const sf::RenderTarget* target)
{
	// Keyboard Input Update.
	this->updateInput();

	// Rigidbody Position Update.
	this->updateRigidbodyPosition();

	// Window Bounds Collision.
	this->updateWindowBoundsCollision(target);
}

// (Private)
void Player::updateInput()
{
	MathVector2 velocity = rigidbody.GetVelocity();
	float speed = movementSpeed * world->GetTimeStep(); // Adjust movement speed with time step

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.SetOnlyX(velocity.GetOnlyX() - speed);
		if (velocity.GetOnlyX() < -movementSpeedMax)
			velocity.SetOnlyX(-movementSpeedMax);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.SetOnlyX(velocity.GetOnlyX() + speed);
		if (velocity.GetOnlyX() > movementSpeedMax)
			velocity.SetOnlyX(movementSpeedMax);
	}
	else
	{
		velocity.SetOnlyX(velocity.GetOnlyX() * 0.9f); // Damping factor
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.SetOnlyY(velocity.GetOnlyY() - speed);
		if (velocity.GetOnlyY() < -movementSpeedMax)
			velocity.SetOnlyY(-movementSpeedMax);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.SetOnlyY(velocity.GetOnlyY() + speed);
		if (velocity.GetOnlyY() > movementSpeedMax)
			velocity.SetOnlyY(movementSpeedMax);
	}
	else
	{
		velocity.SetOnlyY(velocity.GetOnlyY() * 0.9f); // Damping factor
	}





	rigidbody.SetVelocity(velocity);
}

void Player::updateRigidbodyPosition() 
{
	if (!world) {
		std::cerr << "Error: Player world is nullptr.\n";
		return;
	}

	rigidbody.Update(world->GetTimeStep());

	// Apply updated position to shape
	MathVector2 pos = rigidbody.GetPosition();
	this->shape.setPosition(pos.ToSFML());
}

// (Private)
void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	MathVector2 velocity = rigidbody.GetVelocity();
	MathVector2 correctionHorizontal = MathVector2(0,0);
	MathVector2 correctionVertical = MathVector2(0,0);

	// Left Side Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().left <= 0.f)
	{
		correctionHorizontal.SetMathVector2(MathVector2
		(0.f, this->shape.getGlobalBounds().top));
		velocity.SetOnlyX(0);
	}

	// Right Side Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
	{
		correctionHorizontal.SetMathVector2(MathVector2
		(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top));
		velocity.SetOnlyX(0);
	}

	// Top Side Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().top <= 100.f)
	{
		correctionVertical.SetMathVector2(MathVector2
		(this->shape.getGlobalBounds().left, 100.f));
		velocity.SetOnlyY(0);
	}

	// Bottom Side Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
	{
		correctionVertical.SetMathVector2(MathVector2
		(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height));
		velocity.SetOnlyY(0);
	}

	if (correctionHorizontal.GetOnlyX() != 0 || correctionHorizontal.GetOnlyY() != 0)
	{
		this->shape.setPosition(correctionHorizontal.ToSFML());
		this->rigidbody.SetPosition(correctionHorizontal);
	}

	if (correctionVertical.GetOnlyX() != 0 || correctionVertical.GetOnlyY() != 0)
	{
		this->shape.setPosition(correctionVertical.ToSFML());
		this->rigidbody.SetPosition(correctionVertical);
	}

	rigidbody.SetVelocity(velocity);
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
