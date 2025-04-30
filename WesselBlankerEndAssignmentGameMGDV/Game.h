
/*
	File Type: "Header"
	Made by: "Wessel Blanker"
	Started on: "06-12-2024"
	About: "This is kind of like my Game Master, with a few extras."
*/

// Single Safety:
#pragma once

// Included Standard Libraries:
#include <iomanip>
#include <sstream>

// Included Header Files:
#include "Player.h"
#include "Enemy.h"
#include "Orb.h"



// Class:
class Game
{
private:

	// Game Phases Related Variables:
	bool startingPhase; // For is in Starting Phase.
	bool playingPhase; // For is in Playing Phase.
	bool endingPhase; // For is in Ending Phase. 

	// Main Related Variables:
	bool quitGame; // For Quitting the Game.

	// Player Related Variables:
	Player player;

	// Enemies Related Variables:
	std::vector<Enemy> enemies;
	float enemySpawnTimerMax;
	float enemySpawnTimerCur;
	int enemiesMax;

	// Orbs Related Variables:
	std::vector<Orb> orbs;
	float orbSpawnTimerMax;
	float orbSpawnTimerCur;
	int orbsMax;

	// Window Related Variables:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Text Related Variables:
	sf::Font font;
	sf::Text statusText;
	sf::Text endText;
	sf::Text startText;

	// Hacking Related Variables:
	int hackingPointsMax;
	int hackingPointsCur;
	bool allDataHacked;

	// Stealth Related Variables:
	float stealthPercentageMax;
	float stealthPercentageCur;
	float stealthRegenStart;
	float stealthRegenMultiplier;
	float stealthCooldownMax;
	float stealthCooldownCur;
	float stealthRegenCur;
	bool killSwitch;

	// Playable Area Related Variables:
	sf::RectangleShape playableAreaBorder;

	// Initial Functions (Private):
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();

	// Poll-Events Functions (Private):
	void pollEvents();

	// Timed-Events Functions (Private):
	void spawnOrbsTimer();
	void spawnEnemyTimer();
	void stealthRegeneration();
	void randomStealthModifier(bool isPositive, int minP, int maxP);
	void randomHackingCollected();

	// Conditions Functions (Private):
	void stealthConditionCheck();
	void hackingConditionCheck();
	void resetPhases();
	void resetGame();

	// Updating Functions (Private):
	void updatePlayKey();
	void updateCollision();
	void updateVariablesText();
	void updateStartPhaseText();
	void updateEndPhaseText();

	// Rendering Functions (Private):
	void renderPlayableAreaBorder(sf::RenderTarget& target);
	void renderVariablesText(sf::RenderTarget& target);
	void renderStartPhaseText(sf::RenderTarget& target);
	void renderEndPhaseText(sf::RenderTarget& target);

public:

	// Constructor Functions (Public):
	Game();

	// Destructor Functions (Public):
	virtual ~Game();

	// Accessors Functions (Public):
	const bool running() const;
	const bool getEndGame() const;

	// Updating Functions (Public):
	void update();

	// Rendering Functions (Public):
	void render();
};