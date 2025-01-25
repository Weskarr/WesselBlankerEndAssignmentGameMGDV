#pragma once

/*
	Acts kind of like my Game Master.
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <sstream>

#include "Player.h"
#include "Enemy.h"
#include "Orb.h"

class Game
{
private:

	// Game Phases Related:
	bool startingPhase; // For is in Starting Phase.
	bool playingPhase; // For is in Playing Phase.
	bool endingPhase; // For is in Ending Phase. 
	bool quitGame; // For Quitting the Game.

	// Player Related:
	Player player;

	// Enemies Related:
	std::vector<Enemy> enemies;
	float enemySpawnTimerMax;
	float enemySpawnTimerCur;
	int enemiesMax;

	// Orbs Related:
	std::vector<Orb> orbs;
	float orbSpawnTimerMax;
	float orbSpawnTimerCur;
	int orbsMax;

	// Window Related:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Text Related:
	sf::Font font;
	sf::Text statusText;
	sf::Text endText;
	sf::Text startText;

	// Hacking Related:
	int hackingPointsMax;
	int hackingPointsCur;
	bool allDataHacked;

	// Stealth Related:
	float stealthPercentageMax;
	float stealthPercentageCur;
	float stealthRegenStart;
	float stealthRegenMultiplier;
	float stealthCooldownMax;
	float stealthCooldownCur;
	float stealthRegenCur;
	bool killSwitch;

	// Spawn Border Related:
	sf::RectangleShape spawnBorderRect;

	// Initial Functions:
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();

public:

	// Constructor
	Game();

	// Destructor
	virtual ~Game();

	// Accessors
	const bool running() const;
	const bool getEndGame() const;

	// Poll-Events
	void pollEvents();

	// Timed-Events
	void spawnOrbsTimer();
	void spawnEnemyTimer();
	void stealthRegeneration();
	void randomStealthModifier(bool isPositive, int minP, int maxP);
	void randomHackingCollected();

	// Game Conditions
	// *Start
	// *Playing
	void stealthConditionCheck();
	void hackingConditionCheck();
	void resetPhases();
	void resetGame();
	// *End

	// Updating
	void update();
	void updatePlayKey();
	void updateCollision();
	void updateVariablesText();
	void updateStartPhaseText();
	void updateEndPhaseText();

	// Rendering
	void render();
	void renderSpawnBorder(sf::RenderTarget& target);
	void renderVariablesText(sf::RenderTarget& target);
	void renderStartPhaseText(sf::RenderTarget& target);
	void renderEndPhaseText(sf::RenderTarget& target);
};