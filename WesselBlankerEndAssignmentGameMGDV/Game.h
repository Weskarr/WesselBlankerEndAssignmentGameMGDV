
/*
	File Type: "Header"
	Made by: "Wessel Blanker"
	Started on: "06-12-2024"
	About: "This is kind of like my Game Master, with a few extras."
*/

#pragma region included Libraries & Files

// Single Safety:
#pragma once

// Included Standard Libraries:
#include <iomanip>
#include <sstream>

// Included Header Files:
#include "Player.h"
#include "Enemy.h"
#include "Orb.h"
#include "MathWorld.h"

#pragma endregion

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

	// Pointer to the World object
	World* world;

	// Player Related Variables:
	Player* player;

	// Initial Functions (Private):
	void InitVariables();
	void InitWindow();
	void InitFonts();
	void InitText();

	// Poll-Events Functions (Private):
	void PollEvents();

	// Timed-Events Functions (Private):
	void SpawnOrbsTimer();
	void SpawnEnemyTimer();
	void StealthRegeneration();
	void RandomStealthModifier(bool isPositive, int minP, int maxP);
	void RandomHackingCollected();

	// Conditions Functions (Private):
	void StealthConditionCheck();
	void HackingConditionCheck();
	void ResetPhases();
	void ResetGame();

	// Updating Functions (Private):
	void UpdatePlayKey();
	void UpdateCollision();
	void UpdateVariablesText();
	void UpdateStartPhaseText();
	void UpdateEndPhaseText();

	// Rendering Functions (Private):
	void RenderPlayableAreaBorder(sf::RenderTarget& target);
	void RenderVariablesText(sf::RenderTarget& target);
	void RenderStartPhaseText(sf::RenderTarget& target);
	void RenderEndPhaseText(sf::RenderTarget& target);

public:

	// Constructor Functions (Public):
	Game();

	// Accessors Functions (Public):
	const bool Running() const;
	const bool GetEndGame() const;

	// Updating Functions (Public):
	void Update();

	// Rendering Functions (Public):
	void Render();
};