
/*
    File Type: "Header"
    Made by: "Wessel Blanker"
    Started on: "30-04-2025"
    About: "This is for holding World Based Variables."
*/

#pragma region included Libraries & Files

// Single Safety:
#pragma once

#pragma endregion

// Class:
class World 
{
private:

    // Centralized World Variables:
    float friction;
    float gravity;
    float timeStep;

public:

    // Constructor Functions (Public):
    World(float friction = 1.0f / 1500.0f, float gravity = 9.8f * 0, float timeStep = 1.0f * 1.5f);

    // Setter Functions (Public):
    void SetFriction(float newFriction);
    void SetGravity(float newGravity);
    void SetTimeStep(float newTimeStep);

    // Getter Functions (Public):
    float GetFriction() const;
    float GetGravity() const;
    float GetTimeStep() const;

};