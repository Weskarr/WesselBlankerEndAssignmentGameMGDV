
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

// Apply a force to the Rigidbody (change in acceleration)
void MathRigidbody::AddForce(const MathVector2& force) {
    // For simplicity, we're assuming mass=1, so force = acceleration
    acceleration = force;
}

// Update the physics (position and velocity)
void MathRigidbody::Update(float deltaTime) {
    // Apply friction to velocity (simple damping)
    velocity = velocity * World.getFriction();

    // Update velocity based on acceleration
    velocity = velocity + (acceleration * deltaTime);

    // Update position based on velocity
    position = position + (velocity * deltaTime);

    // Reset acceleration after each update
    acceleration = MathVector2(0, 0);
}

// For debugging, print the position and velocity
void MathRigidbody::Print() const {
    std::cout << "Position: ";
    position.Print();
    std::cout << "Velocity: ";
    velocity.Print();
}

// -------------------------------------------------------------------------------
// SETTERS
// -------------------------------------------------------------------------------

MathVector2 MathRigidbody::getPosition() const 
{
    return position;
}

MathVector2 MathRigidbody::getVelocity() const 
{
    return velocity;
}

MathVector2 MathRigidbody::getAcceleration() const 
{
    return acceleration;
}

// -------------------------------------------------------------------------------
// GETTERS
// -------------------------------------------------------------------------------

void MathRigidbody::setPosition(const MathVector2& newPosition) 
{
    position = newPosition;
}

void MathRigidbody::setVelocity(const MathVector2& newVelocity) 
{
    velocity = newVelocity;
}

void MathRigidbody::setAcceleration(const MathVector2& newAcceleration) 
{
    acceleration = newAcceleration;
}