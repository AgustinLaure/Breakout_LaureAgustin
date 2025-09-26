#include "Paddle.h"
#include "Screen.h"

namespace Paddle
{
	void update(Paddle& paddle, float delta)
	{

		paddle.direction = { 0,0 };

		if (slGetKey('W'))
		{
			paddle.direction.y +=1;
		}
		if (slGetKey('A'))
		{
			paddle.direction.x -=1;
		}
		if (slGetKey('S'))
		{
			paddle.direction.y -= 1;
		}
		if (slGetKey('D'))
		{
			paddle.direction.x += 1;
		}

		move(paddle, delta);
	}

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
		slRectangleFill(paddle.position.x, paddle.position.y, paddle.width, paddle.height);
	}
}