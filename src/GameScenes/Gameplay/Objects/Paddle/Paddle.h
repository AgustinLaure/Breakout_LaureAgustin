#pragma once
#include "Screen/Screen.h"
#include "Forms/Forms.h"
#include "Player/Player.h"

namespace Paddle
{
	const static float repositionOffset = 1.0f;
	const static float intededInitialWidth = 100.0f;
	const static float intendedInitialHeight = 5.0f;
	const static float intendedInitialSpeed = 500.0f;
	const static float intendedInitialPosX = Screen::intendedWidth / 2 - 115;
	const static float intendedInitialPosY = 50.0f;
	const float paddleInitialOpacity = 1.0f;

	extern float initialWidth;
	extern float initialHeight;
	extern float initialSpeed;
	extern Math::Vector2 initialPos;
	extern Color::ColorsName initialColor;

	struct Paddle
	{
		Forms::Rectangle body
		{
			initialPos, initialWidth, initialHeight
		};

		Math::Vector2 direction = { 1, 0 };
		float speed = initialSpeed;
		Color::ColorsName color = initialColor;
		float opacity = paddleInitialOpacity;
	};

	void update(Paddle& paddle, Powerup::Powerup& widerPaddle, Forms::Rectangle playableArea, bool& ballWasShot, Math::Vector2& ballDir, float delta, Player::Input inputs[]);
	void onBorderCollision(Paddle& paddle, Forms::Rectangle playableArea);
	void makePaddleWider(Paddle& paddle, Powerup::Powerup& widerPaddle);
	void move(Paddle& paddle, Forms::Rectangle playableArea, float delta);
	void draw(Paddle& paddle);
	void changeDirectionPaddle(Paddle& paddle, Player::Input inputs[]);
	void shootBall(Paddle paddle, bool& ballWasShot, Math::Vector2& ballDir, Player::Input inputs[]);
	void reset(Paddle& paddle);
	void fixPositionOnBorder(Forms::Rectangle& body, Forms::Rectangle playableArea);
}

