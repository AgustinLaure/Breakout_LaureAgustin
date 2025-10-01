#pragma once
#include "GameScenes/Gameplay/Objects/Paddle/Paddle.h"
#include "GameScenes/Gameplay/Objects/Block/Block.h"

namespace Ball
{
	const static float intendedInitialSpeed = 650.0f;
	const static float intendedRepositionOffset = 1.0f;
	const static float intendedBallDist = 20;
	const static float intendedInitialRadius = 10;
	const static float titleInitialOpacity = 1.0f;
	const static Math::Vector2 initialDir = { 0,1 };
	const static float initialOpacity = 1.0f;
	const std::string spriteName = "res/BallSprite/ballGrey.png";

	extern Math::Vector2 initialPos;
	extern float initialRadius;
	extern float initialSpeed;
	extern int initialVertices;
	extern Color::ColorsName initialColor;
	extern bool initialWasShot;
	extern int initialDamage;

	struct Ball
	{
		Forms::Circle body
		{
			initialPos, initialRadius, initialVertices
		};

		Math::Vector2 direction = initialDir;
		float speed = initialSpeed;
		Color::ColorsName color = initialColor;
		float opacity = initialOpacity;
		bool wasShot = initialWasShot;
		int damage = initialDamage;
		bool isColliding = false;
		int spriteId = 0;
	};

	void update(Ball& ball, Paddle::Paddle paddle, Powerup::Powerup powerUps[], Forms::Rectangle playableArea, Block::Block blocks[], int& playerLives, float delta);
	void move(Ball& ball, Math::Vector2 paddlePos, float delta);
	void makeBallBigger(Ball& ball, Powerup::Powerup& biggerBall);
	void draw(Ball ball);
	void onBorderCollision(Ball& ball, Paddle::Paddle paddle, Forms::Rectangle playableArea, int& playerLives);
	void fixPositionOnBorder(Forms::Circle& body, Forms::Rectangle playableArea);
	void onPaddleCollision(Ball& ball, Powerup::Powerup betterAim, Forms::Rectangle rect);
	void onBlockCollision(Ball& ball, Block::Block& block);
	void changeDirectionPaddle(Ball& ball, Powerup::Powerup betterAim, Forms::Rectangle paddleBody);
	void changeDirectionBlock(Ball& ball, Forms::Rectangle blockBody);
	void fixPositionOnRectangle(Forms::Circle& body, Forms::Rectangle rect);
	void damageBlock(int& currentHealth, int damage);
	void reset(Ball& ball, Paddle::Paddle paddle);
}

