
/*
	File Type: "Header"
	Made by: "Wessel Blanker"
	Started on: "07-12-2024"
	About: "This is the Player itself, that dodges Enemies and collects hackable Data Orbs."
*/

// Included SFML Libraries:
#include <SFML/Graphics.hpp> 



// Class:
class Player
{
private:

	// Player Visual Related Variables:
	sf::RectangleShape shape;

	// Movement Related Variables:
	float movementSpeed;

	// Initial Functions (Private):
	void initVariables();
	void initShape();

	// Updating Functions (Private):
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);

public:

	// Constructor Functions (Public):
	Player(float x = 350.f, float y = 400.f);

	// Destructor Functions (Public):
	virtual ~Player();

	// Accessors Functions (Public):
	const sf::RectangleShape getShape() const;

	// Updating Functions (Public):
	void update(const sf::RenderTarget* target);

	// Rendering Functions (Public):
	void render(sf::RenderTarget* target);
};

