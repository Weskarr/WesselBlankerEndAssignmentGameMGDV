
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

// (Public)
World::World(float friction, float gravity, float timeStep)
	: friction(friction), gravity(gravity), timeStep(timeStep) {
}

#pragma endregion

// ======================= SETTERS =========================

#pragma region [Public]

// (Public)
void World::SetFriction(float newFriction)
{ friction = newFriction; }

// (Public)
void World::SetGravity(float newGravity)
{ gravity = newGravity; }

// (Public)
void World::SetTimeStep(float newTimeStep)
{ timeStep = newTimeStep; }

#pragma endregion

// ======================= GETTERS =========================

#pragma region [Public]

// (Public)
float World::GetFriction() const 
{ return friction; }

// (Public) 
float World::GetGravity() const 
{ return gravity; }

// (Public)
float World::GetTimeStep() const 
{ return timeStep; }

#pragma endregion