#include "Game.h"

#include <iostream>
#include <ctime>

#include "raylib.h"
#include "raymath.h"

#include "Objects/Ship.h"
#include "Objects/Asteroid.h"
#include "Objects/ShipBullet.h"
#include "Objects/EnemyShip.h"

const int maxShipBullets = 20;
ShipBullets shipBullets;
ShipBullets maximumShipBullets[maxShipBullets];
int currentBullet = 0;

const int asteroidBigAmount = 8;
const int asteroidMediumAmount = asteroidBigAmount * 2;
const int asteroidSmallAmount = asteroidMediumAmount * 2;

Asteroid asteroidBigArray[asteroidBigAmount];
Asteroid asteroidMediumArray[asteroidMediumAmount];
Asteroid asteroidSmallArray[asteroidSmallAmount];

int asteroidBigCount = 0;
int asteroidMediumCount = 0;
int asteroidSmallCount = 0;

static void Initialize();

static void Close();

bool CollisionCircleCircle(Vector2 positionA, float radiusA, Vector2 positionB, float radiusB);

bool CollisionCircleRectangleEnemyShip(Ship& spaceShip, EnemyShip& enemyShip);

void AsteroidDestruction(ShipBullets& shipBullet, Asteroid& asteroid1, Ship& spaceShip, Sound crashAsteroid);

void RespawnAsteroids(Texture2D asteroidBig);

void GameCollisions(Ship& spaceShip, Asteroid& asteroid1, EnemyShip enemyShip, Sound crashAsteroid, Sound deathSoundEffect);

void CheckInput(Ship& spaceShip, Vector2 normalizedDirection, Vector2 mousePosition, Sound pewSound);

void windowTp(Ship& spaceShip, Asteroid& asteroid1, EnemyShip& enemyShip);

void ShipMovement(Vector2 mousePosition, Ship& spaceShip);

