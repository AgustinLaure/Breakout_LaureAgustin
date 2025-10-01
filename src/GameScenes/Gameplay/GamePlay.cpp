#include <string>
#include "GameScenes/Gameplay/GamePlay.h"
#include "Button/Button.h"

namespace Gameplay
{
	Math::Vector2 playableAreaPos =
	{
		Screen::getPosRelativeValue({intendedPlayableArea.position.x,intendedPlayableArea.position.y})
	};
	float playableAreaWidth = Screen::getWidthRelativeValue(intendedPlayableArea.width);
	float playableAreaHeight = Screen::getHeightRelativeValue(intendedPlayableArea.height);

	Math::Vector2 scorePos =
	{
		Screen::getPosRelativeValue({intendedScore.intendedPos.x,intendedScore.intendedPos.y })
	};
	float scoreFontSize = Screen::getHeightRelativeValue(intendedScore.intendedFontSize);

	Math::Vector2 pauseTitlePos =
	{
		Screen::getPosRelativeValue({intendedPauseTitle.intendedPos.x, intendedPauseTitle.intendedPos.y})
	};
	float pauseTitleFontSize = Screen::getHeightRelativeValue(intendedPauseTitle.intendedFontSize);

	Math::Vector2 heartPos =
	{
		Screen::getPosRelativeValue({intendedHeart.intendedPos.x, intendedHeart.intendedPos.y})
	};
	float heartFontSize = Screen::getHeightRelativeValue(intendedHeart.intendedFontSize);
	float distanceBetweenHearts = Screen::getWidthRelativeValue(intendedDistanceBetweenHearts);

	Math::Vector2 resultPos =
	{
		Screen::getPosRelativeValue({intendedResult.intendedPos.x, intendedResult.intendedPos.y })
	};
	float resultFontSize = Screen::getHeightRelativeValue(intendedResult.intendedFontSize);

	Math::Vector2 resultScorePos =
	{
		Screen::getPosRelativeValue({intendedResultScore.intendedPos.x, intendedResultScore.intendedPos.y })
	};
	float resultScoreFontSize = Screen::getHeightRelativeValue(intendedResultScore.intendedFontSize);

	Math::Vector2 resultTimePos =
	{
		Screen::getPosRelativeValue({intendedResultTime.intendedPos.x, intendedResultTime.intendedPos.y })
	};
	float resultTimeFontSize = Screen::getHeightRelativeValue(intendedResultTime.intendedFontSize);

	void gameplay(Paddle::Paddle& paddle, Ball::Ball& ball, Block::Block blocks[], Forms::Rectangle playableArea, Text::Text& score, float& timerInSec, float deltaTime, Player::Player& player, GameplayScenes& currentGameplayScene, GameScenes::GameScenes& currentGameScene, Text::Text pauseTitle, Text::Text heart, GameplayButton resumeButton, GameplayButton menuButton, Text::Text& result, Text::Text& resultScore, Text::Text& resultTime, GameplayButton& backMenu)
	{
		switch (currentGameplayScene)
		{
		case Gameplay::GameplayScenes::Playing:
			timerInSec += 1 * deltaTime;
			Paddle::update(paddle, player.powerups[int(Powerup::PowerupType::WiderPaddle)], playableArea, ball.wasShot, ball.direction, deltaTime, player.inputs);
			Ball::update(ball, paddle, player.powerups, playableArea, blocks, player.lives, deltaTime);
			Block::updateBlocks(blocks, player.powerups, player.score);
			updateScore(score, player, timerInSec);
			playingUpdate(blocks, player.inputs, player.lives, currentGameplayScene, player.hasLost);

			drawPlayableArea(playableArea);
			Paddle::draw(paddle);
			Ball::draw(ball);
			Block::drawBlocks(blocks);
			drawScore(score);
			drawLives(heart, player.lives);
			break;

		case Gameplay::GameplayScenes::Pause:
			pauseUpdate(resumeButton, menuButton, currentGameplayScene, currentGameScene, player.inputs);
			drawPlayableArea(playableArea);
			Paddle::draw(paddle);
			Ball::draw(ball);
			Block::drawBlocks(blocks);
			drawScore(score);
			drawLives(heart, player.lives);
			pauseDraw(pauseTitle, resumeButton, menuButton);
			break;

		case Gameplay::GameplayScenes::Ended:
			endedUpdate(backMenu, currentGameScene, currentGameplayScene, player.inputs);
			endedDraw(result, resultScore, resultTime, backMenu, timerInSec, player);
			break;

		default:
			timerInSec = 0;
			Player::reset(player);
			Paddle::reset(paddle);
			Ball::reset(ball, paddle);
			Block::resetBlocks(blocks);
			currentGameScene = GameScenes::GameScenes::MainMenu;
			currentGameplayScene = GameplayScenes::Playing;
			break;
		}
	}

