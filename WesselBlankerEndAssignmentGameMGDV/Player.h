
/*
	File Type: "Header"
	Made by: "Wessel Blanker"
	Started on: "07-12-2024"
	About: "This is the Player itself, that dodges Enemies and collects hackable Data Orbs."
*/

// Single Safety:
#pragma once

// Included SFML Libraries:
#include <SFML/Graphics.hpp> 

// Included Header Files:
#include "MathRigidbody.h"

// Class:
class Player
{
private:

	// Player Visual Related Variables:
	sf::RectangleShape shape;

	// Pointer to the World object
	World* world;

	// Movement Related Variables:
	MathRigidbody rigidbody;
	float movementSpeed;
	float movementSpeedMax;

	// Initial Functions (Private):
	void initVariables();
	void initShape();

	// Updating Functions (Private):
	void updateInput();
	void updateRigidbodyPosition();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);

public:

	// Constructor Functions (Public):
	Player(float x, float y, World* world);

	// Destructor Functions (Public):
	virtual ~Player();

	// Accessors Functions (Public):
	const sf::RectangleShape getShape() const;
	void SetNewFillTransparency(float newTransparency);

	// Updating Functions (Public):
	void update(const sf::RenderTarget* target);

	// Rendering Functions (Public):
	void render(sf::RenderTarget* target);
};

