#pragma once
#include "Math.h"
#include "Color.h"
#include "sl.h"

namespace Paddle
{
	struct Paddle
	{
		Math::Vector2 position = { 0,0 };
		Math::Vector2 direction = {0, 1};
		float speed = 0.0f;
		ColorInfo::ColorsName color = ColorInfo::ColorsName::WHITE;
		float height;
		float width;
	};

	void move(Paddle& paddle, float delta);
	void draw();
}

