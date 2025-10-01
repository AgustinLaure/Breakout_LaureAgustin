#include <ctime>
#include "GameScenes/Game/Game.h"
#include "GameScenes/Gameplay/GamePlay.h"
#include "GameScenes/MainMenu/MainMenu.h"
#include "Screen/Screen.h"
#include "GameScenes/GameScenes.h"
#include "Player/Player.h"

namespace Game
{
	void game()
	{
		srand(time(0));

		slSetTextAlign(SL_ALIGN_CENTER);

		slWindow(Screen::width, Screen::height, Screen::windowName.c_str(), Screen::isFullScreen);

		Color::ColorsName gameBackColor = Color::ColorsName::BLACK;
		GameScenes::GameScenes currentGameScene = GameScenes::GameScenes::MainMenu;
		MainMenu::MainMenuScenes currentMainMenuScene = MainMenu::MainMenuScenes::Menu;

		Paddle::Paddle paddle;

		Ball::Ball ball;
		ball.spriteId = slLoadTexture(Ball::spriteName.c_str());

		Block::Block blocks[Block::blockAmount];
		Block::setupBlocks(blocks);
		Screen::setBackColor(gameBackColor);

		MainMenu::MainMenuButton mainMenuButtons[MainMenu::buttonsSize];

		for (int button = 0; button < MainMenu::buttonsSize; button++)
		{
			MainMenu::initMainMenuButton(mainMenuButtons[button], MainMenu::intendedButtons[button]);
		}

		MainMenu::MainMenuButton backButton;

		MainMenu::initMainMenuButton(backButton, MainMenu::backButtonIntended);

		Text::Text title;
		Text::initText(title, MainMenu::titlePos, MainMenu::titleFontName, MainMenu::titleFontSize, MainMenu::titleText, MainMenu::titleBaseColor, MainMenu::titleInitialOpacity);

		Text::Text credits[MainMenu::maxCreditsLines];
		Text::initText(credits[0], MainMenu::creditsPos, MainMenu::creditsFontName, MainMenu::creditsFontSize, MainMenu::creditsText, MainMenu::creditsBaseColor, MainMenu::creditsInitialOpacity);
		Text::initText(credits[1], {MainMenu::creditsPos.x, MainMenu::creditsPos.y - MainMenu::creditsDistance}, MainMenu::creditsFontName, MainMenu::creditsFontSize, MainMenu::creditsText2, MainMenu::creditsBaseColor, MainMenu::creditsInitialOpacity);

		Text::Text rules[MainMenu::maxRulesLines];
		Text::initText(rules[0], MainMenu::rulesPos, MainMenu::rulesFontName, MainMenu::rulesFontSize, MainMenu::rulesText1, MainMenu::rulesBaseColor, MainMenu::rulesInitialOpacity);
		Text::initText(rules[1], { MainMenu::rulesPos.x, MainMenu::rulesPos.y - MainMenu::rulesDistanceBetweenLines }, MainMenu::rulesFontName, MainMenu::rulesFontSize, MainMenu::rulesText2, MainMenu::rulesBaseColor, MainMenu::rulesInitialOpacity);
		Text::initText(rules[2], { MainMenu::rulesPos.x, MainMenu::rulesPos.y - MainMenu::rulesDistanceBetweenLines*2 }, MainMenu::rulesFontName, MainMenu::rulesFontSize, MainMenu::rulesText3, MainMenu::rulesBaseColor, MainMenu::rulesInitialOpacity);

		Text::Text heart;
		Text::initText(heart, Gameplay::heartPos, Gameplay::intendedHeart.fontName, Gameplay::heartFontSize, Gameplay::intendedHeart.text, Gameplay::intendedHeart.baseColor, Gameplay::intendedHeart.initialOpacity);

		Forms::Rectangle playableArea =
		{
			Gameplay::playableAreaPos, Gameplay::playableAreaWidth, Gameplay::playableAreaHeight
		};

		Text::Text score;
		Text::initText(score, Gameplay::scorePos, Gameplay::intendedScore.fontName, Gameplay::scoreFontSize, Gameplay::intendedScore.text, Gameplay::intendedScore.baseColor, Gameplay::intendedScore.initialOpacity);

		Player::Player player;

		Gameplay::GameplayScenes gameplayScene = Gameplay::GameplayScenes::Playing;

		float timerInSec = 0.0f;

		Text::Text pauseTitle;
		Text::initText(pauseTitle, Gameplay::pauseTitlePos, Gameplay::intendedPauseTitle.fontName, Gameplay::pauseTitleFontSize, Gameplay::intendedPauseTitle.text, Gameplay::intendedPauseTitle.baseColor, Gameplay::intendedPauseTitle.initialOpacity);

		Gameplay::GameplayButton resumeButton;
		Gameplay::initGameplayButton(resumeButton, Gameplay::resumeButtonIntended);

		Gameplay::GameplayButton backMenu;
		Gameplay::initGameplayButton(backMenu, Gameplay::menuButtonIntended);

		Text::Text result;
		initText(result, Gameplay::resultPos, Gameplay::intendedResult.fontName, Gameplay::resultFontSize, Gameplay::intendedResult.text, Gameplay::intendedResult.baseColor, Gameplay::intendedResult.initialOpacity);

		Text::Text resultScore;
		initText(resultScore, Gameplay::resultScorePos, Gameplay::intendedResultScore.fontName, Gameplay::resultScoreFontSize, Gameplay::intendedResultScore.text, Gameplay::intendedResultScore.baseColor, Gameplay::intendedResultScore.initialOpacity);

		Text::Text resultTime;
		initText(resultTime, Gameplay::resultTimePos, Gameplay::intendedResultTime.fontName, Gameplay::resultTimeFontSize, Gameplay::intendedResultTime.text, Gameplay::intendedResultTime.baseColor, Gameplay::intendedResultTime.initialOpacity);

		Gameplay::GameplayButton resultBackMenu;
		Gameplay::initGameplayButton(resultBackMenu, Gameplay::resultBackMenuIntended);

		while (!slShouldClose() && currentGameScene != GameScenes::GameScenes::Exit)
		{
			float deltaTime = slGetDeltaTime();

			input(player.inputs);

			switch (currentGameScene)
			{
			case GameScenes::GameScenes::MainMenu:
				MainMenu::mainMenu(mainMenuButtons, backButton, title, credits, rules, currentGameScene, currentMainMenuScene, player.inputs);
				break;

			case GameScenes::GameScenes::Gameplay:
				Gameplay::gameplay(paddle, ball, blocks, playableArea, score, timerInSec, deltaTime, player, gameplayScene, currentGameScene,pauseTitle, heart, resumeButton, backMenu, result, resultScore, resultTime, resultBackMenu);
				break;

			default:
				break;
			}

			slRender();
		}

		slClose();
	}

	void input(Player::Input inputs[])
	{
		for (int i = 0; i < Player::maxInputs; i++)
		{
			inputs[i].wasDown = inputs[i].isDown;

			switch (Player::presetInputs[i].device)
			{
			case Player::Device::Keyboard:
				inputs[i].isDown = slGetKey(Player::presetInputs[i].key);

				break;
			case Player::Device::Mouse:
				inputs[i].isDown = slGetMouseButton(Player::presetInputs[i].key);
				break;

			default:
				break;

			}

			inputs[i].eventIsUp = false;
			inputs[i].eventIsJustReleased = false;
			inputs[i].eventIsJustPressed = false;
			inputs[i].eventIsHold = false;

			if (!inputs[i].isDown && !inputs[i].wasDown)
			{
				inputs[i].eventIsUp = true;
			}
			else if (!inputs[i].isDown && inputs[i].wasDown)
			{
				inputs[i].eventIsJustReleased = true;
			}
			else if (inputs[i].isDown && !inputs[i].wasDown)
			{
				inputs[i].eventIsJustPressed = true;
			}
			else if (inputs[i].isDown && inputs[i].wasDown)
			{
				inputs[i].eventIsHold = true;
			}
		}
	}
}