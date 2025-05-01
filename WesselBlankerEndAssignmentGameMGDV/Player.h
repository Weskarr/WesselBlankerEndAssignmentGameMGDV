
/*
	File Type: "Header"
	Made by: "Wessel Blanker"
	Started on: "07-12-2024"
	About: "This is the Player itself, that dodges Enemies and collects hackable Data Orbs."
*/

#pragma region included Libraries & Files

// Single Safety:
#pragma once

// Included SFML Libraries:
#include <SFML/Graphics.hpp> 

// Included Header Files:
#include "MathRigidbody.h"

#pragma endregion

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
	void InitVariables();
	void InitShape();

	// Updating Functions (Private):
	void UpdateInput();
	void UpdateRigidbodyPosition();
	void UpdateWindowBoundsCollision(const sf::RenderTarget* target);

public:

	// Constructor Functions (Public):
	Player(float x, float y, World* world);

	// Accessors Functions (Public):
	const sf::RectangleShape getShape() const;
	void SetNewFillTransparency(float newTransparency);

	// Updating Functions (Public):
	void Update(const sf::RenderTarget* target);

	// Rendering Functions (Public):
	void Render(sf::RenderTarget* target);
};