void RunGame()
{
	Initialize();

	HideCursor();

	SetExitKey(KEY_NULL);

	bool playingGame = true;
	bool exitWindow = false;
	bool isPaused = false;
	bool gameFinished = false;
	bool restartGame = true;

	Vector2 mousePosition = GetMousePosition();

	GameScreen gameState = GameScreen::GAMETITLE;

	Texture2D backGround = LoadTexture("res/backgroundtiled.png");
	Texture2D exitButton = LoadTexture("res/xbutton.png");
	Texture2D menuBackGround = LoadTexture("res/menubgbig.png");
	Texture2D howToPlayMenu = LoadTexture("res/howtoplay.png");
	Texture2D gameTitle = LoadTexture("res/gametitle.png");
	Texture2D playTitle = LoadTexture("res/playbutton.png");
	Texture2D howToPlayTitle = LoadTexture("res/howtoplaybutton.png");
	Texture2D creditsTitle = LoadTexture("res/creditsbutton.png");
	Texture2D exitTitle = LoadTexture("res/exitbutton.png");
	Texture2D button1 = LoadTexture("res/button.png");
	Texture2D asteroidBig = LoadTexture("res/enemy1.png");
	Texture2D asteroidMedium = LoadTexture("res/enemy2.png");
	Texture2D asteroidSmall = LoadTexture("res/enemy3.png");
	Texture2D cursorLollipop = LoadTexture("res/cursor.png");
	Texture2D creditsBg = LoadTexture("res/Credits.png");

	Font titleFont = LoadFont("res/MilkyCoffee.otf");

	Sound pewSound = LoadSound("res/pew.wav");
	Sound deathSoundEffect = LoadSound("res/deathsoundeffect.wav");
	Sound crashAsteroid = LoadSound("res/crashasteroids.wav");

	Music bgMusic = LoadMusicStream("res/bgMusic.mp3");

	Ship spaceShip;

	EnemyShip enemyShip;

	for (int i = 0; i < asteroidBigAmount; i++)
	{
		asteroidBigArray[i].asteroidSize = Size::BIG;
		CreateAsteroid(asteroidBigArray[i], asteroidBigArray[i].asteroidSize, asteroidBig);
	}
	for (int i = 0; i < asteroidMediumAmount; i++)
	{
		asteroidMediumArray[i].asteroidSize = Size::MEDIUM;
		CreateAsteroid(asteroidMediumArray[i], asteroidMediumArray[i].asteroidSize, asteroidMedium);

	}
	for (int i = 0; i < asteroidSmallAmount; i++)
	{
		asteroidSmallArray[i].asteroidSize = Size::SMALL;
		CreateAsteroid(asteroidSmallArray[i], asteroidSmallArray[i].asteroidSize, asteroidSmall);
	}

	for (int i = 0; i < maxShipBullets - 1; i++)
	{
		CreateShipBullet(maximumShipBullets[i]);
	}

	CreateShip(spaceShip);

	CreateEnemyShip(enemyShip);

	PlayMusicStream(bgMusic);

	SetMusicVolume(bgMusic, 0.35f);

	while (playingGame && !WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		UpdateMusicStream(bgMusic);

		switch (gameState)
		{
		case GameScreen::GAMETITLE:

			mousePosition = GetMousePosition();

			if (CheckCollisionPointRec(mousePosition, { 410, 255, 237, 130 }))
			{
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					restartGame = true;
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

			DrawTexture(cursorLollipop, static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y), WHITE);

			break;

		case GameScreen::GAME:

			mousePosition = GetMousePosition();

			if (!isPaused)
			{
				if (restartGame)
				{
					spaceShip.score = 0;
					spaceShip.lives = 3;
					spaceShip.isActive = true;
					spaceShip.isAlive = true;
					spaceShip.position.x = static_cast<float>(GetScreenWidth() / 2);
					spaceShip.position.y = static_cast<float>(GetScreenHeight() / 2);
					spaceShip.speed.x = 0;
					spaceShip.speed.y = 0;
					asteroidMediumCount = 0;
					asteroidSmallCount = 0;
					restartGame = false;
				}

				ShipMovement(mousePosition, spaceShip);
				CheckInput(spaceShip, spaceShip.normalizeDir, mousePosition, pewSound);

				enemyShip.source = { enemyShip.position.x, enemyShip.position.y, (float)enemyShip.enemyTexture.width, (float)enemyShip.enemyTexture.height };
				enemyShip.dest = { enemyShip.position.x, enemyShip.position.y, (float)enemyShip.enemyTexture.width,  (float)enemyShip.enemyTexture.height };
				enemyShip.origin = { (float)enemyShip.position.x / 2.0f, (float)enemyShip.position.y / 2.0f };
				enemyShip.position.x += enemyShip.speed.x * GetFrameTime();

				for (int i = 0; i < asteroidBigAmount; i++)
				{
					RespawnAsteroids(asteroidBig);
					GameCollisions(spaceShip, asteroidBigArray[i], enemyShip, crashAsteroid, deathSoundEffect);
					windowTp(spaceShip, asteroidBigArray[i], enemyShip);
					if (asteroidBigArray[i].speed.x != 0 && asteroidBigArray[i].speed.y != 0)
					{
						asteroidBigArray[i].position.x += asteroidBigArray[i].speed.x * GetFrameTime();
						asteroidBigArray[i].position.y += asteroidBigArray[i].speed.y * GetFrameTime();
					}
				}
				for (int i = 0; i < asteroidMediumAmount; i++)
				{
					GameCollisions(spaceShip, asteroidMediumArray[i], enemyShip, crashAsteroid, deathSoundEffect);
					windowTp(spaceShip, asteroidMediumArray[i], enemyShip);
					if (asteroidMediumArray[i].speed.x != 0 && asteroidMediumArray[i].speed.y != 0)
					{
						asteroidMediumArray[i].position.x += asteroidMediumArray[i].speed.x * GetFrameTime();
						asteroidMediumArray[i].position.y += asteroidMediumArray[i].speed.y * GetFrameTime();
					}
				}
				for (int i = 0; i < asteroidSmallAmount; i++)
				{
					GameCollisions(spaceShip, asteroidSmallArray[i], enemyShip, crashAsteroid, deathSoundEffect);
					windowTp(spaceShip, asteroidSmallArray[i], enemyShip);
					if (asteroidSmallArray[i].speed.x != 0 && asteroidSmallArray[i].speed.y != 0)
					{
						asteroidSmallArray[i].position.x += asteroidSmallArray[i].speed.x * GetFrameTime();
						asteroidSmallArray[i].position.y += asteroidSmallArray[i].speed.y * GetFrameTime();
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
			}

			if (IsKeyPressed(KEY_ESCAPE) && !gameFinished && !spaceShip.lives == 0)
			{
				isPaused = true;
				exitWindow = true;
			}

			if (exitWindow)
			{
				if (CheckCollisionPointRec(mousePosition, { 350, 425, 150, 100 }))
				{
					if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
					{
						exitWindow = false;
						isPaused = !isPaused;
					}
				}
				if (CheckCollisionPointRec(mousePosition, { 530, 425, 150, 100 }))
				{
					if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
					{
						gameState = GameScreen::GAMETITLE;

						exitWindow = false;
						isPaused = !isPaused;
					}
				}
			}

			if (spaceShip.lives <= 0)
			{
				if (CheckCollisionPointRec(mousePosition, { 350, 425, 150, 100 }))
				{
					if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
					{
						gameState = GameScreen::GAMETITLE;
					}
				}
				if (CheckCollisionPointRec(mousePosition, { 530, 425, 150, 100 }))
				{
					if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
					{
						gameState = GameScreen::EXIT;
					}
				}
			}

			DrawTexture(menuBackGround, 0, 0, WHITE);

			DrawTextEx(titleFont, "Press 'ESC' to pause the game", { static_cast<float>(GetScreenWidth() / 2) - 175, 30 }, 35, 0, RED);

			for (int i = 0; i < maxShipBullets; i++)
			{
				if (maximumShipBullets[i].isActive)
				{
					DrawShipBullet(maximumShipBullets[i]);
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
				if (asteroidBigArray[i].isActive)
				{
					DrawAsteroid(asteroidBigArray[i]);
				}
			}
			for (int i = 0; i < asteroidMediumAmount; i++)
			{
				if (asteroidMediumArray[i].isActive)
				{
					DrawAsteroid(asteroidMediumArray[i]);
				}
			}
			for (int i = 0; i < asteroidSmallAmount; i++)
			{
				if (asteroidSmallArray[i].isActive)
				{
					DrawAsteroid(asteroidSmallArray[i]);
				}
			}

			if (exitWindow)
			{
				DrawRectangleRounded({ static_cast<float>(GetScreenWidth() / 2) - 250, static_cast<float>(GetScreenHeight() / 2) - 200, 500, 400 }, 0.5f, 1, BLACK);
				DrawRectangleRounded({ static_cast<float>(GetScreenWidth() / 2) - 245, static_cast<float>(GetScreenHeight() / 2) - 195, 490, 390 }, 0.5f, 1, ORANGE);

				DrawTextEx(titleFont, "Do you want to", { static_cast<float>(GetScreenWidth() - 680), static_cast<float>(GetScreenHeight() / 2) - 150 }, 51.5f, 0.0f, BLACK);
				DrawTextEx(titleFont, "Do you want to", { static_cast<float>(GetScreenWidth() - 675), static_cast<float>(GetScreenHeight() / 2) - 145 }, 50.0f, 0.0f, RED);
				DrawTextEx(titleFont, "keep playing?", { static_cast<float>(GetScreenWidth() - 650), static_cast<float>(GetScreenHeight() / 2) - 80 }, 51.5f, 0.0f, BLACK);
				DrawTextEx(titleFont, "keep playing?", { static_cast<float>(GetScreenWidth() - 645), static_cast<float>(GetScreenHeight() / 2) - 75 }, 50.0f, 0.0f, RED);

				DrawRectangleRounded({ 350, 425, 150, 100 }, 0.5f, 1, BLACK);
				DrawRectangleRounded({ 355, 430, 140, 90 }, 0.5f, 1, PINK);

				DrawTextEx(titleFont, "YES", { 390, 460 }, 35, 0, BLACK);

				DrawRectangleRounded({ 530, 425, 150, 100 }, 0.5f, 1, BLACK);
				DrawRectangleRounded({ 535, 430, 140, 90 }, 0.5f, 1, PINK);

				DrawTextEx(titleFont, "NO", { 580, 460 }, 35, 0, BLACK);
			}
			
			DrawTextEx(titleFont, TextFormat("Lives: %i", spaceShip.lives), { 15, 15 }, 52.5f, 0.0f, BLACK);
			DrawTextEx(titleFont, TextFormat("Lives: %i", spaceShip.lives), { 20, 20 }, 50.0f, 0.0f, ORANGE);

			DrawTextEx(titleFont, TextFormat("Score: %i", spaceShip.score), { static_cast<float>(GetScreenWidth() - 210), 15 }, 52.5f, 0.0f, BLACK);
			DrawTextEx(titleFont, TextFormat("Score: %i", spaceShip.score), { static_cast<float>(GetScreenWidth() - 205), 20 }, 50.0f, 0.0f, ORANGE);

			if (!spaceShip.isAlive && spaceShip.lives != 0)
			{
				DrawText("Press 'SPACE' to respawn", GetScreenWidth() / 2 - 250, GetScreenHeight() / 2, 40, BLACK);
			}

			if (spaceShip.lives <= 0)
			{
				DrawRectangleRounded({ static_cast<float>(GetScreenWidth() / 2) - 250, static_cast<float>(GetScreenHeight() / 2) - 200, 500, 400 }, 0.5f, 1, BLACK);
				DrawRectangleRounded({ static_cast<float>(GetScreenWidth() / 2) - 245, static_cast<float>(GetScreenHeight() / 2) - 195, 490, 390 }, 0.5f, 1, ORANGE);

				DrawTextEx(titleFont, "You Lost!", { static_cast<float>(GetScreenWidth() - 720), static_cast<float>(GetScreenHeight() / 2) - 150 }, 102.5f, 0.0f, BLACK);
				DrawTextEx(titleFont, "You Lost!", { static_cast<float>(GetScreenWidth() - 715), static_cast<float>(GetScreenHeight() / 2) - 145 }, 100.0f, 0.0f, RED);

				DrawTextEx(titleFont, TextFormat("Score: %i", spaceShip.score), { static_cast<float>(GetScreenWidth() - 600), static_cast<float>(GetScreenHeight() / 2) - 35 }, 52.5f, 0.0f, BLACK);
				DrawTextEx(titleFont, TextFormat("Score: %i", spaceShip.score), { static_cast<float>(GetScreenWidth() - 595), static_cast<float>(GetScreenHeight() / 2) - 30 }, 50.0f, 0.0f, PINK);

				DrawRectangleRounded({ 350, 425, 150, 100 }, 0.5f, 1, BLACK);
				DrawRectangleRounded({ 355, 430, 140, 90 }, 0.5f, 1, PINK);

				DrawTextEx(titleFont, "Main", { 390, 440 }, 35, 0, BLACK);
				DrawTextEx(titleFont, "Menu", { 390, 480 }, 35, 0, BLACK);

				DrawRectangleRounded({ 530, 425, 150, 100 }, 0.5f, 1, BLACK);
				DrawRectangleRounded({ 535, 430, 140, 90 }, 0.5f, 1, PINK);

				DrawTextEx(titleFont, "Exit", { 570, 440 }, 35, 0, BLACK);
				DrawTextEx(titleFont, "Game", { 570, 480 }, 35, 0, BLACK);
			}

			DrawTexture(cursorLollipop, static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y), WHITE);

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

			DrawTexture(howToPlayMenu, 0, 0, WHITE);
			DrawTextureEx(exitButton, { -10, 20 }, 0.0f, 0.1f, WHITE);

			DrawTexture(cursorLollipop, static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y), WHITE);

			break;

		case GameScreen::CREDITS:

			mousePosition = GetMousePosition();

			if (CheckCollisionPointRec(mousePosition, { 90, 600, 175, 60 }))
			{
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					OpenURL("https://freesound.org/people/Migfus20/sounds/560446/");
				}
			}

			if (CheckCollisionPointRec(mousePosition, { 270, 675, 175, 60 }))
			{
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					OpenURL("https://freesound.org/people/0ne_one111yt/sounds/478215/");
				}
			}

			if (CheckCollisionPointRec(mousePosition, { 550, 675, 175, 60 }))
			{
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					OpenURL("https://freesound.org/people/Jofae/sounds/364929/");
				}
			}

			if (CheckCollisionPointRec(mousePosition, { 770, 600, 175, 60 }))
			{
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					OpenURL("https://freesound.org/people/pomeroyjoshua/sounds/513455/");
				}
			}

			if (CheckCollisionPointRec(mousePosition, { 630, 250, 150, 50 }))
			{
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					OpenURL("https://nicorm.itch.io/");
				}
			}

			if (CheckCollisionPointRec(mousePosition, { 630, 400, 175, 60 }))
			{
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					OpenURL("https://nicorm.itch.io/");
				}
			}

			if (CheckCollisionPointRec(mousePosition, { 20, 23, 70, 65 }))
			{
				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{
					gameState = GameScreen::GAMETITLE;
				}
			}
			
			DrawTexture(creditsBg, 0, 0, WHITE);
			DrawTextureEx(exitButton, { -10, 20 }, 0.0f, 0.1f, WHITE);
			DrawRectangle(630, 250, 150, 50, RED);
			DrawText("itch.io", 635, 255, 50, WHITE);
			DrawRectangle(630, 400, 150, 50, RED);
			DrawText("itch.io", 635, 405, 50, WHITE);
			DrawRectangleRounded({ 85, 595, 185, 70 }, 0.5f, 1, BLACK);
			DrawRectangleRounded({ 90, 600, 175, 60 }, 0.5f, 1, ORANGE);
			DrawRectangleRounded({ 265, 670, 185, 70 }, 0.5f, 1, BLACK);
			DrawRectangleRounded({ 270, 675, 175, 60 }, 0.5f, 1, ORANGE);
			DrawRectangleRounded({ 545, 670, 185, 70 }, 0.5f, 1, BLACK);
			DrawRectangleRounded({ 550, 675, 175, 60 }, 0.5f, 1, ORANGE);
			DrawRectangleRounded({ 765, 595, 185, 70 }, 0.5f, 1, BLACK);
			DrawRectangleRounded({ 770, 600, 175, 60 }, 0.5f, 1, ORANGE);
			DrawText("Migfus20", 130, 618, 20, BLACK);
			DrawText("0ne_one111yt", 295, 695, 20, BLACK);
			DrawText("Jofae", 605, 695, 20, BLACK);
			DrawText("pomeroyjoshua", 783, 618, 20, BLACK);
			DrawTexture(cursorLollipop, static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y), WHITE);

			break;

		case GameScreen::EXIT:

			playingGame = false;

			break;
		}

		EndDrawing();
	}

	UnloadTexture(backGround);
	UnloadTexture(exitButton);
	UnloadTexture(menuBackGround);
	UnloadTexture(howToPlayMenu);
	UnloadTexture(gameTitle);
	UnloadTexture(playTitle);
	UnloadTexture(howToPlayTitle);
	UnloadTexture(creditsTitle);
	UnloadTexture(exitTitle);
	UnloadTexture(button1);
	UnloadTexture(asteroidBig);
	UnloadTexture(asteroidMedium);
	UnloadTexture(asteroidSmall);
	UnloadTexture(cursorLollipop);
	UnloadTexture(creditsBg);
	UnloadFont(titleFont);
	UnloadSound(pewSound);
	UnloadSound(deathSoundEffect);
	UnloadSound(crashAsteroid);
	UnloadMusicStream(bgMusic);

	Close();
}

