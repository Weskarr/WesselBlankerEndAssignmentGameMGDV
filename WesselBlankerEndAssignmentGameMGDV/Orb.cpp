
/*
	File Type: "Source"
	Made by: "Wessel Blanker"
    Started on: "08-12-2024"
	About: "This is a collectable Data Orb that is hackable by the Player."
*/

#pragma region included Files

// Included Header File:
#include "Orb.h"

#pragma endregion

// ======================= CONSTRUCTOR =========================

#pragma region [Public]

// Constructs this Orb.
Orb::Orb(sf::RenderWindow& window)
{
	// Initialize this.
	this->InitShape(window);
}

#pragma endregion

// ======================= INITIAL =========================

#pragma region [Private]

// Itializes the Orb Shape.
void Orb::InitShape(sf::RenderWindow& window)
{
	// Create the Orb
	this->shape.setRadius(static_cast<float>(rand() % 5 + 10));
	sf::Color color(0, rand() % 25 + 50, 0);
	this->shape.setFillColor(color);

	// Randomize Position.
	float shapePosX = static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width);
	float shapePosY = static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height);

	// Check if Out-Of-Bounds and correct if Necessary.
	if (shapePosX < 0.f)
	{
		// Set X-Position 0.
		shapePosX = 0.f;
	}
	if (shapePosY < 100.f)
	{
		// Move Y-Position Down.
		shapePosY += 200.f;
	}

	// Apply this Position.
	this->shape.setPosition(sf::Vector2f(shapePosX, shapePosY));
}

#pragma endregion

// ======================= ACCESORS =========================

#pragma region [Public]

// Gets the Orb Shape.
const sf::CircleShape Orb::GetShape() const
{ return this->shape; }

#pragma endregion

// ======================= RENDERING =========================

#pragma region [Public]

// Renders the Orb.
void Orb::Render(sf::RenderTarget& target)
{ target.draw(this->shape); }

#pragma endregion