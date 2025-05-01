
/*
    File Type: "Source"
    Made by: "Wessel Blanker"
    Started on: "06-12-2024"
    About: "This is kind of like my Game Master, with a few extras."
*/

#pragma region included Files

// Included Header File:
#include "Game.h"

#pragma endregion

// ======================= CONSTRUCTOR =========================

#pragma region [Public]

//
Game::Game()
{
    // Initialize this.
    this->InitVariables();
    this->InitWindow();
    this->InitFonts();
    this->InitText();
}

#pragma endregion

// ======================= INITIAL =========================

#pragma region [Private]

//
void Game::InitVariables()
{
    // Set the World if null:
    if (!this->world)
        this->world = new World();

    // Set Game Phases Related Variables:
    ResetPhases();
    this->startingPhase = true;

    // Set Main Related Variables:
    this->quitGame = false;

    // Set Window Related Variables:
    this->window = nullptr;

    // Set Enemies Related Variables:
    this->enemySpawnTimerMax = 120.f;
    this->enemySpawnTimerCur = this->enemySpawnTimerMax;
    this->enemiesMax = 8;

    // Set Orbs Related Variables:
    this->orbSpawnTimerMax = 8.0f;
    this->orbSpawnTimerCur = this->orbSpawnTimerMax;
    this->orbsMax = 100;

    // Set Hacking Related Variables:
    this->hackingPointsMax = 1024;
    this->hackingPointsCur = 0;
    this->allDataHacked = false;

    // Set Stealth Related Variables:
    this->stealthPercentageMax = 100.f;
    this->stealthPercentageCur = stealthPercentageMax;
    this->stealthRegenStart = 0.01f;
    this->stealthRegenCur = stealthRegenStart;
    this->stealthRegenMultiplier = 1.f;
    this->stealthCooldownMax = 25.f;
    this->stealthCooldownCur = this->stealthCooldownMax;
    this->killSwitch = false;

    // Apply World to Player:
    if (!this->player)
    {
        this->player = new Player(350.f, 400.f, this->world);
        this->player->SetNewFillTransparency(0);
    }
}

// 
void Game::InitWindow()
{
    // Create the Window.
    this->videoMode.height = 700;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "Game Window", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);

    // Create the Border Visual.
    this->playableAreaBorder.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), 5.f));
    this->playableAreaBorder.setPosition(sf::Vector2f(0.f, 100.f - playableAreaBorder.getSize().y));
    this->playableAreaBorder.setFillColor(sf::Color(0, 255, 0, 50));
}

//
void Game::InitFonts()
{
    // Load the Font.
    if (!this->font.loadFromFile("Fonts/Roboto-Medium.ttf"))
    {
        // Notify Console if Unable!
        std::cout << "[ERROR] Failed to Load a Font: " << "\n";
    }
}

// 
void Game::InitText()
{
    // Status Text Setup.
    this->statusText.setFont(this->font);
    this->statusText.setCharacterSize(24);
    this->statusText.setFillColor(sf::Color::Green);
    this->statusText.setString("NONE");

    // Start Text Setup.
    this->startText.setFont(this->font);
    this->startText.setCharacterSize(48);
    this->startText.setFillColor(sf::Color::Green);
    this->startText.setString("NONE");

    // End Text Setup.
    this->endText.setFont(this->font);
    this->endText.setCharacterSize(48);
    this->endText.setFillColor(sf::Color::Green);
    this->endText.setString("NONE");
}

#pragma endregion

// ======================= ACCESORS =========================

#pragma region [Public]

// 
const bool Game::Running() const
{
    // Returns the Window IsOpen Status.
    return this->window->isOpen();
}

// 
const bool Game::GetEndGame() const
{
    // Returns the Quit Game Status.
    return this->quitGame;
}

#pragma endregion

// ======================= POLL-EVENTS =========================

#pragma region [Private]

