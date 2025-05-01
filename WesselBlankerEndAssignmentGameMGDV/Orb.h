
/*
	File Type: "Header"
	Made by: "Wessel Blanker"
	Started on: "08-12-2024"
	About: "This is a collectable Data Orb that is hackable by the Player."
*/

#pragma region included Libraries & Files

// Single Safety:
#pragma once

// Included SFML Libraries:
#include <SFML/Graphics.hpp>

#pragma endregion

// Class:
class Orb
{
private:

	// Orb Visual Related:
	sf::CircleShape shape;

	// Initial Functions (Private):
	void InitShape(sf::RenderWindow& window);

public:

	// Constructor Functions (Public):
	Orb(sf::RenderWindow& window);

	// Accessors Functions (Public):
	const sf::CircleShape GetShape() const;

	// Rendering Functions (Public):
	void Render(sf::RenderTarget& target);
};