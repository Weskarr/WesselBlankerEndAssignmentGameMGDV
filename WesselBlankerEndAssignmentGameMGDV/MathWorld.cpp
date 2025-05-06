
/*
	File Type: "Source"
	Made by: "Wessel Blanker"
	Started on: "30-04-2025"
	About: "This is for holding world variables."
*/

#pragma region included Files

// Included Header File:
#include "MathWorld.h"

#pragma endregion

// ======================= CONSTRUCTORS =========================

#pragma region [Public]

// Constructs this World.
World::World(float friction, float gravity, float timeStep)
	: friction(friction), gravity(gravity), timeStep(timeStep) {
}

#pragma endregion

// ======================= SETTERS =========================

#pragma region [Public]

// Sets a given Friction Value.
void World::SetFriction(float newFriction)
{ friction = newFriction; }

// Sets a given Gravity Value.
void World::SetGravity(float newGravity)
{ gravity = newGravity; }

// Sets a given TimeStep Value.
void World::SetTimeStep(float newTimeStep)
{ timeStep = newTimeStep; }

#pragma endregion

// ======================= GETTERS =========================

#pragma region [Public]

// Gets the Friction Value.
float World::GetFriction() const 
{ return friction; }

// Gets the Gravity Value.
float World::GetGravity() const 
{ return gravity; }

// Gets the TimeStep Value.
float World::GetTimeStep() const 
{ return timeStep; }

#pragma endregion