	void playingUpdate(Block::Block blocks[], Player::Input inputs[], int remainingLives, GameplayScenes& currentGameplayScene, bool& hasLost)
	{
		if (inputs[int(Player::PossibleKeys::Escape)].eventIsJustPressed)
		{
			currentGameplayScene = GameplayScenes::Pause;
		}

		hasLost = Player::hasLost(remainingLives);

		if (hasLost || !Block::areRemaining(blocks))
		{
			currentGameplayScene = GameplayScenes::Ended;
		}
	}

	void drawPlayableArea(Forms::Rectangle playableArea)
	{
		slRectangleOutline(playableArea.position.x, playableArea.position.y, playableArea.width, playableArea.height);
	}

	void updateScore(Text::Text& scoreText, Player::Player& player, float timerInSec)
	{
		updateScoreText(scoreText, player.score);
		updateScoreNum(player.score, player.loseScoreCooldown, timerInSec);
	}

	void updateScoreText(Text::Text& scoreText, int& score)
	{
		float prevWidth = 0.0f;
		float actualWidth = 0.0f;

		slSetFont(scoreText.fontId, scoreText.fontSize);
		prevWidth = slGetTextWidth(scoreText.text.c_str());

		scoreText.text = intendedScore.text + std::to_string(score);

		slSetFont(scoreText.fontId, scoreText.fontSize);
		actualWidth = slGetTextWidth(scoreText.text.c_str());

		scoreText.position.x += (actualWidth - prevWidth) / 2;
	}

	void updateScoreNum(int& scoreNum, float& minusScoreCooldown, float timerInSec)
	{
		if (timerInSec - minusScoreCooldown >= Player::timeBetweenScoreLost)
		{
			minusScoreCooldown = timerInSec;
			if (scoreNum > 0)
			{
				scoreNum -= Player::scoreLostPerCooldown;
			}
		}
	}

	void drawScore(Text::Text score)
	{
		Text::drawText(score);
	}

	void pauseUpdate(GameplayButton& resumeButton, GameplayButton& menuButton, GameplayScenes& currentGameplayScene, GameScenes::GameScenes& currentGameScene, Player::Input inputs[])
	{
		gameplayButtonLogic(resumeButton, resumeButtonIntended, inputs, currentGameplayScene, currentGameScene);
		gameplayButtonLogic(menuButton, menuButtonIntended, inputs, currentGameplayScene, currentGameScene);
	}

