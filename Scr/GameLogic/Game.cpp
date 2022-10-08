#include "Game.h"
#include "raylib.h"
#include <ctime>
#include "raymath.h"
#include <iostream>

#include "Objects/Ship.h"
#include "Objects/Asteroid.h"
#include "Objects/ShipBullet.h"
#include "Objects/EnemyShip.h"

const int maxShipBullets = 100;
ShipBullets shipBullet;
ShipBullets maximumShipBullets[maxShipBullets];

const int asteroidAmount = 35;
const int asteroidBigAmount = 5;
const int asteroidMediumAmount = 10;
const int asteroidSmallAmount = 20;
Asteroid asteroidArray[asteroidAmount];
Asteroid asteroidBigArray[asteroidBigAmount];
Asteroid asteroidMediumArray[asteroidMediumAmount];
Asteroid asteroidSmallArray[asteroidSmallAmount];
int asteroidBigCount = 0;
int asteroidMediumCount = 0;
int asteroidSmallCount = 0;

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

bool CollisionCircleCircleBullet(ShipBullets& shipBullet, Asteroid& asteroid1)
{
	float distX = shipBullet.position.x - asteroid1.position.x;
	float distY = shipBullet.position.y - asteroid1.position.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= shipBullet.radius + asteroid1.radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionCircleRectangleEnemyShip(Ship& spaceShip, EnemyShip& enemyShip)
{
	float testX = spaceShip.position.x;
	float testY = spaceShip.position.y;

	if (spaceShip.position.x < enemyShip.position.x)
	{
		testX = enemyShip.position.x;
	}
	else if (spaceShip.position.x > enemyShip.position.x + enemyShip.size.x)
	{
		testX = enemyShip.position.x + enemyShip.size.x;
	}

	if (spaceShip.position.y < enemyShip.position.y)
	{
		testY = enemyShip.position.y;
	}
	else if (spaceShip.position.y > enemyShip.position.y + enemyShip.size.y)
	{
		testY = enemyShip.position.y + enemyShip.size.y;
	}

	float distX = spaceShip.position.x - testX;
	float distY = spaceShip.position.y - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= spaceShip.radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameCollisions(Ship& spaceShip, Asteroid& asteroid1, EnemyShip enemyShip)
{
	/*for (int i = 0; i < asteroidAmount; i++)
	{
		for (int j = 0; j < maxShipBullets; j++)
		{
			if (maximumShipBullets[j].isActive)
			{
				if (CollisionCircleCircleBullet(maximumShipBullets[j], asteroidArray[i]))
				{
					asteroidArray[i].isActive = false;
				}
			}
		}
	}*/

	for (int i = 0; i < asteroidAmount; i++)
	{
		for (int j = 0; j < maxShipBullets; j++)
		{
			float distX = maximumShipBullets[j].position.x - asteroidArray[i].position.x;
			float distY = maximumShipBullets[j].position.y - asteroidArray[i].position.y;
			float distance = sqrt((distX * distX) + (distY * distY));

			if (distance <= maximumShipBullets[j].radius + asteroidArray[i].radius)
			{
				asteroidArray[i].isActive = true;
				maximumShipBullets[j].isActive = false;


				if (asteroidArray[i].isActive && asteroidArray[i].asteroidSize == Size::BIG)
				{
					asteroidMediumCount += 2;
					asteroidArray[asteroidBigAmount + asteroidMediumCount].position = asteroidArray[i].position;
					asteroidArray[asteroidBigAmount + asteroidMediumCount - 1].position = asteroidArray[i].position;
					asteroidArray[asteroidBigAmount + asteroidMediumCount].isActive = false;
					asteroidArray[asteroidBigAmount + asteroidMediumCount - 1].isActive = false;

					/*do
					{
						asteroidArray[asteroidBigAmount + asteroidMediumCount].speed.x = static_cast<float>(GetRandomValue(-200, 200));
					} while (asteroidArray[asteroidBigAmount + asteroidMediumCount].speed.x > -100 && asteroidArray[asteroidBigAmount + asteroidMediumCount].speed.x < 100);

					do
					{
						asteroidArray[asteroidBigAmount + asteroidMediumCount].speed.y = static_cast<float>(GetRandomValue(-200, 200));
					} while (asteroidArray[asteroidBigAmount + asteroidMediumCount].speed.y > -100 && asteroidArray[asteroidBigAmount + asteroidMediumCount].speed.y < 100);

					do
					{
						asteroidArray[asteroidBigAmount + asteroidMediumCount - 1].speed.x = static_cast<float>(GetRandomValue(-200, 200));
					} while (asteroidArray[asteroidBigAmount + asteroidMediumCount].speed.x > -100 && asteroidArray[asteroidBigAmount + asteroidMediumCount].speed.x < 100);

					do
					{
						asteroidArray[asteroidBigAmount + asteroidMediumCount - 1].speed.y = static_cast<float>(GetRandomValue(-200, 200));
					} while (asteroidArray[asteroidBigAmount + asteroidMediumCount - 1].speed.y > -100 && asteroidArray[asteroidBigAmount + asteroidMediumCount - 1].speed.y < 100);*/

				}
				else if (asteroidArray[i].isActive && asteroidArray[i].asteroidSize == Size::MEDIUM)
				{
					asteroidSmallCount += 2;
					asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount].position = asteroidArray[i].position;
					asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount - 1].position = asteroidArray[i].position;
					asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount].isActive = false;
					asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount - 1].isActive = false;
				
					/*do
					{
						asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount].speed.x = static_cast<float>(GetRandomValue(-200, 200));
					} while (asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount].speed.x > -100 && asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount].speed.x < 100);

					do
					{
						asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount].speed.y = static_cast<float>(GetRandomValue(-200, 200));
					} while (asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount].speed.y > -100 && asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount].speed.y < 100);

					do
					{
						asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount - 1].speed.x = static_cast<float>(GetRandomValue(-200, 200));
					} while (asteroidArray[asteroidBigAmount + asteroidMediumCount].speed.x > -100 && asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount].speed.x < 100);

					do
					{
						asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount - 1].speed.y = static_cast<float>(GetRandomValue(-200, 200));
					} while (asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount - 1].speed.y > -100 && asteroidArray[asteroidBigAmount + asteroidMediumCount + asteroidSmallAmount - 1].speed.y < 100);*/

				}
				j = maxShipBullets;
			}
		}
	}
	
	if (CollisionCircleCircle(spaceShip, asteroid1))
	{
		//asteroid1.isActive = false;
		/*spaceShip.lifes--;
		if (spaceShip.lifes > 0)
		{
			spaceShip.position.x = GetScreenWidth() / 2;
			spaceShip.position.y = GetScreenHeight() / 2;
			spaceShip.speed.x = 0;
			spaceShip.speed.y = 0;
		}
		else if(spaceShip.lifes <= 0)
		{
			spaceShip.isActive = false;
		}*/
	}

	if (CollisionCircleRectangleEnemyShip(spaceShip, enemyShip))
	{
		spaceShip.isActive = false;
		for (int i = 0; i < maxShipBullets; i++)
		{
			maximumShipBullets[i].isActive = false;
		}
	}
}

