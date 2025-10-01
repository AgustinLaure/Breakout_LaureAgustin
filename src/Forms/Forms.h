#pragma once
#include "Math/Math.h"

namespace Forms
{
	struct Circle
	{
		Math::Vector2 position = {};
		float radius = 1;
		int vertices = 1;
	};

	struct Rectangle
	{
		Math::Vector2 position = {};
		float width = 1;
		float height = 1;
	};

	bool isCollidingWithRectangle(Circle circle, Rectangle rect);
	Math::Vector2 getHowMuchEntered(Circle circle, Rectangle rect);
	Math::Vector2 getHowMuchLeft(Circle body, Rectangle playableArea);
	Math::Vector2 getHowMuchLeft(Rectangle body, Rectangle playableArea);
	bool isInsideRectangle(Math::Vector2 point, Rectangle rectangle);
	void place(Forms::Circle& body, Math::Vector2 pos);
}

