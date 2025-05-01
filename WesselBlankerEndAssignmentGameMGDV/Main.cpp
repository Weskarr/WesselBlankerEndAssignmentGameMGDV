
/*
    File Type: "Source"
    Made by: "Wessel Blanker"
    Started on: "06-12-2024"
    About: "This is the Main Source File that drives the Game (Master)."
*/

#pragma region included Files

// Included Header Files:
#include "Game.h"

#pragma endregion

// ======================= Main =========================

#pragma region [Private]

// Drives the Application.
int main()
{
    // Enable Debug Incase of Memory Leaks.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Initialize srand for Random Values Seed.
    std::srand(static_cast<unsigned>(time(NULL)));

    // Initialize Game (Master).
    Game game;

    // Game Loop.
    while (game.Running() && !game.GetEndGame())
    {
        // Update the Game (Master).
        game.Update();

        // Render the Game (Master).
        game.Render();
    }

    // End of Application.
    return 0;
}

#pragma endregion





#pragma region [Public]

#pragma endregion

#pragma region [Private]

#pragma endregion