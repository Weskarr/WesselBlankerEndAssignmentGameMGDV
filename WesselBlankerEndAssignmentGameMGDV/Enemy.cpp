
/*
	File Type: "Source"
	Made by: "Wessel Blanker"
	Started on: "09-12-2024"
	About: "Is a Enemy that acts like some kind of Anti-Virus, randomly attempting to stop the Player."
*/

/*
	Second Iteration Changes:
	1.
	2.
	3.
*/

// Included Header File:
#include "Enemy.h"


// -------------------------------------------------------------------------------
// CONSTRUCTOR
// -------------------------------------------------------------------------------

// (Public)
Enemy::Enemy(sf::RenderWindow& window, World* world)
	: rigidbody(world), world(world)
{
	// Initialize this.
	this->initShape(window);
	this->initVariables();
}

// -------------------------------------------------------------------------------
// DESTRUCTOR
// -------------------------------------------------------------------------------

// (Public)
Enemy::~Enemy()
{
	// Empty for now..
}

// -------------------------------------------------------------------------------
// INITIAL
// -------------------------------------------------------------------------------

// (Private)
void Enemy::initVariables()
{
	// Set Movement Related Variables:
	this->hitBottom = false;

	// Set initial velocity
	float velX = static_cast<float>(rand() % (2 * 200 + 1) - 200) / 100;
	float velY = static_cast<float>(rand() % 100 + 75) / 100;
	rigidbody.SetVelocity(MathVector2(velX, velY));
	rigidbody.SetPosition(MathVector2(this->shape.getPosition().x, this->shape.getPosition().y));
	//rigidbody.SetPosition(MathVector2(220, 220));
	rigidbody.SetMass(1.0f);
}

// (Private)
void Enemy::initShape(sf::RenderWindow& window)
{
	// Create the Enemy.
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setOutlineColor(sf::Color(255,50,50));
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

// -------------------------------------------------------------------------------
// ACCESORS
// -------------------------------------------------------------------------------

// (Public)
const sf::CircleShape Enemy::getShape() const
{
	// Returns the Enemy Shape.
	return this->shape;
}

// (Public)
const bool Enemy::getHitBottom() const
{
	// Returns the Hit Bottom Status.
	return this->hitBottom;
}

// -------------------------------------------------------------------------------
// UPDATING
// -------------------------------------------------------------------------------

// (Public)
void Enemy::update(const sf::RenderTarget* target)
{
	//Movement Update.
	updateMovement();

	//Window Bounds Collision.
	updateWindowBoundsCollision(target);
}

// (Private)
void Enemy::updateMovement()
{
	rigidbody.Update(world->GetTimeStep());

	// Apply updated position to shape
	MathVector2 pos = rigidbody.GetPosition();
	this->shape.setPosition(pos.ToSFML());
}

// (Private)
void Enemy::updateWindowBoundsCollision(const sf::RenderTarget* target)
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

// -------------------------------------------------------------------------------
// RENDERING
// -------------------------------------------------------------------------------

// (Public)
void Enemy::render(sf::RenderTarget& target)
{
	// Draw the Enemy Shape.
	target.draw(this->shape);
}