
/*
	File Type: "Source"
	Made by: "Wessel Blanker"
	Started on: "09-12-2024"
	About: "Is a Enemy that acts like some kind of Anti-Virus, randomly attempting to stop the Player."
*/

#pragma region included Files

// Included Header File:
#include "Enemy.h"

#pragma endregion

// ======================= CONSTRUCTOR =========================

#pragma region [Public]

// Constructs this Enemy.
Enemy::Enemy(sf::RenderWindow& window, World* world)
	: rigidbody(world), world(world)
{
	// Initialize this.
	this->InitShape(window);
	this->InitVariables();
}

#pragma endregion


// ======================= INITIAL =========================

#pragma region [Private]

// Initializes the Variables.
void Enemy::InitVariables()
{
	// Set Movement Related Variables:
	this->hitBottom = false;

	// Set initial velocity
	float velX = static_cast<float>(rand() % (2 * 200 + 1) - 200) / 100;
	float velY = static_cast<float>(rand() % 100 + 75) / 100;
	rigidbody.SetVelocity(MathVector2(velX, velY));
	rigidbody.SetPosition(MathVector2(this->shape.getPosition().x, this->shape.getPosition().y));
	rigidbody.SetMass(1.0f);
}

// Initializes the Shape Variables.
void Enemy::InitShape(sf::RenderWindow& window)
{
	// Create the Enemy.
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setOutlineColor(sf::Color(255, 50, 50));
	this->shape.setOutlineThickness(-2.f);
	this->shape.setRadius(static_cast<float>(rand() % 16 + 45));

	// Randomize X-Position.
	float shapePosX = static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width);

	// Set Y-Position just above Global Bounds.
	float shapePosY = -this->shape.getGlobalBounds().height;

	// Check if Out-Of-Bounds and correct if Necessary.
	if (shapePosX < 0.f)
	{
		// Set X-Position 0.
		shapePosX = 0.f;
	}

	// Apply this Position.
	this->shape.setPosition(sf::Vector2f(shapePosX, shapePosY));
}

#pragma endregion

// ======================= ACCESORS =========================

#pragma region [Public]

// Returns this Shape.
const sf::CircleShape Enemy::GetShape() const
{
	// Returns the Enemy Shape.
	return this->shape;
}

// Returns this HitBottom Status.
const bool Enemy::GetHitBottom() const
{
	// Returns the Hit Bottom Status.
	return this->hitBottom;
}

#pragma endregion

// ======================= UPDATING =========================

#pragma region [Public]

// Controls the Update Order.
void Enemy::Update(const sf::RenderTarget* target)
{
	//Movement Update.
	UpdateMovement();

	//Window Bounds Collision.
	UpdateWindowBoundsCollision(target);
}

#pragma endregion

#pragma region [Private]

// Updates Movement
void Enemy::UpdateMovement()
{
	rigidbody.Update();

	// Apply updated position to shape
	MathVector2 pos = rigidbody.GetPosition();
	this->shape.setPosition(pos.ToSFML());
}

// Updates Out-Of-Bounds Corrections
void Enemy::UpdateWindowBoundsCollision(const sf::RenderTarget* target)
{
	// Left Side Bounce & Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().left <= 0.f)
	{
		//this->velocity.x *= -1;
		MathVector2 velocity = rigidbody.GetVelocity();
		MathVector2 newVelocity(-velocity.GetMathVector2().GetOnlyX(), velocity.GetMathVector2().GetOnlyY());
		rigidbody.SetVelocity(newVelocity);
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	}

	// Right Side Bounce & Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
	{
		//this->velocity.x *= -1;
		MathVector2 velocity = rigidbody.GetVelocity();
		MathVector2 newVelocity(-velocity.GetMathVector2().GetOnlyX(), velocity.GetMathVector2().GetOnlyY());
		rigidbody.SetVelocity(newVelocity);
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	}

	// Top side, no need..

	// Bottom Side Boolean & Out-Of-Bounds Correction if Necessary.
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y + this->shape.getGlobalBounds().height)
	{
		this->hitBottom = true;
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y + this->shape.getGlobalBounds().height);
	}
}

#pragma endregion

// ======================= RENDERING =========================

#pragma region [Public]

// Controls the Render Order.
void Enemy::Render(sf::RenderTarget& target)
{
	// Draw Shape.
	RenderShape(target);
}

#pragma endregion

#pragma region [Private]

//
void Enemy::RenderShape(sf::RenderTarget& target)
{
	// Draw the Enemy Shape.
	target.draw(this->shape);
}

#pragma endregion