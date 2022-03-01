#pragma once
#include <cmath>

//Quick class to hold some math I might need to use that's not supported by the standard library.
class Math
{
public:
	static float distanceBetween(float x1, float y1, float x2, float y2); //distance between two 2d points
};

inline float Math::distanceBetween(float x1, float y1, float x2, float y2)
{
	return sqrt(pow((x2 - x1), 2) + 
				pow((y2 - y1), 2));
}