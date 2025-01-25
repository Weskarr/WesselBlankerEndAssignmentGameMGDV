#pragma once

#include <iostream>

#include <SFML/Graphics.hpp> // No idea what this truly is yet..?
#include <SFML/System.hpp> // No idea what this truly is yet..?
#include <SFML/Window.hpp> // No idea what this truly is yet..?
#include <SFML/Audio.hpp> // No idea what this truly is yet..?
#include <SFML/Network.hpp> // No idea what this truly is yet..?

class Enemy
{
private:
	sf::CircleShape shape;

	sf::Vector2f velocity;
	bool hitBottom;

	void initVariables();
	void initShape(sf::RenderWindow& window);

public:

	Enemy(sf::RenderWindow& window);
	virtual ~Enemy();

	const sf::CircleShape getShape() const;
	const bool getHitBottom() const;

	void update(const sf::RenderTarget* target);
	void updateMovement();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void render(sf::RenderTarget& target);
};