void CheckInput(Ship& spaceShip, Vector2 normalizedDirection, Vector2 mousePosition)
{
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		spaceShip.speed.x += normalizedDirection.x;
		spaceShip.speed.y += normalizedDirection.y;
	}

	spaceShip.position.x += spaceShip.speed.x * GetFrameTime();
	spaceShip.position.y += spaceShip.speed.y * GetFrameTime();

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		for (int i = 0; i < maxShipBullets; i++)
		{
			if (!maximumShipBullets[i].isMoving)
			{
				maximumShipBullets[i].isMoving = true;

				maximumShipBullets[i].direction.x = mousePosition.x - maximumShipBullets[i].position.x;
				maximumShipBullets[i].direction.y = mousePosition.y - maximumShipBullets[i].position.y;

				maximumShipBullets[i].direction = Vector2Normalize(maximumShipBullets[i].direction);

				break;
			}
		}
	}
}

void windowTp(Ship& spaceShip, Asteroid& asteroid1, EnemyShip& enemyShip)
{
	//ship teleports to other side
	if (spaceShip.position.x > GetScreenWidth() + spaceShip.shipTexture.width)
	{
		spaceShip.position.x = -5;
	}
	if (spaceShip.position.x < 0 - spaceShip.shipTexture.width)
	{
		spaceShip.position.x = static_cast<float>(GetScreenWidth() + 5);
	}

	if (spaceShip.position.y > GetScreenHeight() + spaceShip.shipTexture.height)
	{
		spaceShip.position.y = -5;
	}
	if (spaceShip.position.y < 0 - spaceShip.shipTexture.height)
	{
		spaceShip.position.y = static_cast<float>(GetScreenHeight() + 5);
	}

	//asteroid teleports to other side
	if (asteroid1.position.x > GetScreenWidth() + asteroid1.size.x)
	{
		asteroid1.position.x = -5;
	}
	if (asteroid1.position.x < 0 - asteroid1.size.x)
	{
		asteroid1.position.x = static_cast<float>(GetScreenWidth() + 5);
	}

	if (asteroid1.position.y > GetScreenHeight() + asteroid1.size.y)
	{
		asteroid1.position.y = -5;
	}
	if (asteroid1.position.y < 0 - asteroid1.size.y)
	{
		asteroid1.position.y = static_cast<float>(GetScreenHeight() + 5);
	}

	for (int i = 0; i < maxShipBullets; i++)
	{
		if (maximumShipBullets[i].isMoving)
		{
			if (maximumShipBullets[i].position.x < 0)
			{
				maximumShipBullets[i].isMoving = false;
			}
			if (maximumShipBullets[i].position.x >= GetScreenWidth())
			{
				maximumShipBullets[i].isMoving = false;
			}
			if (maximumShipBullets[i].position.y < 0)
			{
				maximumShipBullets[i].isMoving = false;
			}
			if (maximumShipBullets[i].position.y >= GetScreenHeight())
			{
				maximumShipBullets[i].isMoving = false;
			}
		}
	}

	//enemyShip teleports to other side
	if (enemyShip.position.x > GetScreenWidth())
	{
		enemyShip.position.x = - 199;
	}
	if (enemyShip.position.x < - 199)
	{
		enemyShip.position.x = static_cast<float>(GetScreenWidth());
	}
}

