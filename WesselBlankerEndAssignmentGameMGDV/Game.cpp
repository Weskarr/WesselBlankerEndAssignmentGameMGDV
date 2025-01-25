
#include "Game.h"

// -------------------------------------------------------------------------------
// CONSTRUCTOR (Public)
// -------------------------------------------------------------------------------

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
}

// -------------------------------------------------------------------------------
// DESTRUCTOR (Public)
// -------------------------------------------------------------------------------

Game::~Game()
{
    delete this->window; // Otherwise big memory leak ???
}

// -------------------------------------------------------------------------------
// INITIAL (Private)
// -------------------------------------------------------------------------------

void Game::initVariables()
{
    // Game Phases Related:
    resetPhases();
    this->startingPhase = true;

    // Game Related
    this->window = nullptr;
    this->quitGame = false;

    // Enemies Related
    this->enemySpawnTimerMax = 120.f;
    this->enemySpawnTimerCur = this->enemySpawnTimerMax;
    this->enemiesMax = 8;

    // Hacking Related
    this->hackingPointsMax = 1024;
    this->hackingPointsCur = 0;
    this->allDataHacked = false;

    // Stealth Related
    this->stealthPercentageMax = 100.f;
    this->stealthPercentageCur = stealthPercentageMax;
    this->stealthRegenStart = 0.01f;
    this->stealthRegenCur = stealthRegenStart;
    this->stealthRegenMultiplier = 1.f;
    this->stealthCooldownMax = 25.f;
    this->stealthCooldownCur = this->stealthCooldownMax;
    this->killSwitch = false;

    // Orbs Related
    this->orbSpawnTimerMax = 8.f;
    this->orbSpawnTimerCur = this->orbSpawnTimerMax;
    this->orbsMax = 100;
}

void Game::initWindow()
{
    this->videoMode.height = 700;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "Game Window", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);

    this->spawnBorderRect.setSize(sf::Vector2f(this->window->getSize().x, 5.f));
    this->spawnBorderRect.setPosition(sf::Vector2f(0.f, 100.f - spawnBorderRect.getSize().y));
    this->spawnBorderRect.setFillColor(sf::Color(0, 255, 0, 50));
}

void Game::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Roboto-Medium.ttf"))
    {
        std::cout << "[ERROR] Failed to Load a Font: " << "\n";
    }
}

void Game::initText()
{
    this->statusText.setFont(this->font);
    this->statusText.setCharacterSize(24);
    this->statusText.setFillColor(sf::Color::Green);
    this->statusText.setString("NONE");

    this->startText.setFont(this->font);
    this->startText.setCharacterSize(48);
    this->startText.setFillColor(sf::Color::Green);
    this->startText.setString("NONE");

    this->endText.setFont(this->font);
    this->endText.setCharacterSize(48);
    this->endText.setFillColor(sf::Color::Green);
    this->endText.setString("NONE");
}

// -------------------------------------------------------------------------------
// ACCESORS (Public)
// -------------------------------------------------------------------------------

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->quitGame;
}

// -------------------------------------------------------------------------------
// POLL-EVENTS (Public)
// -------------------------------------------------------------------------------

