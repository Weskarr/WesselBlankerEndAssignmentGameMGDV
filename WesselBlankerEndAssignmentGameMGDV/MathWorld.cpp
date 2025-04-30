
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

// (Public) [CUSTOM]
World::World(float friction = 0.1f, float gravity = 9.8f, float timeStep = 1.0f) 
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
void World::setFriction(float newFriction)
{
	friction = newFriction;
}

// (Public)
void World::setGravity(float newGravity)
{
	gravity = newGravity;
}

// (Public)
void World::setTimeStep(float newTimeStep)
{
	timeStep = newTimeStep;
}

// -------------------------------------------------------------------------------
// GETTERS
// -------------------------------------------------------------------------------

// (Public)
float World::getFriction() const
{
	return friction;
}

// (Public)
float World::getGravity() const
{
	return gravity;
}

// (Public)
float World::getTimeStep() const
{
	return timeStep;
}