void ShipMovement(Vector2 mousePosition, Ship& spaceShip)
{
	//ship update values
	Vector2 vectorDirection{ mousePosition.x - spaceShip.position.x, mousePosition.y - spaceShip.position.y };

	float arcTan = atan(vectorDirection.y / vectorDirection.x);

	float angle = arcTan * 180 / PI;

	if (vectorDirection.x < 0)
	{
		angle += 180;
	}

	float vectorModule = sqrt(pow(vectorDirection.x, 2) + pow(vectorDirection.y, 2));

	Vector2 normalizedDirection = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };

	spaceShip.normalizeDir = normalizedDirection;
	spaceShip.rotation = angle;
	spaceShip.origin = { (float)spaceShip.size.x / 2, (float)spaceShip.size.y / 2 };
	spaceShip.source = { 0, 0, (float)spaceShip.shipTexture.width, (float)spaceShip.shipTexture.height };
	spaceShip.dest = { spaceShip.position.x, spaceShip.position.y, (float)spaceShip.shipTexture.width,  (float)spaceShip.shipTexture.height };
}

void RunGame()
{
	Initialize();

	HideCursor();

	SetExitKey(KEY_NULL);

	bool playingGame = true;
	bool exitWindow = false;
	bool isPaused = false;
	
	Vector2 mousePosition = GetMousePosition();

	GameScreen gameState = GameScreen::GAMETITLE;

	Texture2D backGround = LoadTexture("../resources/backgroundtiled.png");
	Texture2D exitButton = LoadTexture("../resources/xbutton.png");
	Texture2D menuBackGround = LoadTexture("../resources/menubgbig.png");
	Texture2D gameTitle = LoadTexture("../resources/gametitle.png");
	Texture2D playTitle = LoadTexture("../resources/playbutton.png");
	Texture2D howToPlayTitle = LoadTexture("../resources/howtoplaybutton.png");
	Texture2D creditsTitle = LoadTexture("../resources/creditsbutton.png");
	Texture2D exitTitle = LoadTexture("../resources/exitbutton.png");
	Texture2D button1 = LoadTexture("../resources/button.png");
	Font titleFont = LoadFont("../resources/Fonts/MilkyCoffee.otf");

	Ship spaceShip;
	EnemyShip enemyShip;

	for (int i = 0; i < asteroidBigAmount; i++)
	{
		asteroidArray[i].asteroidSize = Size::BIG;
		CreateAsteroid(asteroidArray[i], asteroidArray[i].asteroidSize);
	}
	for (int i = asteroidBigAmount; i < asteroidBigAmount + asteroidMediumAmount + 1; i++)
	{
		asteroidArray[i].asteroidSize = Size::MEDIUM;
		CreateAsteroid(asteroidArray[i], asteroidArray[i].asteroidSize);
	}
	for (int i = asteroidBigAmount + asteroidMediumAmount + 1; i < asteroidAmount; i++)
	{
		asteroidArray[i].asteroidSize = Size::SMALL;
		CreateAsteroid(asteroidArray[i], asteroidArray[i].asteroidSize);
	}

	for (int i = 0; i < maxShipBullets - 1; i++)
	{
		CreateShipBullet(maximumShipBullets[i]);
	}

	CreateShip(spaceShip);
	CreateEnemyShip(enemyShip);

	while (playingGame && !WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		switch (gameState)
		{
		case GameScreen::GAMETITLE:

			mousePosition = GetMousePosition();

			if (CheckCollisionPointRec(mousePosition, { 410, 255, 237, 130 }))
			{
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					gameState = GameScreen::GAME;
				}
			}
			
			if (CheckCollisionPointRec(mousePosition, { 355, 418, 377, 80 }))
			{
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					gameState = GameScreen::HOWTOPLAY;
				}
			}
			
			if (CheckCollisionPointRec(mousePosition, { 402, 530, 253, 82 }))
			{
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					gameState = GameScreen::CREDITS;
				}
			}

			if (CheckCollisionPointRec(mousePosition, { 435, 655, 165, 98 }))
			{
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					gameState = GameScreen::EXIT;
				}
			}

			DrawTexture(menuBackGround, 0, 0, WHITE);
			DrawTextureEx(gameTitle, { 75, -130 }, 0, 0.7f, WHITE);
			DrawTextureEx(playTitle, { 400, 250 }, 0, 0.2f, WHITE);
			DrawTextureEx(howToPlayTitle, { 350, 350 }, 0, 0.3f, WHITE);
			DrawTextureEx(creditsTitle, { 400, 500 }, 0, 0.2f, WHITE);
			DrawTextureEx(exitTitle, { 420, 650 }, 0, 0.15f, WHITE);
			
			DrawCircle(static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y), 5, GREEN);

			break;

		case GameScreen::GAME:

			mousePosition = GetMousePosition();

			ShipMovement(mousePosition, spaceShip);

			enemyShip.source = { enemyShip.position.x, enemyShip.position.y, (float)enemyShip.enemyTexture.width, (float)enemyShip.enemyTexture.height };
			enemyShip.dest = { enemyShip.position.x, enemyShip.position.y, (float)enemyShip.enemyTexture.width,  (float)enemyShip.enemyTexture.height };
			enemyShip.origin = { (float)enemyShip.position.x / 2.0f, (float)enemyShip.position.y / 2.0f };
			enemyShip.position.x += enemyShip.speed.x * GetFrameTime();

			for (int i = 0; i < asteroidAmount; i++)
			{
				GameCollisions(spaceShip, asteroidArray[i], enemyShip);
				windowTp(spaceShip, asteroidArray[i], enemyShip);
				if (asteroidArray[i].speed.x != 0 && asteroidArray[i].speed.y != 0)
				{
					asteroidArray[i].position.x += asteroidArray[i].speed.x * GetFrameTime();
					asteroidArray[i].position.y += asteroidArray[i].speed.y * GetFrameTime();
				}
				else
				{
					asteroidArray[i].speed.x = static_cast<float>(GetRandomValue(-100, 100));
					asteroidArray[i].speed.y = static_cast<float>(GetRandomValue(-100, 100));

					asteroidArray[i].position.x += asteroidArray[i].speed.x * GetFrameTime();
					asteroidArray[i].position.y += asteroidArray[i].speed.y * GetFrameTime();
				}
			}

			for (int i = 0; i < maxShipBullets; i++)
			{
				if (maximumShipBullets[i].isMoving == false)
				{
					maximumShipBullets[i].position.x = spaceShip.position.x - spaceShip.size.x / 2;
					maximumShipBullets[i].position.y = spaceShip.position.y - spaceShip.size.y / 2;
				}

				if (maximumShipBullets[i].isMoving)
				{
					maximumShipBullets[i].position.x += maximumShipBullets[i].direction.x * maximumShipBullets[i].speed * GetFrameTime();
					maximumShipBullets[i].position.y += maximumShipBullets[i].direction.y * maximumShipBullets[i].speed * GetFrameTime();
				}
			}

			CheckInput(spaceShip, spaceShip.normalizeDir, mousePosition);

			DrawTexture(menuBackGround, 0, 0, WHITE);
			
			for (int i = 0; i < maxShipBullets; i++)
			{
				if (maximumShipBullets[i].isActive)
				{
					DrawShipBullet(maximumShipBullets[i], spaceShip);
				}
			}
			if (spaceShip.isActive)
			{
				DrawShip(spaceShip, spaceShip.rotation);
			}

			if (enemyShip.isActive)
			{
				DrawEnemyShip(enemyShip);
			}

			for (int i = 0; i < asteroidAmount; i++)
			{
				if (asteroidArray[i].isActive == false && asteroidArray[i].asteroidSize == Size::BIG)
				{
					DrawAsteroid(asteroidArray[i], Size::BIG);
				}
				else if (asteroidArray[i].isActive == false && asteroidArray[i].asteroidSize == Size::MEDIUM)
				{
					DrawAsteroid(asteroidArray[i], Size::MEDIUM);
				}
				else if (asteroidArray[i].isActive == false && asteroidArray[i].asteroidSize == Size::SMALL)
				{
					DrawAsteroid(asteroidArray[i], Size::SMALL);
				}
			}

			DrawCircle(static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y), 5, GREEN);

			break;

		case GameScreen::HOWTOPLAY:

			mousePosition = GetMousePosition();

			if (CheckCollisionPointRec(mousePosition, { 20, 23, 70, 65 }))
			{
				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{
					gameState = GameScreen::GAMETITLE;
				}
			}

			DrawTexture(menuBackGround, 0, 0, WHITE);
			DrawTextureEx(exitButton, { -10, 20 }, 0, 0.1, WHITE);

			DrawCircle(static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y), 5, GREEN);

			break;

		case GameScreen::CREDITS:

			mousePosition = GetMousePosition();

			if (CheckCollisionPointRec(mousePosition, { 20, 23, 70, 65 }))
			{
				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{
					gameState = GameScreen::GAMETITLE;
				}
			}

			DrawTexture(menuBackGround, 0, 0, WHITE);
			DrawTextureEx(exitButton, { -10, 20 }, 0, 0.1, WHITE);

			DrawCircle(static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y), 5, GREEN);

			break;

		case GameScreen::EXIT:

			playingGame = false;

			break;
		}

		EndDrawing();
	}

	UnloadTexture(backGround);
	UnloadTexture(spaceShip.shipTexture);
	UnloadTexture(button1);
	for (int i = 0; i < asteroidAmount; i++)
	{
		UnloadTexture(asteroidArray[i].asteroidTexture);
	}

	Close();
}