void Game::pollEvents()
{
    while (this->window->pollEvent(this->ev)) {
        //Polling loop to check for events.
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

// -------------------------------------------------------------------------------
// TIMED-EVENTS (Public)
// -------------------------------------------------------------------------------

void Game::spawnOrbsTimer()
{
    // Timer
    if (this->orbs.size() < this->orbsMax)
    {
        if (this->orbSpawnTimerCur >= this->orbSpawnTimerMax)
        {
            this->orbs.push_back(Orb(*this->window));
            this->orbSpawnTimerCur = 0.f;
        }
        else
        {
            this->orbSpawnTimerCur += 1.f;
        }
    }
}

void Game::spawnEnemyTimer()
{
    // Timer
    if (this->enemies.size() < this->enemiesMax)
    {
        if (this->enemySpawnTimerCur >= this->enemySpawnTimerMax)
        {
            //std::cout << "[STATUS] Enemies Size: " << this->enemies.size();
            this->enemies.push_back(Enemy(*this->window));
            this->enemySpawnTimerCur = 0.f;
        }
        else
        {
            this->enemySpawnTimerCur += 1.f;
        }
    }
}

void Game::stealthRegeneration()
{
    // Generate a Random Value that is Subtracted from the Current Stealth.

    if (stealthCooldownCur >= stealthCooldownMax) 
    {
        if (this->stealthPercentageCur < 100.f)
        {
            this->stealthRegenMultiplier *= 1.01f;
            std::cout << "Multiplier: " << stealthRegenMultiplier << "\n";
            this->stealthRegenCur = stealthRegenStart * stealthRegenMultiplier;
            this->stealthPercentageCur += stealthRegenCur;
        }
        else
        {
            this->stealthRegenMultiplier = 1.f;
            this->stealthRegenCur = 0.f;
            this->stealthPercentageCur = 100.f;
            this->stealthCooldownCur = 0.f;
        }
    }
    else 
    {
        this->stealthCooldownCur += 1.f;
    }

}

void Game::randomStealthModifier(bool isPositive, int minP, int maxP)
{
    // Generate a Random Value that is Subtracted from the Current Stealth.
    float randomValue = static_cast<float>(rand() % ((maxP * 100) - (minP * 100)) + minP * 100) / 100.f;
    std::cout << "RandomValue of " << minP << " and " << maxP << " is: " << randomValue << "\n";

    if (isPositive) 
    {
        this->stealthPercentageCur += randomValue;

        if (this->stealthPercentageCur > 100.f) 
            this->stealthPercentageCur = 100.f;

    }
    else 
    {
        this->stealthPercentageCur -= randomValue;

        this->stealthRegenMultiplier = 1.f;
        this->stealthRegenCur = 0.f;
        this->stealthCooldownCur = 0.f;
    }
}

void Game::randomHackingCollected()
{
    // Generate a Random Value that is Collected.
    int randomValue = static_cast<float>(rand() % 1 + 3);
    this->hackingPointsCur += randomValue;
    this->randomStealthModifier(false, 0, 1);
}

// -------------------------------------------------------------------------------
// CONDITIONS (Public)
// -------------------------------------------------------------------------------


void Game::stealthConditionCheck()
{
    if (this->stealthPercentageCur <= 0)
    {
        //this->quitGame = true;
        this->killSwitch = true;
        std::cout << "[STATUS] End Game Condition Satisfied: " << "Killswitch!";

        this->resetPhases();
        this->endingPhase = true;
    }
}

void Game::hackingConditionCheck()
{
    if (this->hackingPointsCur >= hackingPointsMax)
    {
        //this->quitGame = true;
        this->allDataHacked = true;
        std::cout << "[STATUS] End Game Condition Satisfied: " << "All Data Hacked!";

        this->resetPhases();
        this->endingPhase = true;
    }
}

void Game::resetPhases()
{
    this->startingPhase = false;
    this->playingPhase = false;
    this->endingPhase = false;
}

void Game::resetGame()
{
    killSwitch = false;
    allDataHacked = false;

    if (orbs.size() > 0)
        this->orbs.clear();

    if (enemies.size() > 0)
        this->enemies.clear();

    if (hackingPointsCur != 0)
        hackingPointsCur = 0;

    if (stealthPercentageCur != 100.f)
        stealthPercentageCur = 100.f;

    for (size_t i = 0; i < this->orbsMax; i++)
    {
        this->orbs.push_back(Orb(*this->window));
    }
}

// -------------------------------------------------------------------------------
// UPDATING (Public)
// -------------------------------------------------------------------------------

void Game::update()
{
    // Checks for Poll-Events.
    this->pollEvents();

    if (this->quitGame == false) 
    {
        // Updates are Dependant on the Current Phase.
        if (startingPhase) 
        {
            // Update the Start Phase Text
            this->updateStartPhaseText();

            // Update the Possibility of Starting with Space Key
            this->updatePlayKey();
        }
        else if (playingPhase)
        {
            // Timed Stealth Regeneration.
            this->stealthRegeneration();

            // Timed Enemy Spawner Update.
            this->spawnEnemyTimer();

            // Timed Orb Spawner Update.
            this->spawnOrbsTimer();

            // Update Enemies
            for (auto& i : this->enemies)
                i.update(this->window);

            // Update the Player.
            this->player.update(this->window);

            // Update Collision.
            this->updateCollision();

            // Update the Text.
            this->updateVariablesText();
        }
        else if (endingPhase) 
        {
            // Update the End Phase Text
            this->updateEndPhaseText();

            // Update the Possibility of Restarting with Space Key
            this->updatePlayKey();
        }
    }
}

void Game::updatePlayKey()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        resetGame();

        this->resetPhases();
        this->playingPhase = true;
    }
}

