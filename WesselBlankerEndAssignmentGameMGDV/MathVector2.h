
/*
	File Type: "Header"
	Made by: "Wessel Blanker"
	Started on: "30-04-2025"
	About: "This is my custom Vector2 class."
*/

/*
    Second Iteration Changes:
    1. Completely New!
*/

// Single Safety:
#pragma once

// Included Standard Libraries:
#include <cmath>
#include <iostream>



// Class:
class MathVector2
{
private:

    // Vector2 Variables:
    float x, y;

public:

    // Constructor Functions (Public):
    MathVector2(); // [DEFAULT]
    MathVector2(float x, float y); // [CUSTOM]

    // Destructor Functions (Public):
    virtual ~MathVector2();

    // Accessor Functions (Public):
    MathVector2 operator+(const MathVector2& other) const;
    MathVector2 operator-(const MathVector2& other) const;
    MathVector2 operator*(float scalar) const;
    MathVector2 operator/(float scalar) const;
    float Magnitude() const;
    MathVector2 Normalized() const;
    void Print() const;

    // Setter Functions (Public):
    void setX(float newX);
    void setY(float newY);

    // Getter Functions (Public):
    float getX() const;
    float getY() const;

};