// 
void Game::PollEvents()
{
    // Sort of Input Manager.
    while (this->window->pollEvent(this->ev)) {
        
        //Polling loop to check for events.
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            // Do this when the Window is Closed.
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            // Do this when the Escape is Pressed.
            if (ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

#pragma endregion

// ======================= TIMED-EVENTS =========================

#pragma region [Private]

// 
void Game::SpawnOrbsTimer()
{
    // Only continue when not Max Orbs.
    if (this->orbs.size() < this->orbsMax)
    {
        // Await Timer.
        if (this->orbSpawnTimerCur >= this->orbSpawnTimerMax)
        {
            // Spawn New Orb.
            this->orbs.push_back(Orb(*this->window));

            // Reset This Timer.
            this->orbSpawnTimerCur = 0.f;
        }
        else
        {
            // Tick Time.
            this->orbSpawnTimerCur += 1.f;
        }
    }
}

// 
void Game::SpawnEnemyTimer()
{
    // Only continue when not Max Enemies.
    if (this->enemies.size() < this->enemiesMax)
    {
        // Await Timer.
        if (this->enemySpawnTimerCur >= this->enemySpawnTimerMax)
        {
            // Spawn New Enemy.
            this->enemies.push_back(Enemy(*this->window, world));

            // Reset This Timer.
            this->enemySpawnTimerCur = 0.f;
        }
        else
        {
            // Tick Time.
            this->enemySpawnTimerCur += 1.f;
        }
    }
}

// 
void Game::StealthRegeneration()
{
    // Await Cooldown Timer.
    if (stealthCooldownCur >= stealthCooldownMax)
    {
        if (this->stealthPercentageCur < 100.f)
        {
            // Increase Multiplier
            this->stealthRegenMultiplier *= 1.01f;

            // Notify Console of this change.
            std::cout << "Multiplier: " << stealthRegenMultiplier << "\n";

            // Add the Stealth.
            this->stealthRegenCur = stealthRegenStart * stealthRegenMultiplier;
            this->stealthPercentageCur += stealthRegenCur;

            // Change Player Transparency
            this->player->SetNewFillTransparency(stealthPercentageCur);
        }
        else
        {
            // Reset All Regeneration Variables if Max Stealth. 
            this->stealthRegenMultiplier = 1.f;
            this->stealthRegenCur = 0.f;
            this->stealthPercentageCur = 100.f;
            this->stealthCooldownCur = 0.f;
        }
    }
    else
    {
        // Tick Time.
        this->stealthCooldownCur += 1.f;
    }
}

// 
void Game::RandomStealthModifier(bool isPositive, int minP, int maxP)
{
    // Generate a Random Value that is Subtracted from the Current Stealth.
    float randomValue = static_cast<float>(rand() % ((maxP * 100) - (minP * 100)) + minP * 100) / 100.f;

    // Notify Console of this (shortly upcoming) change.
    std::cout << "RandomValue of " << minP << " and " << maxP << " is: " << randomValue << "\n";

    // Add or Subtract?
    if (isPositive)
    {
        // Add the Random Stealth Value.
        this->stealthPercentageCur += randomValue;

        // Make sure not to exceed Max.
        if (this->stealthPercentageCur > 100.f)
            this->stealthPercentageCur = 100.f;
    }
    else
    {
        // Subtract the Random Stealth Value.
        this->stealthPercentageCur -= randomValue;

        // Reset Regeneration and Cooldown.
        this->stealthRegenMultiplier = 1.f;
        this->stealthRegenCur = 0.f;
        this->stealthCooldownCur = 0.f;
    }
}

// 
void Game::RandomHackingCollected()
{
    // Generate a Random Value that is Collected.
    int randomValue = rand() % 1 + 3;
    this->hackingPointsCur += randomValue;

    // Also Generate a Random Value of Stealth that is Lost.
    this->RandomStealthModifier(false, 0, 1);
}

#pragma endregion

// ======================= CONDITIONS =========================

#pragma region [Private]

// 
void Game::StealthConditionCheck()
{
    if (this->stealthPercentageCur <= 0)
    {
        // Enable Kill Switch Condition True = You lost!
        this->killSwitch = true;

        // Notify Console of this important development.
        std::cout << "[STATUS] End Game Condition Satisfied: " << "Kill Switch!";

        // Set Current Phase to Playing Phase.
        this->ResetPhases();
        this->endingPhase = true;
    }
}

// 
void Game::HackingConditionCheck()
{
    if (this->hackingPointsCur >= hackingPointsMax)
    {
        // Enable All Data Hacked Condition True = You won!
        this->allDataHacked = true;

        // Notify Console of this important development.
        std::cout << "[STATUS] End Game Condition Satisfied: " << "All Data Hacked!";

        // Set Current Phase to Ending Phase.
        this->ResetPhases();
        this->endingPhase = true;
    }
}

// 
void Game::ResetPhases()
{
    // Set all Phases False
    this->startingPhase = false;
    this->playingPhase = false;
    this->endingPhase = false;
}

// 
void Game::ResetGame()
{
    // Reset End Conditions.
    killSwitch = false;
    allDataHacked = false;

    // Clear all Orbs If Necessary.
    if (orbs.size() > 0)
        this->orbs.clear();

    // Clear all Enemies If Necessary.
    if (enemies.size() > 0)
        this->enemies.clear();

    // Reset Hacking Points If Necessary.
    if (hackingPointsCur != 0)
        hackingPointsCur = 0;

    // Reset Stealth Percentage If Necessary.
    if (stealthPercentageCur != 100.f)
    {
        stealthPercentageCur = 100.f;
        this->player->SetNewFillTransparency(stealthPercentageCur);
    }

    // Start with Max Orbs.
    for (size_t i = 0; i < this->orbsMax; i++)
    {
        this->orbs.push_back(Orb(*this->window));
    }

    // Set Current Phase to Playing Phase.
    this->ResetPhases();
    this->playingPhase = true;
}

#pragma endregion

// ======================= UPDATING =========================

#pragma region [Public]

//
void Game::Update()
{
    // Checks for Poll-Events.
    this->PollEvents();

    // Check if Quiting Game.
    if (this->quitGame == true)
        return;

    // Updates are Dependant on the Current Phase.
    if (startingPhase)
    {
        // Update the Start Phase Text.
        this->UpdateStartPhaseText();

        // Update the Possibility of Starting with Space Key.
        this->UpdatePlayKey();
    }
    else if (playingPhase)
    {
        // Timed Stealth Regeneration.
        this->StealthRegeneration();

        // Timed Enemy Spawner Update.
        this->SpawnEnemyTimer();

        // Timed Orb Spawner Update.
        this->SpawnOrbsTimer();

        // Update Enemies.
        for (auto& i : this->enemies)
            i.Update(this->window);

        // Update the Player.
        this->player->Update(this->window);

        // Update Collision.
        this->UpdateCollision();

        // Update the Text.
        this->UpdateVariablesText();
    }
    else if (endingPhase)
    {
        // Update the End Phase Text.
        this->UpdateEndPhaseText();

        // Update the Possibility of Restarting with Space Key.
        this->UpdatePlayKey();
    }
}

#pragma endregion

#pragma region [Private]

// 
void Game::UpdatePlayKey()
{
    // If the Space Key is Pressed Continue.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        // Resets the Game & Sets Playing Phase True.
        ResetGame();
    }
}

// 
void Game::UpdateCollision()
{
    // For Condition Check Afterwards.
    bool checkStealthCondition = false;
    bool checkHackingCondition = false;

    // Loop Through All Orbs.
    for (size_t i = 0; i < this->orbs.size(); i++)
    {
        // Conditional Bool for Removing the Current Orb.
        bool eraseOrbBool = false;

        // Check for Player & Orb Collision.
        if (this->player->getShape().getGlobalBounds().intersects(
            this->orbs[i].GetShape().getGlobalBounds()))
        {
            // Collect Hacking Points.
            this->RandomHackingCollected();

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

        // Check for Player & Enemy Collision.
        if (this->player->getShape().getGlobalBounds().intersects(
            this->enemies[i].GetShape().getGlobalBounds()))
        {
            // Lose a Random Amount of Stealth.
            this->RandomStealthModifier(false, 30, 50);

            // Make sure to do a Condition Check Afterwards and Remove the Enemy.
            checkStealthCondition = true;
            eraseEnemyBool = true;
        }
        // Check if Hit Bottom.
        else if (this->enemies[i].GetHitBottom())
        {
            // Gain a Random Amount of Stealth.
            this->RandomStealthModifier(true, 2, 5);

            // Make sure to do a Condition Check Afterwards and Remove the Enemy.
            checkStealthCondition = true;
            eraseEnemyBool = true;
        }

        // Condition for Removing the Current Enemy.
        if (eraseEnemyBool)
            this->enemies.erase(this->enemies.begin() + i);
    }

    // Check Stealth Condition If Changed and apply correct feedback.
    if (checkStealthCondition)
    {
        this->StealthConditionCheck();
        this->player->SetNewFillTransparency(stealthPercentageCur);
    }


    // Check Hacking Condition If Changed.
    if (checkHackingCondition)
        this->HackingConditionCheck();
}

// 
void Game::UpdateVariablesText()
{
    // Open String Stream.
    std::stringstream ss;

    // Add String Information to the String Stream.
    ss << std::fixed
        << std::setprecision(0) << "Data Hacked: " << "[ " << hackingPointsCur << " / " << hackingPointsMax << " GB ]" << "\n"
        << std::setprecision(1) << "Stealth: " << "[ " << stealthPercentageCur << "% ]";

    // Finally Apply it to the Status Text.
    this->statusText.setString(ss.str());
}

// 
void Game::UpdateStartPhaseText()
{
    // Open String Stream.
    std::stringstream ss;

    // Add String Information to the String Stream.
    ss << "PRESS SPACE TO START";

    // Finally Apply it to the Start Text.
    this->startText.setString(ss.str());
}

// 
void Game::UpdateEndPhaseText()
{
    // Open String Stream.
    std::stringstream ss;

    // if lost + reason.
    if (killSwitch == true)
    {
        // Add String Information to the String Stream.
        ss << "[LOST] Kill Switch Shutdown!";
    }

    // if won + reason.
    if (allDataHacked == true)
    {
        // Add String Information to the String Stream.
        ss << "[WON] All Data is Hacked!";
    }

    // Finally Apply it to the End Text.
    this->endText.setString(ss.str());
}

#pragma endregion

// ======================= RENDERING =========================

#pragma region [Public]

//
void Game::Render()
{
    // Clear the Window.
    this->window->clear(sf::Color(0, 20, 0));

    // Draw Spawn Border.
    this->RenderPlayableAreaBorder(*this->window);

    // Draw Player.
    this->player->Render(this->window);

    // Draw Orbs.
    for (auto& i : this->orbs)
        i.Render(*this->window);

    // Draw Enemies.
    for (auto& i : this->enemies)
        i.Render(*this->window);

    // Render Depending on the Current Phase.
    if (startingPhase)
    {
        // Draw Start Phase Text.
        this->RenderStartPhaseText(*this->window);
    }
    else if (playingPhase)
    {
        // Draw Variables (Score & Health).
        this->RenderVariablesText(*this->window);
    }
    else if (endingPhase)
    {
        // Draw End Phase Text.
        this->RenderEndPhaseText(*this->window);
    }

    // Display All Renders.
    this->window->display();
}

#pragma endregion

#pragma region [Private]

// 
void Game::RenderPlayableAreaBorder(sf::RenderTarget& target)
{
    // Draw the Playable Area Border.
    target.draw(this->playableAreaBorder);
}

// 
void Game::RenderVariablesText(sf::RenderTarget& target)
{
    // Draw the Status Text.
    target.draw(this->statusText);
}

// 
void Game::RenderStartPhaseText(sf::RenderTarget& target)
{
    // Draw the Start Text.
    target.draw(this->startText);
}

// 
void Game::RenderEndPhaseText(sf::RenderTarget& target)
{
    // Draw the End Text.
    target.draw(this->endText);
}

#pragma endregion
