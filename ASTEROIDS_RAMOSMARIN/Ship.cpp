#include "Ship.h"

Ship CreateShip(Ship& spaceShip)
{
	spaceShip.size.x = 10;
	spaceShip.size.y = 10;
	spaceShip.position.x = GetScreenWidth() / 2.0f;
	spaceShip.position.y = GetScreenHeight() / 2.0f;
	spaceShip.radius = 10;
	spaceShip.speed.x = 50;
	spaceShip.color = WHITE;
	return spaceShip;
}

void DrawShip(Ship& spaceShip)
{
	DrawCircle((int)spaceShip.position.x, (int)spaceShip.position.y, spaceShip.radius, spaceShip.color);
}