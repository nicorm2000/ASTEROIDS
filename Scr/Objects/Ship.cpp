#include "Ship.h"

Ship CreateShip(Ship& spaceShip)
{
	spaceShip.size.x = 20;
	spaceShip.size.y = 20;
	spaceShip.position.x = GetScreenWidth() / 2.0f;
	spaceShip.position.y = GetScreenHeight() / 2.0f;
	spaceShip.radius = 13;
	spaceShip.isAlive = true;
	spaceShip.score = 0;
	spaceShip.speed.x = 5;
	spaceShip.speed.y = 5;
	spaceShip.rotation = 0;
	spaceShip.color = RED;
	spaceShip.lives = 3;
	spaceShip.isActive = true;
	spaceShip.shipTexture = LoadTexture("res/candyship.png");
	spaceShip.shipOriginalTexture = LoadTexture("res/candyship.png");
	spaceShip.shipTextureMovement = LoadTexture("res/candyshipmovement.png");
	return spaceShip;
}

void DrawShip(Ship& spaceShip, float angle)
{
	//DrawCircleLines(static_cast<int>(spaceShip.position.x), static_cast<int>(spaceShip.position.y), spaceShip.radius, spaceShip.color);
	DrawTexturePro(spaceShip.shipTexture, spaceShip.source, spaceShip.dest, spaceShip.origin, angle, WHITE);
}