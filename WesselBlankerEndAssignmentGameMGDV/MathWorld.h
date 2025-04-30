
/*
    File Type: "Header"
    Made by: "Wessel Blanker"
    Started on: "30-04-2025"
    About: "This is for holding world variables."
*/

/*
    Second Iteration Changes:
    1. Completely New!
*/

// Single Safety:
#pragma once



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
    World(float friction = 0.1f, float gravity = 9.8f, float timeStep = 1.0f)
        : friction(friction), gravity(gravity), timeStep(timeStep) {
    }

    // Destructor Functions (Public):
    virtual ~World();

    // Setter Functions (Public):
    void setFriction(float newFriction);
    void setGravity(float newGravity);
    void setTimeStep(float newTimeStep);

    // Getter Functions (Public):
    float getFriction() const;
    float getGravity() const;
    float getTimeStep() const;

};