static void Initialize()
{
	InitWindow(1024, 768, "ASTEROIDS");
	InitAudioDevice();
}

static void Close()
{
	CloseAudioDevice();
	CloseWindow();
}

bool CollisionCircleCircle(Vector2 positionA, float radiusA, Vector2 positionB, float radiusB)
{
	float distX = positionA.x - positionB.x;
	float distY = positionA.y - positionB.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= radiusA + radiusB)
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

void AsteroidDestruction(ShipBullets& shipBullet, Asteroid& asteroid1, Ship& spaceShip, Sound crashAsteroid)
{
	float distX = shipBullet.position.x - asteroid1.position.x;
	float distY = shipBullet.position.y - asteroid1.position.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= shipBullet.radius + asteroid1.radius)
	{
		switch (asteroid1.asteroidSize)
		{
		case Size::BIG:
			asteroid1.isActive = false;
			shipBullet.isActive = false;

			if (asteroidMediumCount < asteroidMediumAmount)
			{
				asteroidMediumArray[asteroidMediumCount].speed.x = static_cast<float>(GetRandomValue(-100, 100));
				do
				{
					asteroidMediumArray[asteroidMediumCount].speed.x = static_cast<float>(GetRandomValue(-100, 100));
				} while (asteroidMediumArray[asteroidMediumCount].speed.x == 0);

				asteroidMediumArray[asteroidMediumCount].speed.y = static_cast<float>(GetRandomValue(-100, 100));
				do
				{
					asteroidMediumArray[asteroidMediumCount].speed.y = static_cast<float>(GetRandomValue(-100, 100));
				} while (asteroidMediumArray[asteroidMediumCount].speed.y == 0);

				asteroidMediumArray[asteroidMediumCount].position.x = asteroid1.position.x;
				asteroidMediumArray[asteroidMediumCount].position.y = asteroid1.position.y;
				asteroidMediumArray[asteroidMediumCount].isActive = true;
				asteroidMediumCount++;

				asteroidMediumArray[asteroidMediumCount].speed.x = static_cast<float>(GetRandomValue(-100, 100));
				do
				{
					asteroidMediumArray[asteroidMediumCount].speed.x = static_cast<float>(GetRandomValue(-100, 100));
				} while (asteroidMediumArray[asteroidMediumCount].speed.x == 0);

				asteroidMediumArray[asteroidMediumCount].speed.y = static_cast<float>(GetRandomValue(-100, 100));
				do
				{
					asteroidMediumArray[asteroidMediumCount].speed.y = static_cast<float>(GetRandomValue(-100, 100));
				} while (asteroidMediumArray[asteroidMediumCount].speed.y == 0);

				asteroidMediumArray[asteroidMediumCount].position.x = asteroid1.position.x;
				asteroidMediumArray[asteroidMediumCount].position.y = asteroid1.position.y;
				asteroidMediumArray[asteroidMediumCount].isActive = true;
				asteroidMediumCount++;

				asteroidBigCount++;
			}
			break;
		case Size::MEDIUM:
			asteroid1.isActive = false;
			shipBullet.isActive = false;

			if (asteroidSmallCount < asteroidSmallAmount)
			{
				asteroidSmallArray[asteroidSmallCount].speed.x = static_cast<float>(GetRandomValue(-100, 100));
				do
				{
					asteroidSmallArray[asteroidSmallCount].speed.x = static_cast<float>(GetRandomValue(-100, 100));
				} while (asteroidSmallArray[asteroidSmallCount].speed.x == 0);

				asteroidSmallArray[asteroidSmallCount].speed.y = static_cast<float>(GetRandomValue(-100, 100));
				do
				{
					asteroidSmallArray[asteroidSmallCount].speed.y = static_cast<float>(GetRandomValue(-100, 100));
				} while (asteroidSmallArray[asteroidSmallCount].speed.y == 0);

				asteroidSmallArray[asteroidSmallCount].position.x = asteroid1.position.x;
				asteroidSmallArray[asteroidSmallCount].position.y = asteroid1.position.y;
				asteroidSmallArray[asteroidSmallCount].isActive = true;
				asteroidSmallCount++;

				asteroidSmallArray[asteroidSmallCount].speed.x = static_cast<float>(GetRandomValue(-100, 100));
				do
				{
					asteroidSmallArray[asteroidSmallCount].speed.x = static_cast<float>(GetRandomValue(-100, 100));
				} while (asteroidSmallArray[asteroidSmallCount].speed.x == 0);

				asteroidSmallArray[asteroidSmallCount].speed.y = static_cast<float>(GetRandomValue(-100, 100));
				do
				{
					asteroidSmallArray[asteroidSmallCount].speed.y = static_cast<float>(GetRandomValue(-100, 100));
				} while (asteroidSmallArray[asteroidSmallCount].speed.y == 0);

				asteroidSmallArray[asteroidSmallCount].position.x = asteroid1.position.x;
				asteroidSmallArray[asteroidSmallCount].position.y = asteroid1.position.y;
				asteroidSmallArray[asteroidSmallCount].isActive = true;
				asteroidSmallCount++;
			}
			break;
		case Size::SMALL:
			asteroid1.isActive = false;
			shipBullet.isActive = false;
			break;
		}

		PlaySound(crashAsteroid);

		SetSoundVolume(crashAsteroid, 0.15f);

		spaceShip.score++;
	}
}

