#pragma once

namespace Math
{
	struct Vector2
	{
		float x = 0.0f;
		float y = 0.0f;
	};

	Vector2 getSumOfVectors(Vector2 v1, Vector2 v2);
	void invert(float& num);
	Vector2 getNormalizedVector(Vector2 v);
	float getMagnitude(Vector2 v);
	Vector2 getMultipliedVector(Vector2 v, int mult);
}


