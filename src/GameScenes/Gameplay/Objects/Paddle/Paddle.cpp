#include "GameScenes/Gameplay/Objects/Paddle/Paddle.h"

namespace Paddle
{
	Math::Vector2 initialPos = Screen::getPosRelativeValue({ intendedInitialPosX ,intendedInitialPosY });
	float initialWidth = Screen::getWidthRelativeValue(intededInitialWidth);
	float initialHeight = Screen::getHeightRelativeValue(intendedInitialHeight);
	float initialSpeed = Screen::getWidthRelativeValue(intendedInitialSpeed);
	Color::ColorsName initialColor = Color::ColorsName::WHITE;

	void update(Paddle& paddle, Powerup::Powerup& widerPaddle, Forms::Rectangle playableArea, bool& ballWasShot, Math::Vector2& ballDir, float delta, Player::Input inputs[])
	{
		changeDirectionPaddle(paddle, inputs);
		shootBall(paddle, ballWasShot, ballDir, inputs);
		
		makePaddleWider(paddle, widerPaddle);
		onBorderCollision(paddle, playableArea);

		move(paddle, playableArea, delta);
	}

	void onBorderCollision(Paddle& paddle, Forms::Rectangle playableArea)
	{
		if (paddle.body.position.x - paddle.body.width / 2 <= playableArea.position.x - playableArea.width / 2
			|| paddle.body.position.x + paddle.body.width / 2 >= playableArea.position.x + playableArea.width / 2)
		{
			fixPositionOnBorder(paddle.body, playableArea);
		}
	}

	void makePaddleWider(Paddle& paddle, Powerup::Powerup& widerPaddle)
	{
		if (widerPaddle.isActive)
		{
			paddle.body.width += Powerup::paddleGrowOnWiderPaddle;
			widerPaddle.isActive = false;
		}
	}

	void move(Paddle& paddle, Forms::Rectangle playableArea, float delta)
	{
		Math::Vector2 newPosition = getSumOfVectors(paddle.body.position, { paddle.direction.x * paddle.speed * delta, paddle.direction.y * paddle.speed * delta });

		if (newPosition.x - paddle.body.width / 2 > playableArea.position.x - playableArea.width / 2
			&& newPosition.x + paddle.body.width / 2 < playableArea.position.x + playableArea.width / 2
			&& newPosition.y - paddle.body.height / 2 > playableArea.position.y - playableArea.height / 2
			&& newPosition.y + paddle.body.height / 2 < playableArea.position.y + playableArea.height / 2)
		{
			paddle.body.position = newPosition;

		}
	}

	void draw(Paddle& paddle)
	{
		Screen::setForeColor(paddle.color, paddle.opacity);
		slRectangleFill(paddle.body.position.x, paddle.body.position.y, paddle.body.width, paddle.body.height);
		Screen::setForeDeaultColor();
	}

	void changeDirectionPaddle(Paddle& paddle, Player::Input inputs[])
	{
		paddle.direction = { 0,0 };

		if (inputs[int(Player::PossibleKeys::LeftKey)].eventIsHold)
		{
			paddle.direction.x -= 1;
		}

		if (inputs[int(Player::PossibleKeys::RightKey)].eventIsHold)
		{
			paddle.direction.x += 1;
		}
	}

	void shootBall(Paddle paddle, bool& ballWasShot, Math::Vector2& ballDir, Player::Input inputs[])
	{
		if (inputs[int(Player::PossibleKeys::Tab)].eventIsJustPressed)
		{
			if (!ballWasShot)
			{
				ballWasShot = true;
				ballDir = Math::getSumOfVectors(ballDir, paddle.direction);
			}
		}
	}

	void reset(Paddle& paddle)
	{
		paddle.body.position = initialPos;
		paddle.body.width = initialWidth;
		paddle.body.height = initialHeight;
		paddle.direction = { 0,0 };
		paddle.speed = initialSpeed;
		paddle.color = initialColor;
		paddle.opacity = paddleInitialOpacity;
	}

	void fixPositionOnBorder(Forms::Rectangle& body, Forms::Rectangle playableArea)
	{
		Math::Vector2 howMuchLeft = Forms::getHowMuchLeft(body, playableArea);

		if (howMuchLeft.x > 0)
		{
			howMuchLeft.x += repositionOffset;
		}
		else
		{
			howMuchLeft.x -= repositionOffset;
		}

		if (howMuchLeft.y > 0)
		{
			howMuchLeft.y += repositionOffset;
		}
		else
		{
			howMuchLeft.y -= repositionOffset;
		}

		body.position = Math::getSumOfVectors(body.position, howMuchLeft);
	}
}