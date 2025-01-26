
/*
    File Type: "Source"
    Made by: "Wessel Blanker"
    Started on: "06-12-2024"
    About: "This is the Main Source File that drives the Game (Master)."
*/

// Included Header Files:
#include "Game.h"



// Main:
int main()
{
    // Enable Debug Incase of Memory Leaks.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Initialize srand for Random Values Seed.
    std::srand(static_cast<unsigned>(time(NULL)));

    // Initialize Game (Master).
    Game game;

    // Game Loop.
    while(game.running() && !game.getEndGame()) 
    {
        // Update the Game (Master).
        game.update();

        // Render the Game (Master).
        game.render();
    }

    // End of Application.
    return 0; 
}