void Game::updateCollision()
{
    // For Condition Check Afterwards.
    bool checkStealthCondition = false;
    bool checkHackingCondition = false;

    // Loop Through All Orbs.
    for (size_t i = 0; i < this->orbs.size(); i++)
    {
        // Conditional Bool for Removing the Current Orb.
        bool eraseOrbBool = false;

        // Check for Player & Orb Collision
        if (this->player.getShape().getGlobalBounds().intersects(
            this->orbs[i].getShape().getGlobalBounds()))
        {
            // Collect Hacking Points.
            this->randomHackingCollected();

            // Make sure to do a Condition Check Afterwards and Remove the Orb.
            checkStealthCondition = true;
            checkHackingCondition = true;
            eraseOrbBool = true;
        }

        // Condition for Removing the Current Orb.
        if (eraseOrbBool)
            this->orbs.erase(this->orbs.begin() + i);
    }

    // Loop Through All Enemies.
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        // Conditional Bool for Removing the Current Enemy.
        bool eraseEnemyBool = false;

        // Check for Player & Enemy Collision
        if (this->player.getShape().getGlobalBounds().intersects(
            this->enemies[i].getShape().getGlobalBounds()))
        {
            // Lose a Random Amount of Stealth.
            this->randomStealthModifier(false, 30, 50);

            // Make sure to do a Condition Check Afterwards and Remove the Enemy.
            checkStealthCondition = true;
            eraseEnemyBool = true;
        }
        // Check if Hit Bottom
        else if (this->enemies[i].getHitBottom()) 
        {
            // Gain a Random Amount of Stealth.
            this->randomStealthModifier(true, 2, 5);

            // Make sure to do a Condition Check Afterwards and Remove the Enemy.
            checkStealthCondition = true;
            eraseEnemyBool = true;
        }

        // Condition for Removing the Current Enemy.
        if (eraseEnemyBool)
            this->enemies.erase(this->enemies.begin() + i);
    }

    // Condition for Stealth.
    if (checkStealthCondition)
        this->stealthConditionCheck();

    // Condition for Hacking.
    if (checkHackingCondition)
        this->hackingConditionCheck();
}

void Game::updateVariablesText()
{
    std::stringstream ss;

    float progress = std::round(static_cast<float>(this->hackingPointsCur) / static_cast<float>(this->hackingPointsMax) * 100.f) / 10.0f;

    ss << std::fixed
        << std::setprecision(0) << "Data Hacked: " << "[ " << hackingPointsCur << " / " << hackingPointsMax << " GB ]" << "\n"
        << std::setprecision(1) << "Stealth: " << "[ " << stealthPercentageCur << "% ]";

    this->statusText.setString(ss.str());
}

void Game::updateStartPhaseText()
{
    std::stringstream ss;

    ss << "PRESS SPACE TO START";

    this->startText.setString(ss.str());
}

void Game::updateEndPhaseText()
{
    std::stringstream ss;

    // if lost + reason
    if (killSwitch == true) 
    {
        ss << "[LOST] Kill Switch Shutdown!";
    }

    // if won + reason
    if (allDataHacked == true)
    {
        ss << "[WON] All Data is Hacked!";
    }

    this->endText.setString(ss.str());
}

// -------------------------------------------------------------------------------
// RENDERING (Public)
// -------------------------------------------------------------------------------

void Game::render()
{
    // Clear the Window
    this->window->clear(sf::Color(0, 20, 0));
   
    // Draw Spawn Border
    this->renderSpawnBorder(*this->window);

    // Draw Player
    this->player.render(this->window);

    // Draw Orbs
    for (auto i : this->orbs)
        i.render(*this->window);

    // Draw Enemies
    for (auto i : this->enemies)
        i.render(*this->window);

    // Render Depending on the Current Phase.
    if (startingPhase) 
    {
        // Draw Start Phase Text
        this->renderStartPhaseText(*this->window);
    }
    else if (playingPhase) 
    {
        // Draw Variables (Score & Health)
        this->renderVariablesText(*this->window);
    }
    else if (endingPhase) 
    {
        // Draw End Phase Text
        this->renderEndPhaseText(*this->window);
    }

    // Display All Renders
    this->window->display();
}

void Game::renderSpawnBorder(sf::RenderTarget& target)
{
    target.draw(this->spawnBorderRect);
}

void Game::renderVariablesText(sf::RenderTarget& target)
{
    target.draw(this->statusText);
}

void Game::renderStartPhaseText(sf::RenderTarget& target)
{
    target.draw(this->startText);
}

void Game::renderEndPhaseText(sf::RenderTarget& target)
{
    target.draw(this->endText);
}
