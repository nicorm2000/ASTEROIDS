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
	for (int i = 0; i < asteroidAmount; i++)
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
		spaceShip.position.x = GetScreenWidth() + 5;
	}

	if (spaceShip.position.y > GetScreenHeight() + spaceShip.shipTexture.height)
	{
		spaceShip.position.y = -5;
	}
	if (spaceShip.position.y < 0 - spaceShip.shipTexture.height)
	{
		spaceShip.position.y = GetScreenHeight() + 5;
	}

	//asteroid teleports to other side
	if (asteroid1.position.x > GetScreenWidth() + asteroid1.size.x)
	{
		asteroid1.position.x = -5;
	}
	if (asteroid1.position.x < 0 - asteroid1.size.x)
	{
		asteroid1.position.x = GetScreenWidth() + 5;
	}

	if (asteroid1.position.y > GetScreenHeight() + asteroid1.size.y)
	{
		asteroid1.position.y = -5;
	}
	if (asteroid1.position.y < 0 - asteroid1.size.y)
	{
		asteroid1.position.y = GetScreenHeight() + 5;
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
		enemyShip.position.x = GetScreenWidth();
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

//void DrawBackgroundGame(Texture2D backGround)
//{
//	DrawTexture(backGround, 0, 0, WHITE);
//	DrawTexture(backGround, 0, 128, WHITE);
//	DrawTexture(backGround, 0, 256, WHITE);
//	DrawTexture(backGround, 0, 384, WHITE);
//	DrawTexture(backGround, 0, 512, WHITE);
//	DrawTexture(backGround, 0, 640, WHITE);
//	DrawTexture(backGround, 128, 0, WHITE);
//	DrawTexture(backGround, 128, 128, WHITE);
//	DrawTexture(backGround, 128, 256, WHITE);
//	DrawTexture(backGround, 128, 384, WHITE);
//	DrawTexture(backGround, 128, 512, WHITE);
//	DrawTexture(backGround, 128, 640, WHITE);
//	DrawTexture(backGround, 256, 0, WHITE);
//	DrawTexture(backGround, 256, 128, WHITE);
//	DrawTexture(backGround, 256, 256, WHITE);
//	DrawTexture(backGround, 256, 384, WHITE);
//	DrawTexture(backGround, 256, 512, WHITE);
//	DrawTexture(backGround, 256, 640, WHITE);
//	DrawTexture(backGround, 384, 0, WHITE);
//	DrawTexture(backGround, 384, 128, WHITE);
//	DrawTexture(backGround, 384, 256, WHITE);
//	DrawTexture(backGround, 384, 384, WHITE);
//	DrawTexture(backGround, 384, 512, WHITE);
//	DrawTexture(backGround, 384, 640, WHITE);
//	DrawTexture(backGround, 512, 0, WHITE);
//	DrawTexture(backGround, 512, 128, WHITE);
//	DrawTexture(backGround, 512, 256, WHITE);
//	DrawTexture(backGround, 512, 384, WHITE);
//	DrawTexture(backGround, 512, 512, WHITE);
//	DrawTexture(backGround, 512, 640, WHITE);
//	DrawTexture(backGround, 640, 0, WHITE);
//	DrawTexture(backGround, 640, 128, WHITE);
//	DrawTexture(backGround, 640, 256, WHITE);
//	DrawTexture(backGround, 640, 384, WHITE);
//	DrawTexture(backGround, 640, 512, WHITE);
//	DrawTexture(backGround, 640, 640, WHITE);
//	DrawTexture(backGround, 768, 0, WHITE);
//	DrawTexture(backGround, 768, 128, WHITE);
//	DrawTexture(backGround, 768, 256, WHITE);
//	DrawTexture(backGround, 768, 384, WHITE);
//	DrawTexture(backGround, 768, 512, WHITE);
//	DrawTexture(backGround, 768, 640, WHITE);
//	DrawTexture(backGround, 896, 0, WHITE);
//	DrawTexture(backGround, 896, 128, WHITE);
//	DrawTexture(backGround, 896, 256, WHITE);
//	DrawTexture(backGround, 896, 384, WHITE);
//	DrawTexture(backGround, 896, 512, WHITE);
//	DrawTexture(backGround, 896, 640, WHITE);
//}

void RunGame()
{
	Initialize();

	HideCursor();

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
	//GenTextureMipmaps(&titleFont.texture);
	//SetTextureFilter(titleFont.texture, TEXTURE_FILTER_ANISOTROPIC_16X);

	Ship spaceShip;
	EnemyShip enemyShip;

	for (int i = 0; i < asteroidAmount; i++)
	{
		if (i < asteroidBigAmount)
		{
			asteroidArray[i].asteroidSize = BIG;
			CreateAsteroid(asteroidArray[i], asteroidArray[i].asteroidSize);
		}
		else if (i >= asteroidBigAmount && i < asteroidMediumAmount)
		{
			asteroidArray[i].asteroidSize = MEDIUM;
			CreateAsteroid(asteroidArray[i], asteroidArray[i].asteroidSize);
		}
		else if (i >= asteroidSmallAmount)
		{
			asteroidArray[i].asteroidSize = SMALL;
			CreateAsteroid(asteroidArray[i], asteroidArray[i].asteroidSize);
		}
	}

	for (int i = 0; i < maxShipBullets + 1; i++)
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
			DrawTextureEx(gameTitle, { 75, -130 }, 0, 0.7, WHITE);
			DrawTextureEx(playTitle, { 400, 250 }, 0, 0.2, WHITE);
			DrawTextureEx(howToPlayTitle, { 350, 350 }, 0, 0.3, WHITE);
			DrawTextureEx(creditsTitle, { 400, 500 }, 0, 0.2, WHITE);
			DrawTextureEx(exitTitle, { 420, 650 }, 0, 0.15, WHITE);
			
			DrawCircle(mousePosition.x, mousePosition.y, 5, GREEN);

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
					asteroidArray[i].speed.x = GetRandomValue(-100, 100);
					asteroidArray[i].speed.y = GetRandomValue(-100, 100);

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

			for (int i = 0; i < asteroidBigAmount; i++)
			{
				if (asteroidArray[i].isActive)
				{
					DrawAsteroid(asteroidArray[i], BIG);
				}
			}
			for (int i = 0; i < asteroidMediumAmount; i++)
			{
				if (asteroidArray[i].isActive)
				{
					DrawAsteroid(asteroidArray[i], MEDIUM);
				}
			}
			for (int i = 0; i < asteroidSmallAmount; i++)
			{
				if (asteroidArray[i].isActive)
				{
					DrawAsteroid(asteroidArray[i], SMALL);
				}
			}

			DrawCircle(mousePosition.x, mousePosition.y, 5, GREEN);

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

			DrawCircle(mousePosition.x, mousePosition.y, 5, GREEN);

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

			DrawCircle(mousePosition.x, mousePosition.y, 5, GREEN);

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