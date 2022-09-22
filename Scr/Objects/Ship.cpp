#include "Ship.h"

Ship CreateShip(Ship& spaceShip)
{
	spaceShip.size.x = 20;
	spaceShip.size.y = 20;
	spaceShip.position.x = GetScreenWidth() / 2.0f;
	spaceShip.position.y = GetScreenHeight() / 2.0f;
	spaceShip.radius = 10;
	spaceShip.speed.x = 0;
	spaceShip.rotation = 0;
	spaceShip.color = WHITE;
	return spaceShip;
}

void DrawShip(Ship& spaceShip, float angle, Texture2D shipTexture)
{
	//DrawCircle((int)spaceShip.position.x, (int)spaceShip.position.y, spaceShip.radius, spaceShip.color);
	Rectangle ship = { 0, 0, (float)shipTexture.width, (float)shipTexture.height };
	Vector2 shipOrigin = { (int)spaceShip.size.x / 2, (int)spaceShip.size.y / 2 };
	//DrawRectanglePro(ship, shipOrigin, angle, spaceShip.color);
	DrawTexturePro(shipTexture, ship, { spaceShip.position.x, spaceShip.position.y, (float)shipTexture.width,  (float)shipTexture.height }, shipOrigin, angle, WHITE);
}