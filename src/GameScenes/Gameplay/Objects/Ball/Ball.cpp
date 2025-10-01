#include "GameScenes/Gameplay/Objects/Ball/Ball.h"
#include "Screen/Screen.h"

namespace Ball
{
	Math::Vector2 initialPos = { Screen::width / 2, Screen::height * (intendedBallDist + intendedInitialRadius) / Screen::intendedHeight };
	float initialRadius = Screen::getWidthRelativeValue(intendedInitialRadius);
	float initialSpeed = Screen::getWidthRelativeValue(intendedInitialSpeed);
	int initialVertices = 100;
	Color::ColorsName initialColor = Color::ColorsName::WHITE;
	bool initialWasShot = false;
	static float repositionOffset = intendedInitialSpeed * intendedRepositionOffset / intendedInitialSpeed;
	int initialDamage = 1;

	void update(Ball& ball, Paddle::Paddle paddle, Powerup::Powerup powerups[], Forms::Rectangle playableArea, Block::Block blocks[], int& playerLives, float delta)
	{
		move(ball, paddle.body.position, delta);

		if (ball.wasShot)
		{
			onBorderCollision(ball, paddle, playableArea, playerLives);
			onPaddleCollision(ball, powerups[int(Powerup::PowerupType::BetterAim)], paddle.body);
			for (int block = 0; block < Block::blockAmount; block++)
			{
				if (blocks[block].isAlive)
				{
					onBlockCollision(ball, blocks[block]);
				}
			}
			makeBallBigger(ball, powerups[int(Powerup::PowerupType::BiggerBall)]);
		}
	}

	void move(Ball& ball, Math::Vector2 paddlePos, float delta)
	{
		if (ball.wasShot)
		{
			ball.body.position = getSumOfVectors(ball.body.position, { ball.direction.x * ball.speed * delta, ball.direction.y * ball.speed * delta });
		}
		else if (!ball.wasShot)
		{
			ball.body.position = paddlePos;
			ball.body.position.y += initialPos.y;
		}
	}

	void makeBallBigger(Ball& ball, Powerup::Powerup& biggerBall)
	{
		if (biggerBall.isActive)
		{
			ball.body.radius += Powerup::ballGrowONBiggerBall;
			biggerBall.isActive = false;
		}
	}

	void draw(Ball ball)
	{
		Screen::setForeColor(ball.color, ball.opacity);
		slSprite(ball.spriteId,ball.body.position.x, ball.body.position.y, ball.body.radius * 2, ball.body.radius*2);
		Screen::setForeDeaultColor();
	}

	void onBorderCollision(Ball& ball, Paddle::Paddle paddle, Forms::Rectangle playableArea, int& playerLives)
	{
		bool wentOut = false;

		if (ball.body.position.x - ball.body.radius <= playableArea.position.x - playableArea.width / 2
			|| ball.body.position.x + ball.body.radius >= playableArea.position.x + playableArea.width / 2)
		{
			Math::invert(ball.direction.x);
			fixPositionOnBorder(ball.body, playableArea);
		}
		if (ball.body.position.y - ball.body.radius <= playableArea.position.y - playableArea.height / 2
			|| ball.body.position.y + ball.body.radius >= playableArea.position.y + playableArea.height / 2)
		{
			if (ball.body.position.y - ball.body.radius <= playableArea.position.y - playableArea.height / 2)
			{
				wentOut = true;
			}
			Math::invert(ball.direction.y);
			fixPositionOnBorder(ball.body, playableArea);
		}

		if (wentOut)
		{
			reset(ball, paddle);
			Player::loseLive(playerLives);
		}
	}

	void fixPositionOnBorder(Forms::Circle& body, Forms::Rectangle playableArea)
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

	void onPaddleCollision(Ball& ball, Powerup::Powerup betterAim, Forms::Rectangle rect)
	{
		if (Forms::isCollidingWithRectangle(ball.body, rect) && !ball.isColliding)
		{
			if (!ball.isColliding)
			{
				changeDirectionPaddle(ball, betterAim, rect);
				fixPositionOnRectangle(ball.body, rect);
				ball.isColliding = true;
			}
			else
			{
				ball.isColliding = false;
			}
		}
	}

	void onBlockCollision(Ball& ball, Block::Block& block)
	{
		if (Forms::isCollidingWithRectangle(ball.body, block.body))
		{
			if (!ball.isColliding)
			{
				changeDirectionBlock(ball, block.body);
				fixPositionOnRectangle(ball.body, block.body);
				damageBlock(block.currentHealth, ball.damage);
			}
			ball.isColliding = true;
		}
		else
		{
			ball.isColliding = false;
		}
	}

	void changeDirectionPaddle(Ball& ball, Powerup::Powerup betterAim, Forms::Rectangle paddleBody)
	{
		Math::Vector2 ballDir = { paddleBody.position.x - ball.body.position.x , paddleBody.position.y - ball.body.position.y };

		if (betterAim.isActive)
		{
			ballDir.x = ballDir.x / Powerup::betterAimMult;
		}

		ball.direction = getNormalizedVector(ballDir);

		ball.direction = getMultipliedVector(ball.direction, -1);

		if (ball.direction.x == 0 && (ball.direction.y == 1 || ball.direction.y == 0))
		{
			ball.direction.x -= 0.01f;
		}
	}

	void changeDirectionBlock(Ball& ball, Forms::Rectangle blockBody)
	{
		ball.body.position.x = trunc(ball.body.position.x);
		ball.body.position.y = trunc(ball.body.position.y);

		if (ball.body.position.x <= blockBody.position.x - blockBody.width / 2
			|| ball.body.position.x >= blockBody.position.x + blockBody.width / 2)
		{
			ball.direction.x *= -1;
		}
		if (ball.body.position.y <= blockBody.position.y - blockBody.height / 2
			|| ball.body.position.y >= blockBody.position.y + blockBody.height / 2)
		{
			ball.direction.y *= -1;
		}
	}

	void fixPositionOnRectangle(Forms::Circle& body, Forms::Rectangle rect)
	{
		Math::Vector2 howMuchEntered = Forms::getHowMuchEntered(body, rect);

		if (howMuchEntered.x > 0)
		{
			howMuchEntered.x += repositionOffset;
		}
		else if (howMuchEntered.x < 0)
		{
			howMuchEntered.x -= repositionOffset;
		}

		if (howMuchEntered.y > 0)
		{
			howMuchEntered.y += repositionOffset;
		}
		else if (howMuchEntered.y < 0)
		{
			howMuchEntered.y -= repositionOffset;
		}

		body.position = Math::getSumOfVectors(body.position, howMuchEntered);
	}

	void damageBlock(int& currentHealth, int damage)
	{
		Block::takeDamage(currentHealth, damage);
	}

	void reset(Ball& ball, Paddle::Paddle paddle)
	{
		ball.body.position = { paddle.body.position.x, paddle.body.position.y + initialPos.y };
		ball.body.radius = initialRadius;
		ball.direction = initialDir;
		ball.speed = initialSpeed;
		ball.color = initialColor;
		ball.opacity = initialOpacity;
		ball.wasShot = initialWasShot;
		ball.damage = initialDamage;
		ball.isColliding = false;
	}
}