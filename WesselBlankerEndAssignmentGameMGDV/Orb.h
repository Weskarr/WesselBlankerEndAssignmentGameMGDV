#pragma once

#include <SFML/Graphics.hpp> // No idea what this truly is yet..?
#include <SFML/System.hpp> // No idea what this truly is yet..?
#include <SFML/Window.hpp> // No idea what this truly is yet..?
#include <SFML/Audio.hpp> // No idea what this truly is yet..?
#include <SFML/Network.hpp> // No idea what this truly is yet..?

class Orb
{
private:
	sf::CircleShape shape;

	void initShape(sf::RenderWindow& window);

public:
	Orb(sf::RenderWindow& window);
	virtual ~Orb();

	const sf::CircleShape getShape() const;

	void update();
	void render(sf::RenderTarget& target);
};