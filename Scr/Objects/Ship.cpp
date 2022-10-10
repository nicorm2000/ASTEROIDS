#include "Ship.h"

Ship CreateShip(Ship& spaceShip)
{
	spaceShip.size.x = 20;
	spaceShip.size.y = 20;
	spaceShip.position.x = GetScreenWidth() / 2.0f;
	spaceShip.position.y = GetScreenHeight() / 2.0f;
	spaceShip.radius = 13;
	spaceShip.speed.x = 5;
	spaceShip.speed.y = 5;
	spaceShip.rotation = 0;
	spaceShip.color = RED;
	spaceShip.lifes = 3;
	spaceShip.isActive = true;
	spaceShip.shipTexture = LoadTexture("../resources/candyship.png");
	spaceShip.shipOriginalTexture = LoadTexture("../resources/candyship.png");
	spaceShip.shipTextureMovement = LoadTexture("../resources/candyshipmovement.png");
	return spaceShip;
}

void DrawShip(Ship& spaceShip, float angle)
{
	DrawTexturePro(spaceShip.shipTexture, spaceShip.source, spaceShip.dest, spaceShip.origin, angle, WHITE);
	DrawCircleLines(spaceShip.position.x, spaceShip.position.y, spaceShip.radius, spaceShip.color);
}