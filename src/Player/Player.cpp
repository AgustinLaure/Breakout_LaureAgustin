#include "Player/Player.h"

namespace Player
{
	void addScore(int& score, int add)
	{
		score += add;
	}

	void loseLive(int& lives)
	{
		lives -= livesLostPerOnce;
	}

	void reset(Player& player)
	{
		player.score = initialScore;
		player.loseScoreCooldown = 0.0f;
		player.lives = maxLives;
	}

	bool hasLost(int lives)
	{
		return lives <= 0;
	}
}