	void gameplayButtonLogic(GameplayButton& gameplayButton, GameplayButtonIntended intended, Player::Input inputs[], GameplayScenes& currentGameplayScene, GameScenes::GameScenes& currentGameScene)
	{
		gameplayButton.button.isPressed = false;
		gameplayButton.button.text.opacity = intended.opacity;

		if (Forms::isInsideRectangle({ float(slGetMouseX()), float(slGetMouseY()) }, gameplayButton.button.area))
		{
			gameplayButton.button.text.opacity = intended.opacity - Button::onHoverOpacity;

			if (inputs[int(Player::PossibleKeys::LeftClick)].eventIsHold)
			{
				gameplayButton.button.text.opacity = intended.opacity - Button::onSelectOpacity;
			}
			if (inputs[int(Player::PossibleKeys::LeftClick)].eventIsJustReleased &&
				inputs[int(Player::PossibleKeys::LeftClick)].isValid)
			{
				currentGameScene = gameplayButton.pointingGameScene;
				currentGameplayScene = gameplayButton.pointingGameplayScene;
				inputs[int(Player::PossibleKeys::LeftClick)].isValid = false;
			}

			if (inputs[int(Player::PossibleKeys::LeftClick)].eventIsUp)
			{
				inputs[int(Player::PossibleKeys::LeftClick)].isValid = true;
			}
		}
	}

	void pauseDraw(Text::Text pauseTitle, GameplayButton resumeButton, GameplayButton menuButton)
	{
		Text::drawText(pauseTitle);
		Text::drawText(resumeButton.button.text);
		Text::drawText(menuButton.button.text);
	}

	void endedUpdate(GameplayButton& backMenu, GameScenes::GameScenes& currentGameScene, GameplayScenes& currentGameplayScene, Player::Input inputs[])
	{
		gameplayButtonLogic(backMenu, resultBackMenuIntended, inputs, currentGameplayScene, currentGameScene);
	}

	void endedDraw(Text::Text result, Text::Text resultScore, Text::Text resultTime, GameplayButton backMenu, int timeInSeconds, Player::Player player)
	{
		if (player.hasLost)
		{
			result.text = "YOU LOST";
			result.color = Color::ColorsName::RED;
		}
		else
		{
			result.text = "YOU WON";
			result.color = Color::ColorsName::GREEN;
		}
		resultScore.text = intendedResultScore.text + std::to_string(player.score);
		resultTime.text = intendedResultTime.text + std::to_string(timeInSeconds);

		Text::drawText(result);
		Text::drawText(resultScore);
		Text::drawText(resultTime);
		Text::drawText(backMenu.button.text);
	}

	void initGameplayButton(GameplayButton& mainMenuButton, GameplayButtonIntended intendedButton)
	{
		mainMenuButton.button.text.position =
		{
			Screen::getWidthRelativeValue(intendedButton.pos.x),
			Screen::getHeightRelativeValue(intendedButton.pos.y)
		};

		mainMenuButton.button.text.fontId = slLoadFont(intendedButton.fontName.c_str());
		mainMenuButton.button.text.fontSize = Screen::getWidthRelativeValue(intendedButton.fontSize);
		mainMenuButton.button.text.text = intendedButton.text;
		mainMenuButton.button.text.color = intendedButton.color;
		mainMenuButton.button.text.opacity = intendedButton.opacity;
		slSetFont(mainMenuButton.button.text.fontId, mainMenuButton.button.text.fontSize);
		mainMenuButton.button.area.width = slGetTextWidth(mainMenuButton.button.text.text.c_str());
		mainMenuButton.button.area.height = slGetTextHeight(mainMenuButton.button.text.text.c_str());
		mainMenuButton.button.area.position = { mainMenuButton.button.text.position.x, mainMenuButton.button.text.position.y + mainMenuButton.button.area.height };
		mainMenuButton.button.isPressed = false;
		mainMenuButton.pointingGameScene = intendedButton.pointingGameScene;
		mainMenuButton.pointingGameplayScene = intendedButton.pointingGameplayScene;
	}

	void drawLives(Text::Text heart, int currentLives)
	{
		for (int i = 0; i < currentLives; i++)
		{
			Screen::setForeColor(heart.color, heart.opacity);

			slSetFont(heart.fontId, heart.fontSize);
			heart.position.x -= slGetTextWidth(heart.text.c_str()) / 2;
			heart.position.x = heartPos.x + distanceBetweenHearts * i;
			slSetFontSize(heart.fontSize);
			slText(heart.position.x, heart.position.y, heart.text.c_str());

			Screen::setForeDeaultColor();
		}
	}
}