void GameCollisions(Ship& spaceShip, Asteroid& asteroid1, EnemyShip enemyShip, Sound crashAsteroid, Sound deathSoundEffect)
{
	if (asteroid1.isActive)
	{
		for (int j = 0; j < maxShipBullets; j++)
		{
			if (maximumShipBullets[j].isActive)
			{
				AsteroidDestruction(maximumShipBullets[j], asteroid1, spaceShip, crashAsteroid);
			}
		}
	}

	if (spaceShip.isActive && asteroid1.isActive)
	{
		if (CollisionCircleCircle(spaceShip.position, spaceShip.radius, asteroid1.position, asteroid1.radius))
		{
			spaceShip.lives--;
			spaceShip.isActive = false;
			spaceShip.isAlive = false;
			asteroid1.isActive = false;

			PlaySound(deathSoundEffect);

			SetSoundVolume(deathSoundEffect, 0.5f);
		}
	}

	if (spaceShip.lives <= 2 && spaceShip.lives > 0 && IsKeyPressed(KEY_SPACE))
	{
		spaceShip.isActive = true;
		spaceShip.isAlive = true;
		spaceShip.position.x = static_cast<float>(GetScreenWidth() / 2);
		spaceShip.position.y = static_cast<float>(GetScreenHeight() / 2);
		spaceShip.speed.x = 0;
		spaceShip.speed.y = 0;
	}
	else if (spaceShip.lives <= 0)
	{
		spaceShip.isActive = false;
	}

	if (CollisionCircleRectangleEnemyShip(spaceShip, enemyShip))
	{
		spaceShip.isActive = false;
		spaceShip.lives = 0;
		for (int i = 0; i < maxShipBullets; i++)
		{
			maximumShipBullets[i].isActive = false;
		}

		PlaySound(deathSoundEffect);

		SetSoundVolume(deathSoundEffect, 0.5f);
	}
}

