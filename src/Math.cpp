#include "Math.h"

namespace Math
{
	Vector2 GetSumOfVectors(Vector2 v1, Vector2 v2)
	{
		return { v1.x + v2.x, v1.y + v2.y };
	}
}
