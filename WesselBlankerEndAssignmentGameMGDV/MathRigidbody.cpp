
/*
	File Type: "Source"
	Made by: "Wessel Blanker"
	Started on: "30-04-2025"
	About: "This is my custom Rigidbody class."
*/

#pragma region included Files

// Included Header File:
#include "MathRigidbody.h"

#pragma endregion

// ======================= CONSTRUCTORS =========================

#pragma region [Public]

// Constructs this MathRigidbody.
MathRigidbody::MathRigidbody(World* world,
    MathVector2 position,
    MathVector2 velocity,
    MathVector2 acceleration,
    float mass)
    : world(world), position(position), velocity(velocity), acceleration(acceleration), mass(mass) {
}

#pragma endregion

// ======================= ACCESORS =========================

#pragma region [Public]

// Applies force to the Rigidbody.
void MathRigidbody::AddForce(const MathVector2& force) 
{
    acceleration = force / mass;
}

// Debug Prints the Position and Velocity.
void MathRigidbody::Print() const
{
    std::cout << "Position: ";
    position.Print();
    std::cout << "Velocity: ";
    velocity.Print();
}

#pragma endregion

// ======================= UPDATING =========================

#pragma region [Private]

// Is the Main Update Function.
void MathRigidbody::Update()
{
    // Quick safety check..
    if (!world) 
    {
        std::cerr << "Error: MathRigidbody world is null!\n";
        return;
    }

    // Update Gravity Force.
    AddForce(MathVector2(0, mass * world->GetGravity()));

    // Update Friction.
    velocity = velocity * (1.0f - world->GetFriction());

    // Update Velocity based on Acceleration.
    velocity = velocity + (acceleration * world->GetTimeStep());

    // Update Position based on Velocity.
    position = position + (velocity * world->GetTimeStep());

    // Reset Acceleration.
    acceleration = MathVector2(0, 0);
}

#pragma endregion

// ======================= SETTERS =========================

#pragma region [Public]

// Sets a given Position MathVector2.
void MathRigidbody::SetPosition(const MathVector2& newPosition)
{
    position = newPosition;
}

// Sets a given Velocity MathVector2.
void MathRigidbody::SetVelocity(const MathVector2& newVelocity)
{
    velocity = newVelocity;
}

// Sets a given Acceleration MathVector2.
void MathRigidbody::SetAcceleration(const MathVector2& newAcceleration)
{
    acceleration = newAcceleration;
}

// Sets a given Mass Value.
void MathRigidbody::SetMass(float newMass)
{
    mass = newMass;
}

#pragma endregion

// ======================= GETTERS =========================

#pragma region [Public]

// Gets the Position MathVector2.
MathVector2 MathRigidbody::GetPosition() const
{
    return position;
}

// Gets the Velocity MathVector2.
MathVector2 MathRigidbody::GetVelocity() const
{
    return velocity;
}

// Gets the Acceleration MathVector2.
MathVector2 MathRigidbody::GetAcceleration() const
{
    return acceleration;
}

// Gets the Mass Value.
float MathRigidbody::GetMass() const
{
    return mass;
}

#pragma endregion