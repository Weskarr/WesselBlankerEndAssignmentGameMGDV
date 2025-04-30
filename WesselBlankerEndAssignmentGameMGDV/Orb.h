
/*
	File Type: "Header"
	Made by: "Wessel Blanker"
	Started on: "08-12-2024"
	About: "This is a collectable Data Orb that is hackable by the Player."
*/

// Single Safety:
#pragma once

// Included SFML Libraries:
#include <SFML/Graphics.hpp>



// Class:
class Orb
{
private:

	// Orb Visual Related:
	sf::CircleShape shape;

	// Initial Functions (Private):
	void initShape(sf::RenderWindow& window);

public:

	// Constructor Functions (Public):
	Orb(sf::RenderWindow& window);

	// Destructor Functions (Public):
	virtual ~Orb();

	// Accessors Functions (Public):
	const sf::CircleShape getShape() const;

	// Rendering Functions (Public):
	void render(sf::RenderTarget& target);
};