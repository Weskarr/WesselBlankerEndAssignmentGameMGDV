
/*
	File Type: "Source"
	Made by: "Wessel Blanker"
	Started on: "30-04-2025"
	About: "This is my custom Vector2 class."
*/

#pragma region included Files

// Included Header File:
#include "MathVector2.h"

#pragma endregion

// ======================= CONSTRUCTORS =========================

#pragma region [Public]

// Constructs this MathVector2.
MathVector2::MathVector2(float x, float y) : x(x), y(y) {}

#pragma endregion

// ======================= ACCESORS =========================

#pragma region [Public]

// Operator for MathVector2 Additions (Vector + Vector).
MathVector2 MathVector2::operator+(const MathVector2& other) const
{
	return MathVector2(x + other.x, y + other.y);
}

// Operator for MathVector2 Subtractions (Vector - Vector).
MathVector2 MathVector2::operator-(const MathVector2& other) const
{
	return MathVector2(x - other.x, y - other.y);
}

// Operator for MathVector2 Multiplications (Vector * Scalar).
MathVector2 MathVector2::operator*(float scalar) const
{
	return MathVector2(x * scalar, y * scalar);
}

// Operator for MathVector2 Divisions (Vector / Scalar).
MathVector2 MathVector2::operator/(float scalar) const
{
	return MathVector2(x / scalar, y / scalar);
}

// Calculates and Gets a Magnitude Value.
float MathVector2::Magnitude() const
{
	return std::sqrt(x * x + y * y);
}

// Calculates and Gets a Normalized Value.
MathVector2 MathVector2::Normalized() const
{
	float mag = Magnitude();
	return (mag > 0) ? *this / mag : MathVector2(0, 0);
}

// Debug Prints the CustomVector2.
void MathVector2::Print() const
{
	std::cout << "CustomVector2(" << x << ", " << y << ")\n";
}

// Converts MathVector2 to SFML Vector.
sf::Vector2f MathVector2::ToSFML() const 
{
	return sf::Vector2f(x, y);
}

#pragma endregion

// ======================= SETTERS =========================

#pragma region [Public]

// Sets given values for this MathVector2.
void MathVector2::SetMathVector2(const MathVector2& newMathVector2)
{ x = newMathVector2.x; y = newMathVector2.y; }

// Sets a given Only X Value of this MathVector2.
void MathVector2::SetOnlyX(float newX)
{ x = newX; }

// Sets a given Only Y Value of this MathVector2.
void MathVector2::SetOnlyY(float newY)
{ y = newY; }

#pragma endregion

// ======================= GETTERS =========================

#pragma region [Public]

// Gets the Full MathVector2.
MathVector2 MathVector2::GetMathVector2() const
{ return MathVector2(x, y); }

// Gets the Only X Value of this MathVector2.
float MathVector2::GetOnlyX() const
{ return x; }

// Gets the Only Y Value of this MathVector2.
float MathVector2::GetOnlyY() const
{ return y; }

#pragma endregion