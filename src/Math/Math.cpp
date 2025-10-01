#include <math.h>
#include "Math/Math.h"

namespace Math
{
	Vector2 getSumOfVectors(Vector2 v1, Vector2 v2)
	{
		return { v1.x + v2.x, v1.y + v2.y };
	}

	void invert(float& num)
	{
		num *= -1;
	}

	Vector2 getNormalizedVector(Vector2 v)
	{
		float magnitude = getMagnitude(v);
		float descalate = 0.0f;

		if (magnitude > 0)
		{
			descalate = 1.0f / magnitude;
			v.x *= descalate;
			v.y *= descalate;
		}

		return v;
	}

	float getMagnitude(Vector2 v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	Vector2 getMultipliedVector(Vector2 v, int mult)
	{
		return { v.x * mult, v.y * mult };
	}
}
