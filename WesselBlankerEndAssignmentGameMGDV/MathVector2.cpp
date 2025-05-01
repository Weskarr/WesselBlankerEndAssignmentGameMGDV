
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

// (Public)
MathVector2::MathVector2(float x, float y) : x(x), y(y) {}

#pragma endregion

// ======================= ACCESORS =========================

#pragma region [Public]

// (Public) 
MathVector2 MathVector2::operator+(const MathVector2& other) const
{
	// Addition to CustomVector2.
	return MathVector2(x + other.x, y + other.y);
}

// (Public) 
MathVector2 MathVector2::operator-(const MathVector2& other) const
{
	// Subtraction to CustomVector2.
	return MathVector2(x - other.x, y - other.y);
}

// (Public) 
MathVector2 MathVector2::operator*(float scalar) const
{
	// Scalar Multiplication to CustomVector2.
	return MathVector2(x * scalar, y * scalar);
}

// (Public) 
MathVector2 MathVector2::operator/(float scalar) const
{
	// Scalar Division to CustomVector2.
	return MathVector2(x / scalar, y / scalar);
}

// (Public)
float MathVector2::Magnitude() const
{
	// Magnitude of the CustomVector2.
	return std::sqrt(x * x + y * y);
}

// (Public) 
MathVector2 MathVector2::Normalized() const
{
	// Normalize the CustomVector2 (convert it to unit length).
	float mag = Magnitude();
	return (mag > 0) ? *this / mag : MathVector2(0, 0);
}

// (Public) 
void MathVector2::Print() const
{
	// Print the CustomVector2 for debugging.
	std::cout << "CustomVector2(" << x << ", " << y << ")\n";
}

sf::Vector2f MathVector2::ToSFML() const {
	return sf::Vector2f(x, y);
}

#pragma endregion

// ======================= SETTERS =========================

#pragma region [Public]

// (Public)
void MathVector2::SetMathVector2(const MathVector2& newMathVector2)
{
	x = newMathVector2.x;
	y = newMathVector2.y;
}

void MathVector2::SetOnlyX(float newX)
{
	x = newX;
}
void MathVector2::SetOnlyY(float newY)
{
	y = newY;
}

#pragma endregion

// ======================= GETTERS =========================

#pragma region [Public]

// (Public)
MathVector2 MathVector2::GetMathVector2() const
{
	return MathVector2(x, y);
}

float MathVector2::GetOnlyX() const
{
	return x;
}
float MathVector2::GetOnlyY() const
{
	return y;
}

#pragma endregion