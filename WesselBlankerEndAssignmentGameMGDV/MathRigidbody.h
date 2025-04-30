
/*
	File Type: "Header"
	Made by: "Wessel Blanker"
	Started on: "30-04-2025"
	About: "This is my custom Rigidbody class."
*/

/*
    Second Iteration Changes:
    1. Completely New!
*/

// Single Safety:
#pragma once

// Included Header Files:
#include "MathVector2.h"
#include "MathWorld.h"



// Class:
class MathRigidbody
{
private:

    // Physics Variables:
    MathVector2 position;
    MathVector2 velocity;
    MathVector2 acceleration;

    // Pointer to the World object
    World* world;

public:

    // Constructor Functions (Public):
    MathRigidbody(World* world) 
        : world(world), position(0, 0), velocity(0, 0), acceleration(0, 0) {
    }

    // Destructor Functions (Public):
    virtual ~MathRigidbody();

    // Accessor Functions (Public):
    void AddForce(const MathVector2& force);
    void Update(float deltaTime);
    void Print() const;

    // Setter Functions (Public):
    void setPosition(const MathVector2& newPosition);
    void setVelocity(const MathVector2& newVelocity);
    void setAcceleration(const MathVector2& newAcceleration);

    // Getter Functions (Public):
    MathVector2 getPosition() const;
    MathVector2 getVelocity() const;
    MathVector2 getAcceleration() const;

};

