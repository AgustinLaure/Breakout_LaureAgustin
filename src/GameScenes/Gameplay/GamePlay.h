#pragma once
#include "GameScenes/Gameplay/Objects/Paddle/Paddle.h"
#include "GameScenes/Gameplay/Objects/Ball/Ball.h"
#include "Player/Player.h"
#include "Button/Button.h"
#include "GameScenes/GameScenes.h"

namespace Gameplay
{
	enum class GameplayScenes
	{
		None,
		Playing,
		Pause,
		Ended
	};

	static const Forms::Rectangle intendedPlayableArea =
	{
		{(Screen::intendedWidth / 2) - 115, Screen::intendedHeight / 2},
		Screen::intendedWidth / 2 + 175,
		Screen::intendedHeight - 50
	};

	extern Math::Vector2 playableAreaPos;
	extern float playableAreaWidth;
	extern float playableAreaHeight;

	static const Text::TextIntended intendedScore =
	{
		{800,430},
		20,
		"Score: ",
		"res/ARCADE_I.TTF",
		Color::ColorsName::WHITE,
		1.0f
	};

	extern Math::Vector2 scorePos;
	extern float scoreFontSize;

	static const int pauseMaxButtons = 2;
	static const Text::TextIntended intendedPauseTitle =
	{
		{intendedPlayableArea.position.x,intendedPlayableArea.position.y+100},
		60,
		"PAUSE",
		"res/ARCADE_I.TTF",
		Color::ColorsName::WHITE,
		1.0f
	};

	extern Math::Vector2 pauseTitlePos;
	extern float pauseTitleFontSize;

	static const Text::TextIntended intendedHeart
	{
		{796,40},
		18,
		"<3",
		"res/ARCADE_I.TTF",
		Color::ColorsName::RED,
		1.0f
	};

	extern Math::Vector2 heartPos;
	extern float heartFontSize;

	const int intendedDistanceBetweenHearts = 50;

	static const Text::TextIntended intendedResult
	{
		{Screen::intendedWidth / 2, (Screen::intendedWidth / 2) - 112}
		,40
		,""
		,"res/ARCADE_I.TTF"
		,Color::ColorsName::WHITE
		,1.0f
	};
	extern Math::Vector2 resultPos;
	extern float resultFontSize;

	static const Text::TextIntended intendedResultScore
	{
		{Screen::intendedWidth / 2, (Screen::intendedWidth / 2) - 225}
		,40
		,"Score:"
		,"res/ARCADE_I.TTF"
		,Color::ColorsName::WHITE
		,1.0f
	};

	extern Math::Vector2 resultScorePos;
	extern float resultScoreFontSize;

	static const Text::TextIntended intendedResultTime
	{
		{Screen::intendedWidth / 2, (Screen::intendedWidth / 2) - 325}
		,40
		,"Time:"
		,"res/ARCADE_I.TTF"
		,Color::ColorsName::WHITE
		,1.0f
	};

	extern Math::Vector2 resultTimePos;
	extern float resultTimeFontSize;
	
	struct GameplayButtonIntended
	{
		Math::Vector2 pos = {};
		std::string fontName = " ";
		int fontSize = 0;
		std::string text = " ";
		Color::ColorsName color = Color::ColorsName::WHITE;
		float opacity = 1.0f;
		GameScenes::GameScenes pointingGameScene = GameScenes::GameScenes::Gameplay;
		GameplayScenes pointingGameplayScene = GameplayScenes::Playing;
	};

	struct GameplayButton
	{
		Button::Button button;
		GameScenes::GameScenes pointingGameScene;
		GameplayScenes pointingGameplayScene;
	};

	const GameplayButtonIntended resumeButtonIntended =
	{
			{intendedPlayableArea.position.x,intendedPlayableArea.position.y-25}		//Pos
			,"res/ARCADE_I.TTF"					//FontName
			,22									//FontSize
			,"RESUME"								//Text
			,Color::ColorsName::WHITE			//Color
			,1.0f								//Opacity
			,GameScenes::GameScenes::Gameplay
			,GameplayScenes::Playing
	};

	const GameplayButtonIntended menuButtonIntended =
	{
			{intendedPlayableArea.position.x,intendedPlayableArea.position.y-75}		//Pos
			,"res/ARCADE_I.TTF"					//FontName
			,22									//FontSize
			,"MENU"								//Text
			,Color::ColorsName::WHITE			//Color
			,1.0f								//Opacity
			,GameScenes::GameScenes::MainMenu
			,GameplayScenes::Playing
	};

	const GameplayButtonIntended resultBackMenuIntended =
	{
			{400,75}		//Pos
			,"res/ARCADE_I.TTF"					//FontName
			,22									//FontSize
			,"MENU"								//Text
			,Color::ColorsName::WHITE			//Color
			,1.0f								//Opacity
			,GameScenes::GameScenes::Gameplay
			,GameplayScenes::None
	};

	void gameplay(Paddle::Paddle& paddle, Ball::Ball& ball, Block::Block blocks[], Forms::Rectangle playableArea, Text::Text& score, float& timerInSec, float deltaTime, Player::Player& player, GameplayScenes& currentGameplayScene, GameScenes::GameScenes& currentGameScene, Text::Text pauseTitle, Text::Text heart, GameplayButton resumeButton, GameplayButton menuButton, Text::Text& result, Text::Text& resultScore, Text::Text& resultTime, GameplayButton& backMenu);
	void playingUpdate(Block::Block blocks[], Player::Input inputs[], int remainingLives, GameplayScenes& currentGameplayScene, bool& hasLost);
	void drawPlayableArea(Forms::Rectangle playableArea);
	void updateScore(Text::Text& scoreText, Player::Player& player, float timerInSec);
	void updateScoreText(Text::Text& text, int& num);
	void updateScoreNum(int& scoreNum, float& minusScoreCooldown, float timerInSec);
	void drawScore(Text::Text score);
	void pauseUpdate(GameplayButton& resumeButton, GameplayButton& menuButton, GameplayScenes& currentGameplayScene, GameScenes::GameScenes& currentGameScene, Player::Input inputs[]);
	void gameplayButtonLogic(GameplayButton& gameplayButton, GameplayButtonIntended intended, Player::Input inputs[], GameplayScenes& currentGameplayScene, GameScenes::GameScenes& currentGameScene);
	void pauseDraw(Text::Text pauseTitle, GameplayButton resumeButton, GameplayButton menuButton);
	void endedUpdate(GameplayButton& backMenu, GameScenes::GameScenes& currentGameScene, GameplayScenes& currentGameplayScene, Player::Input inputs[]);
	void endedDraw(Text::Text result, Text::Text resultScore, Text::Text resultTime, GameplayButton backMenu, int timeInSeconds, Player::Player player);
	void initGameplayButton(GameplayButton& mainMenuButton, GameplayButtonIntended intendedButton);
	void drawLives(Text::Text heart, int currentLives);
}

