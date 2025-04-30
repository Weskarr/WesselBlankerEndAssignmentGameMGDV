
/*
	File Type: "Header"
	Made by: "Wessel Blanker"
	Started on: "09-12-2024"
	About: "Is a Enemy that acts like some kind of Anti-Virus, attempting to stop the Player."
*/

// Single Safety:
#pragma once

// Included Standard Libraries:
#include <iostream>

// Included SFML Libraries:
#include <SFML/Graphics.hpp>

// Included Header Files:
#include "MathRigidbody.h"

// Class:
class Enemy
{
private:

	// Enemy Visual Related Variables:
	sf::CircleShape shape;

	// Pointer to the World object
	World* world;

	// Movement Related Variables:
	MathRigidbody rigidbody;
	bool hitBottom;

	// Initial Functions (Private):
	void initVariables();
	void initShape(sf::RenderWindow& window);

	// Updating Functions (Private):
	void updateMovement();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);

public:

	// Constructor Functions (Public):
	Enemy(sf::RenderWindow& window, World* world);

	// Destructor Functions (Public):
	virtual ~Enemy();

	// Accessors Functions (Public):
	const sf::CircleShape getShape() const;
	const bool getHitBottom() const;

	// Updating Functions (Public):
	void update(const sf::RenderTarget* target);

	// Rendering Functions (Public):
	void render(sf::RenderTarget& target);
};