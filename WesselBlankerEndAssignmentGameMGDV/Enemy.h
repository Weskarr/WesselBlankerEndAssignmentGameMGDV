
/*
	File Type: "Header"
	Made by: "Wessel Blanker"
	Started on: "09-12-2024"
	About: "Is a Enemy that acts like some kind of Anti-Virus, attempting to stop the Player."
*/

#pragma region included Libraries & Files

// Single Safety:
#pragma once

// Included Standard Libraries:
#include <iostream>

// Included SFML Libraries:
#include <SFML/Graphics.hpp>

// Included Header Files:
#include "MathRigidbody.h"

#pragma endregion

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
	void InitVariables();
	void InitShape(sf::RenderWindow& window);

	// Updating Functions (Private):
	void UpdateMovement();
	void UpdateWindowBoundsCollision(const sf::RenderTarget* target);

	// Rendering Functions (Private)
	void RenderShape(sf::RenderTarget& target);

public:

	// Constructor Functions (Public):
	Enemy(sf::RenderWindow& window, World* world);

	// Accessors Functions (Public):
	const sf::CircleShape GetShape() const;
	const bool GetHitBottom() const;

	// Updating Functions (Public):
	void Update(const sf::RenderTarget* target);

	// Rendering Functions (Public):
	void Render(sf::RenderTarget& target);
};