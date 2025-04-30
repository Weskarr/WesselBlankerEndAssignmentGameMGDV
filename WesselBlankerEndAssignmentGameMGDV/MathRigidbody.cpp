
/*
	File Type: "Source"
	Made by: "Wessel Blanker"
	Started on: "30-04-2025"
	About: "This is my custom Rigidbody class."
*/

/*
	Second Iteration Changes:
    1. Completely New!
*/

// Included Header File:
#include "MathRigidbody.h"



// -------------------------------------------------------------------------------
// CONSTRUCTORS
// -------------------------------------------------------------------------------

// (Public)
MathRigidbody::MathRigidbody(World* world) 
    : world(world), position(0, 0), velocity(0, 0), acceleration(0, 0) {
}

// -------------------------------------------------------------------------------
// DESTRUCTORS
// -------------------------------------------------------------------------------

MathRigidbody::~MathRigidbody()
{
    // Empty for now..
}

// -------------------------------------------------------------------------------
// ACCESORS
// -------------------------------------------------------------------------------

// (Public)
void MathRigidbody::AddForce(const MathVector2& force) {
    // Apply a force to the Rigidbody (change in acceleration)
    // Formula: F = ma, so acceleration = force / mass
    acceleration = force / mass;
}

// (Public)
void MathRigidbody::Print() const
{
    // For debugging, print the position and velocity
    std::cout << "Position: ";
    position.Print();
    std::cout << "Velocity: ";
    velocity.Print();
}

// -------------------------------------------------------------------------------
// UPDATING
// -------------------------------------------------------------------------------

// (Private)
void MathRigidbody::Update(float deltaTime) 
{
    // Add gravity
    MathVector2 gravityForce(0, -world->getGravity() * mass); // F = m * g
    AddForce(gravityForce);

    // Apply friction to velocity (simple damping)
    velocity = velocity * (1 - world->getFriction());

    // Update velocity based on acceleration
    velocity = velocity + (acceleration * deltaTime);

    // Update position based on velocity
    position = position + (velocity * deltaTime);

    // Reset acceleration after each update
    acceleration = MathVector2(0, 0);
}

// -------------------------------------------------------------------------------
// SETTERS
// -------------------------------------------------------------------------------

// (Public)
void MathRigidbody::setPosition(const MathVector2& newPosition)
{
    position = newPosition;
}

// (Public)
void MathRigidbody::setVelocity(const MathVector2& newVelocity)
{
    velocity = newVelocity;
}

// (Public)
void MathRigidbody::setAcceleration(const MathVector2& newAcceleration)
{
    acceleration = newAcceleration;
}

// (Public)
void MathRigidbody::setMass(float newMass)
{
    mass = newMass;
}

// -------------------------------------------------------------------------------
// GETTERS
// -------------------------------------------------------------------------------

// (Public)
MathVector2 MathRigidbody::getPosition() const
{
    return position;
}

// (Public)
MathVector2 MathRigidbody::getVelocity() const
{
    return velocity;
}

// (Public)
MathVector2 MathRigidbody::getAcceleration() const
{
    return acceleration;
}

// (Public)
float MathRigidbody::getMass() const
{
    return mass;
}