#pragma once

#include <SFML/Graphics.hpp> // No idea what this truly is yet..?
#include <SFML/System.hpp> // No idea what this truly is yet..?
#include <SFML/Window.hpp> // No idea what this truly is yet..?
#include <SFML/Audio.hpp> // No idea what this truly is yet..?
#include <SFML/Network.hpp> // No idea what this truly is yet..?

class Player
{
private:
	sf::RectangleShape shape;

	float movementSpeed;

	void initVariables();
	void initShape();


public:

	// Constructors & Destructors
	Player(float x = 350.f, float y = 400.f);
	virtual ~Player();

	const sf::RectangleShape getShape() const;

	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

