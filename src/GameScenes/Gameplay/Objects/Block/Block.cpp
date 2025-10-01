#include "sl.h"
#include "GameScenes/Gameplay/Objects/Block/Block.h"
#include "Screen/Screen.h"
#include "Math/Math.h"
#include "GameScenes/Gameplay/Objects/Paddle/Paddle.h"
#include "Player/Player.h"

namespace Block
{
	static float distanceBetweenBlocksX = Screen::getWidthRelativeValue(intendedDistBetweenBlocksX);
	static float distanceBetweenBlocksY = Screen::getHeightRelativeValue(intendedDistBetweenBlocksY);

	float blockWidth = Screen::getWidthRelativeValue(intendedBlockWidth);
	float blockHeight = Screen::getHeightRelativeValue(intendedBlockHeight);
	Math::Vector2 position = { Screen::getWidthRelativeValue(intendedDistFromSide), Screen::height * (Screen::intendedHeight - intendedDistFromTop) / Screen::intendedHeight };
	int initialHealth = 2;
	float initialColorOpacity = 1.0f;
	float initialPointsDrop = 30.0f;

	void setupBlocks(Block blocks[])
	{
		int blocksRowCol = sqrt(blockAmount);


		for (int row = 0; row < blocksRowCol; row++)
		{
			for (int col = 0; col < blocksRowCol; col++)
			{
				Block currentBlockPos = blocks[col + row * blocksRowCol];

				blocks[col + row * blocksRowCol].body.position = Math::getSumOfVectors(currentBlockPos.body.position, { (position.x + distanceBetweenBlocksX) * col, -(blockHeight + distanceBetweenBlocksY) * row });
				blocks[col + row * blocksRowCol].pointsDrop = initialPointsDrop - (pointsDecreseValue * row);
				if ((col + row) % 2 == 0)
				{
					blocks[col + row * blocksRowCol].color = Color::ColorsName::YELLOW;
				}
				else
				{
					blocks[col + row * blocksRowCol].color = Color::ColorsName::RED;
				}

				if (rand() % 100 <= Powerup::powerUpChance)
				{
					blocks[col + row * blocksRowCol].powerUp = Powerup::PowerupType(rand() % Powerup::maxPowerups);
					blocks[col + row * blocksRowCol].hasPowerup = true;
					blocks[col + row * blocksRowCol].color = Powerup::powerupColors[int(blocks[col + row * blocksRowCol].powerUp)];
				}
			}
		}
	}

	void updateBlocks(Block block[], Powerup::Powerup powerups[Powerup::maxPowerups], int& score)
	{
		for (int curr = 0; curr < blockAmount; curr++)
		{
			if (shouldLive(block[curr].currentHealth))
			{
				block[curr].colorOpacity = initialColorOpacity - (block[curr].maxHealth - block[curr].currentHealth) * deOpacityValue;
			}
			else if (block[curr].isAlive)
			{
				block[curr].isAlive = false;
				Player::addScore(score, block[curr].pointsDrop);

				if (block[curr].hasPowerup)
				{
					powerups[int(block[curr].powerUp)].isActive = true;
				}
			}
		}
	}

	void drawBlocks(Block block[])
	{
		for (int curr = 0; curr < blockAmount; curr++)
		{
			if (block[curr].isAlive)
			{
				Forms::Rectangle currentBody = block[curr].body;

				Screen::setForeColor(block[curr].color, block[curr].colorOpacity);
				slRectangleFill(currentBody.position.x, currentBody.position.y, currentBody.width, currentBody.height);
				Screen::setForeDeaultColor();
			}
		}
	}

	void takeDamage(int& currentHealth, int damage)
	{
		currentHealth -= damage;
	}

	bool shouldLive(int currentHealth)
	{
		return currentHealth > 0;
	}

	void resetBlocks(Block block[])
	{
		for (int i = 0; i < blockAmount; i++)
		{
			block[i].colorOpacity = initialColorOpacity;
			block[i].currentHealth = initialHealth;
			block[i].isAlive = true;
		}
	}

	bool areRemaining(Block block[])
	{
		for (int i = 0; i < blockAmount; i++)
		{
			if (block[i].isAlive)
			{
				return true;
			}
		}

		return false;
	}
}
