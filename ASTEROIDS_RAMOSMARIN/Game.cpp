#include "Game.h"
#include "raylib.h"
#include <ctime>
#include "Ship.h"
#include "Asteroid.h"
#include <math.h>

static void Initialize()
{
	InitWindow(1024, 768, "ASTEROIDS");
}

static void Close()
{
	CloseWindow();
}

bool CollisionCircleCircle(Ship& spaceShip, Asteroid& asteroid1)
{
	float distX = spaceShip.position.x - asteroid1.position.x;
	float distY = spaceShip.position.y - asteroid1.position.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= spaceShip.radius + asteroid1.radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameCollisions(Ship& spaceShip, Asteroid& asteroid1)
{
	if (CollisionCircleCircle(spaceShip, asteroid1))
	{
		spaceShip.color = RED;
	}
}

void CheckInput(Ship& spaceShip, Vector2 normalizedDirection)
{
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		spaceShip.speed.x += normalizedDirection.x;
		spaceShip.speed.y += normalizedDirection.y;
	}

	spaceShip.position.x += spaceShip.speed.x * GetFrameTime();
	spaceShip.position.y += spaceShip.speed.y * GetFrameTime();
}

void RunGame()
{
	Initialize();

	SetTargetFPS(60);

	HideCursor();

	bool playing_game = true;
	bool exitWindow = false;
	bool isPaused = false;

	Vector2 mousePosition = GetMousePosition();

	GameScreen gameState = GameScreen::GAME;

	Ship spaceShip;
	Asteroid asteroid1;
	CreateShip(spaceShip);
	CreateAsteroid(asteroid1);

	Vector2 vectorDirection{ mousePosition.x - spaceShip.position.x, mousePosition.y - spaceShip.position.y };

	float arcTan = atan(vectorDirection.y / vectorDirection.x);

	float angle = arcTan * 180 / PI;

	float vectorModule = sqrt(pow(vectorDirection.x, 2)  + pow(vectorDirection.y, 2));

	Vector2 normalizedDirection = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };

	while (!WindowShouldClose() || !playing_game)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		switch (gameState)
		{
		case GameScreen::GAMETITLE:

			mousePosition = GetMousePosition();

			break;

		case GameScreen::GAME:

			mousePosition = GetMousePosition();

			vectorDirection = { mousePosition.x - spaceShip.position.x, mousePosition.y - spaceShip.position.y };

			arcTan = atan(vectorDirection.y / vectorDirection.x);

			angle = arcTan * 180 / PI;

			vectorModule = sqrt(pow(vectorDirection.x, 2) + pow(vectorDirection.y, 2));

			normalizedDirection = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };

			spaceShip.rotation = angle;

			GameCollisions(spaceShip, asteroid1);
			CheckInput(spaceShip, normalizedDirection);

			DrawFPS(10, 10);
			DrawLineEx({ spaceShip.position.x , spaceShip.position.y }, { mousePosition.x, mousePosition.y }, 3, WHITE);
			DrawShip(spaceShip, angle);
			DrawAsteroid(asteroid1);
			DrawCircle(mousePosition.x, mousePosition.y, 5, GREEN);
			DrawText(TextFormat("Rotation %02.02f", spaceShip.rotation), 10, 50, 20, WHITE);

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