void CheckInput(Ship& spaceShip, Vector2 normalizedDirection, Vector2 mousePosition, Sound pewSound)
{
	if (spaceShip.isActive)
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			spaceShip.speed.x += normalizedDirection.x * 150 * GetFrameTime();
			spaceShip.speed.y += normalizedDirection.y * 150 * GetFrameTime();

			spaceShip.shipTexture = spaceShip.shipTextureMovement;
		}
		else
		{
			spaceShip.shipTexture = spaceShip.shipOriginalTexture;
		}

		spaceShip.position.x += spaceShip.speed.x * GetFrameTime();
		spaceShip.position.y += spaceShip.speed.y * GetFrameTime();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			maximumShipBullets[currentBullet].isActive = true;

			maximumShipBullets[currentBullet].isMoving = true;

			maximumShipBullets[currentBullet].direction.x = mousePosition.x - maximumShipBullets[currentBullet].position.x;
			maximumShipBullets[currentBullet].direction.y = mousePosition.y - maximumShipBullets[currentBullet].position.y;

			maximumShipBullets[currentBullet].direction = Vector2Normalize(maximumShipBullets[currentBullet].direction);

			currentBullet++;

			if (currentBullet >= maxShipBullets)
			{
				currentBullet = 0;
			}

			PlaySound(pewSound);

			SetSoundVolume(pewSound, 0.35f);
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
		enemyShip.position.x = -199;
	}
	if (enemyShip.position.x < -199)
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

	float vectorModule = static_cast<float>(sqrt(pow(vectorDirection.x, 2) + pow(vectorDirection.y, 2)));

	Vector2 normalizedDirection = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };

	spaceShip.normalizeDir = normalizedDirection;
	spaceShip.rotation = angle;
	spaceShip.origin = { (float)spaceShip.size.x / 2, (float)spaceShip.size.y / 2 };
	spaceShip.source = { 0, 0, (float)spaceShip.shipTexture.width, (float)spaceShip.shipTexture.height };
	spaceShip.dest = { spaceShip.position.x, spaceShip.position.y, (float)spaceShip.shipTexture.width,  (float)spaceShip.shipTexture.height };
}

void RespawnAsteroids(Texture2D asteroidBig)
{
	for (int i = 0; i < asteroidBigAmount; i++)
	{
		if (!asteroidBigArray[i].isActive)
		{
			asteroidBigArray[i].asteroidSize = Size::BIG;
			asteroidBigArray[i] = CreateAsteroid(asteroidBigArray[i], asteroidBigArray[i].asteroidSize, asteroidBig);
		}
	}

	asteroidBigCount += asteroidBigAmount;
	asteroidMediumCount = 0;
	asteroidSmallCount = 0;
}