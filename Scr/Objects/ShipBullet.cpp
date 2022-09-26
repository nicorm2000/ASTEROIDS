#include "raylib.h"
#include "Objects/ShipBullet.h"

ShipBullets CreateShipBullet(ShipBullets& shipBullets)
{
	shipBullets.position.x = 0;
	shipBullets.position.y = 0;
	shipBullets.direction.x = 0;
	shipBullets.direction.y = 0;
	shipBullets.radius = 7.0f;
	shipBullets.speed = 300.0f;
	shipBullets.isMoving = false;
	shipBullets.bulletTexture = LoadTexture("../resources/shipBullet.png");
	return shipBullets;
}

void DrawShipBullet(ShipBullets shipBullet, Ship spaceShip)
{
	//DrawCircle(shipBullet.position.x + 10, shipBullet.position.y + 7, shipBullet.radius, RED);
	DrawTexture(shipBullet.bulletTexture, shipBullet.position.x + 3, shipBullet.position.y, WHITE);
}