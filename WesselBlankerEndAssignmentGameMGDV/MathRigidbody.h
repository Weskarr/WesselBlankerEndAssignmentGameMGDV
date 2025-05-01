
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
    float mass;

    // Pointer to the World object
    World* world;

public:

    // Constructor Functions (Public):
    MathRigidbody(World* world = nullptr,
        MathVector2 position = MathVector2(0, 0),
        MathVector2 velocity = MathVector2(0, 0),
        MathVector2 acceleration = MathVector2(0, 0),
        float mass = 1.0f);

    // Accessor Functions (Public):
    void AddForce(const MathVector2& force);
    void Print() const;

    // Updating Functions (Private):
    void Update();

    // Setter Functions (Public):
    void SetPosition(const MathVector2& newPosition);
    void SetVelocity(const MathVector2& newVelocity);
    void SetAcceleration(const MathVector2& newAcceleration);
    void SetMass(float newMass);

    // Getter Functions (Public):
    MathVector2 GetPosition() const;
    MathVector2 GetVelocity() const;
    MathVector2 GetAcceleration() const;
    float GetMass() const;

};

