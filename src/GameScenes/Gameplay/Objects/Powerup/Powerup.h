#pragma once

#include "Color/Color.h"

namespace Powerup
{
	enum class PowerupType
	{
		BetterAim,
		WiderPaddle,
		BiggerBall
	};

	struct Powerup
	{
		PowerupType type;
		bool isActive;
	};

	const float betterAimMult = 4.0f;
	const float paddleGrowOnWiderPaddle = 40.0f;
	const float ballGrowONBiggerBall = 4.0f;
	const float powerUpChance = 10.0f;
	const int maxPowerups = 3;

	const Color::ColorsName powerupColors[maxPowerups] =
	{
		Color::ColorsName::VIOLET,
		Color::ColorsName::BLUE,
		Color::ColorsName::LIGHTBLUE
	};
}
