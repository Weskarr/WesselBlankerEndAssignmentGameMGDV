
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
MathRigidbody::MathRigidbody(World* world,
    MathVector2 position,
    MathVector2 velocity,
    MathVector2 acceleration,
    float mass)
    : world(world), position(position), velocity(velocity), acceleration(acceleration), mass(mass) {
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
    if (!world) {
        std::cerr << "Error: Rigidbody world is nullptr.\n";
        return;
    }

    // Add gravity force: m * g
    MathVector2 gravityForce(0, mass * world->GetGravity());
    AddForce(gravityForce);

    // Apply friction: simple damping, using velocity directly (no timeStep needed here)
    velocity = velocity * (1.0f - world->GetFriction());

    // Update velocity based on acceleration (using the time step already passed)
    velocity = velocity + (acceleration * deltaTime);

    // Update position based on velocity (using deltaTime for proper integration)
    position = position + (velocity * deltaTime);

    // Reset acceleration after each update
    acceleration = MathVector2(0, 0);
}

// -------------------------------------------------------------------------------
// SETTERS
// -------------------------------------------------------------------------------

// (Public)
void MathRigidbody::SetPosition(const MathVector2& newPosition)
{
    position = newPosition;
}

// (Public)
void MathRigidbody::SetVelocity(const MathVector2& newVelocity)
{
    velocity = newVelocity;
}

// (Public)
void MathRigidbody::SetAcceleration(const MathVector2& newAcceleration)
{
    acceleration = newAcceleration;
}

// (Public)
void MathRigidbody::SetMass(float newMass)
{
    mass = newMass;
}

// -------------------------------------------------------------------------------
// GETTERS
// -------------------------------------------------------------------------------

// (Public)
MathVector2 MathRigidbody::GetPosition() const
{
    return position;
}

// (Public)
MathVector2 MathRigidbody::GetVelocity() const
{
    return velocity;
}

// (Public)
MathVector2 MathRigidbody::GetAcceleration() const
{
    return acceleration;
}

// (Public)
float MathRigidbody::GetMass() const
{
    return mass;
}