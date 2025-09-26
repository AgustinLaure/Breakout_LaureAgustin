#include "Paddle.h"
#include "Screen.h"

namespace Paddle
{
	void move(Paddle& paddle, float delta)
	{
		Math::Vector2 newPosition = GetSumOfVectors(paddle.position, { paddle.direction.x * paddle.speed * delta, paddle.direction.y * paddle.speed * delta });

		if (newPosition.x > 0 && newPosition.x + paddle.width < Screen::width &&
			newPosition.y + paddle.height < Screen::height)
		{
			paddle.position = newPosition;
		}
	}

	void draw(Paddle& paddle)
	{
		slRectangleFill(paddle.position.x, paddle.position.y, paddle.width, paddle.height, paddle.color);
	}
}