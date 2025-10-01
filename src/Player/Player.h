#pragma once
#include "sl.h"
#include "GameScenes/Gameplay/Objects/Powerup/Powerup.h"

namespace Player
{
	const int maxInputs = 5;

	enum class Device
	{
		None,
		Mouse,
		Keyboard
	};

	enum class PossibleKeys
	{
		LeftClick,
		LeftKey,
		RightKey,
		Tab,
		Escape
	};

	struct PossibleInputs
	{
		int key = 0;
		Device device = Device::None;
	};

	const PossibleInputs presetInputs[maxInputs] =
	{
		{SL_MOUSE_BUTTON_1, Device::Mouse},
		{SL_KEY_LEFT,Device::Keyboard},
		{SL_KEY_RIGHT,Device::Keyboard},
		{SL_KEY_TAB,Device::Keyboard},
		{SL_KEY_ESCAPE,Device::Keyboard}
	};

	struct Input
	{
		bool isValid = true;

		bool isDown = false;
		bool wasDown = false;

		bool eventIsUp = false;
		bool eventIsJustReleased = false;
		bool eventIsJustPressed = false;
		bool eventIsHold = false;
	};

	const float timeBetweenScoreLost = 2.0f;
	const float scoreLostPerCooldown = 1.0f;
	const float initialScore = 0.0f;
	const int maxLives = 3;
	const int livesLostPerOnce = 1;
	const int livesToLose = 0;

	struct Player
	{
		int score = initialScore;
		float loseScoreCooldown = 0.0f;
		Input inputs[maxInputs];
		int lives = maxLives;
		bool hasLost = false;
		Powerup::Powerup powerups[Powerup::maxPowerups] =
		{
			{Powerup::PowerupType::BetterAim, false},
			{Powerup::PowerupType::WiderPaddle, false},
			{Powerup::PowerupType::BiggerBall,false}
		};
	};

	const int optionSelect = SL_MOUSE_BUTTON_1;

	void addScore(int& score, int add);
	void loseLive(int& lives);
	void reset(Player& player);
	bool hasLost(int lives);
}

