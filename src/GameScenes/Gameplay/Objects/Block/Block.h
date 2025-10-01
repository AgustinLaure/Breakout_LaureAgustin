#pragma once

#include "Forms/Forms.h"
#include "GameScenes/Gameplay/Objects/Powerup/Powerup.h"

namespace Block
{
	static const float intendedDistFromTop = 50.0f;
	static const float intendedDistFromSide = 103.0f;
	static const float intendedDistBetweenBlocksX = 10.0f;
	static const float intendedDistBetweenBlocksY = 20.0f;
	static const float intendedBlockWidth = 100.0f;
	static const float intendedBlockHeight = 10.0f;
	static const float deOpacityValue = 0.4f;
	static const float pointsDecreseValue = 3.0f;
	const int blockAmount = 36;

	extern float blockWidth;
	extern float blockHeight;
	extern Math::Vector2 position;
	extern int initialHealth;
	extern float initialColorOpacity;
	extern float initialPointsDrop;

	struct Block
	{
		Forms::Rectangle body =
		{
			position, blockWidth, blockHeight
		};

		Color::ColorsName color = Color::ColorsName::GREEN;
		float colorOpacity = initialColorOpacity;
		int maxHealth = initialHealth;
		int currentHealth = maxHealth;
		bool isAlive = true;
		float pointsDrop = initialPointsDrop;
		Powerup::PowerupType powerUp;
		bool hasPowerup = false;
	};

	void setupBlocks(Block blocks[]);
	void updateBlocks(Block block[], Powerup::Powerup powerups[Powerup::maxPowerups], int& score);
	void drawBlocks(Block block[]);
	void takeDamage(int& currentHealth, int damage);
	bool shouldLive(int currentHealth);
	void resetBlocks(Block block[]);
	bool areRemaining(Block block[]);
	}

