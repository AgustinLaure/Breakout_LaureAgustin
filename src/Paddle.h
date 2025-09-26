#pragma once
#include "Math.h"
#include "Color.h"
#include "sl.h"

namespace Paddle
{
	const Math::Vector2 paddleInitialPos = {200,120};

	const float paddleInitialWidth = 100;
	const float paddleInitialHeight = 30;

	struct Paddle
	{
		Math::Vector2 position = paddleInitialPos;
		Math::Vector2 direction = {0, 1};
		float speed = 0.0f;
		ColorInfo::ColorsName color = ColorInfo::ColorsName::WHITE;
		float width = paddleInitialWidth;
		float height = paddleInitialHeight;
	};

	void update(Paddle& paddle, float delta);
	void move(Paddle& paddle, float delta);
	void draw(Paddle& paddle);
}

