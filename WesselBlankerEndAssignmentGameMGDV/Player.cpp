
/*
	File Type: "Source"
	Made by: "Wessel Blanker"
	Started on: "07-12-2024"
	About: "This is the Player itself, that dodges Enemies and collects hackable Data Orbs."	
*/

#pragma region included Files

// Included Header File:
#include "Player.h"

#pragma endregion

#pragma region [Public]

#pragma endregion

#pragma region [Private]

#pragma endregion

// ======================= CONSTRUCTOR =========================

#pragma region [Public]

// (Public)
Player::Player(float x, float y, World* world)
	: rigidbody(world, MathVector2(x, y)), world(world)
{
	this->InitVariables();
	this->InitShape();
}

#pragma endregion

// ======================= INITIAL =========================

#pragma region [Public]

// (Public)
void Player::InitVariables()
{
	// Set Movement Related Variables:
	this->movementSpeed = 0.6f;
	this->movementSpeedMax = 3.5f;
	rigidbody.SetMass(1.0f);
}

// (Public)
void Player::InitShape()
{
	// Create the Player.
	this->shape.setOutlineThickness(-2.f);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

#pragma endregion


// ======================= ACCESORS =========================

#pragma region [Public]

// (Public)
const sf::RectangleShape Player::getShape() const
{
	// Returns the Player Shape.
	return this->shape;
}

// (Public)
void Player::SetNewFillTransparency(float newTransparency)
{
	this->shape.setFillColor(sf::Color(0, 255, 0, 5 + static_cast<sf::Uint8>(newTransparency)));
	this->shape.setOutlineColor(sf::Color(0, 255, 0, 50 + static_cast<sf::Uint8>(newTransparency)));
}

#pragma endregion

// ======================= UPDATING =========================

#pragma region [Public]

// (Public)
void Player::Update(const sf::RenderTarget* target)
{
	// Keyboard Input Update.
	this->UpdateInput();

	// Rigidbody Position Update.
	this->UpdateRigidbodyPosition();

	// Window Bounds Collision.
	this->UpdateWindowBoundsCollision(target);
}

#pragma endregion

#pragma region [Private]

// (Private)
void Player::UpdateInput()
{
	MathVector2 velocity = rigidbody.GetVelocity();
	float speed = movementSpeed;

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

//
void Player::UpdateRigidbodyPosition()
{
	if (!world) {
		std::cerr << "Error: Player world is nullptr.\n";
		return;
	}

	rigidbody.Update();

	// Apply updated position to shape
	MathVector2 pos = rigidbody.GetPosition();
	this->shape.setPosition(pos.ToSFML());
}

// (Private)
void Player::UpdateWindowBoundsCollision(const sf::RenderTarget* target)
{
	MathVector2 velocity = rigidbody.GetVelocity();
	MathVector2 correction = MathVector2(0, 0);

	// Left Side Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().left <= 0.f)
	{
		correction.SetMathVector2(MathVector2
		(0.f, this->shape.getGlobalBounds().top));
		velocity.SetOnlyX(0);
	}

	// Right Side Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
	{
		correction.SetMathVector2(MathVector2
		(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top));
		velocity.SetOnlyX(0);
	}

	// Top Side Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().top <= 100.f)
	{
		correction.SetMathVector2(MathVector2
		(this->shape.getGlobalBounds().left, 100.f));
		velocity.SetOnlyY(0);
	}

	// Bottom Side Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
	{
		correction.SetMathVector2(MathVector2
		(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height));
		velocity.SetOnlyY(0);
	}

	if (correction.GetOnlyX() != 0 || correction.GetOnlyY() != 0)
	{
		this->shape.setPosition(correction.ToSFML());
		this->rigidbody.SetPosition(correction);
	}

	rigidbody.SetVelocity(velocity);
}

#pragma endregion

// ======================= RENDERING =========================

#pragma region [Public]

// (Public)
void Player::Render(sf::RenderTarget* target)
{
	// Draw the Player Shape.
	target->draw(this->shape);
}

#pragma endregion