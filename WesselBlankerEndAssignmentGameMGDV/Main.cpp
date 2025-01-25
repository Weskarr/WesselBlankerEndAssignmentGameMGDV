
#pragma region General
/*
    Made by: "Wessel Blanker"
    Started on: "06-12-2024"
    About: "Learning basics of C++ by tutorial playlist & HKU Lessons called Math for GDV."

    Sources:
        > Extensive youtube playlist from: "Suraj Sharma"

    Unknowns:
        > Look into PreCompiled Headers?

    Questions:
        > What does main really - really mean ? Fixed Update or smth ?
        > Why require a return at the end of main ? Bit weird..no ?
        > Why do you need to dereference pointers?
*/
#pragma endregion

#include <iostream> // No idea what this truly is yet..?
#include "Game.h"

int main()
{
    // Enable debug heap checks
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init Game Master
    Game game;

    // Game Loop
    while(game.running() && !game.getEndGame()) 
    {
        // Update
        game.update();

        // Render
        game.render();
    }

    // End of Application
    return 0; 
}