#include "Game.h"
#include "raylib.h"
#include <ctime>
#include "Ship.h"

static void Initialize()
{
	InitWindow(1024, 768, "ASTEROIDS");
}

static void Close()
{
	CloseWindow();
}

//bool CollisionCircleCircle()
//{
//
//}

void GameCollisions()
{

}

void RunGame()
{
	Initialize();

	SetTargetFPS(60);

	bool playing_game = true;
	bool exitWindow = false;
	bool isPaused = false;

	Vector2 mousePosition = GetMousePosition();

	GameScreen gameState = GameScreen::GAMETITLE;

	Ship spaceShip;
	CreateShip(spaceShip);

	while (!WindowShouldClose() || !playing_game)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		switch (gameState)
		{
		case GameScreen::GAMETITLE:

			mousePosition = GetMousePosition();

			DrawFPS(10, 10);
			DrawShip(spaceShip);

			break;

		case GameScreen::GAME:

			mousePosition = GetMousePosition();

			break;

		case GameScreen::HOWTOPLAY:

			mousePosition = GetMousePosition();

			break;

		case GameScreen::CREDITS:

			mousePosition = GetMousePosition();

			break;

		case GameScreen::EXIT:

			WindowShouldClose();

			break;
		}

		EndDrawing();
	}

	Close();
}