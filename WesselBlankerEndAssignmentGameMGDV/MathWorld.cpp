
/*
	File Type: "Source"
	Made by: "Wessel Blanker"
	Started on: "30-04-2025"
	About: "This is for holding world variables."
*/

/*
	Second Iteration Changes:
	1. Completely New!
*/

// Included Header File:
#include "MathWorld.h"



// -------------------------------------------------------------------------------
// CONSTRUCTORS
// -------------------------------------------------------------------------------

// (Public)
World::World(float friction, float gravity, float timeStep)
	: friction(friction), gravity(gravity), timeStep(timeStep) {
}

// -------------------------------------------------------------------------------
// DESTRUCTORS
// -------------------------------------------------------------------------------

// (Public)
World::~World()
{
	// Empty for now..
}

// -------------------------------------------------------------------------------
// SETTERS
// -------------------------------------------------------------------------------

// (Public)
void World::SetFriction(float newFriction)
{
	friction = newFriction;
}

// (Public)
void World::SetGravity(float newGravity)
{
	gravity = newGravity;
}

// (Public)
void World::SetTimeStep(float newTimeStep)
{
	timeStep = newTimeStep;
}

// -------------------------------------------------------------------------------
// GETTERS
// -------------------------------------------------------------------------------

// (Public)
float World::GetFriction() const
{
	return friction;
}

// (Public) 
float World::GetGravity() const
{
	return gravity;
}

// (Public)
float World::GetTimeStep() const
{
	return timeStep;
}

