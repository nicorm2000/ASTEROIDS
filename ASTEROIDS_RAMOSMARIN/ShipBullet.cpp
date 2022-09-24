#include "raylib.h"
#include "Objects/ShipBullet.h"

ShipBullets CreateShipBullet(ShipBullets& shipBullets)
{
	shipBullets.position.x = 0;
	shipBullets.position.y = 0;
	shipBullets.direction.x = 0;
	shipBullets.direction.y = 0;
	shipBullets.radius = 14.0f;
	shipBullets.speed = 300.0f;
	shipBullets.isMoving = false;
	shipBullets.bulletTexture = LoadTexture("../resources/shipBullet.png");
	return shipBullets;
}

void DrawShipBullet(ShipBullets shipBullet)
{
	DrawCircle(shipBullet.position.x, shipBullet.position.y, shipBullet.radius, RED);
	DrawTexture(shipBullet.bulletTexture, shipBullet.position.x - 13, shipBullet.position.y - 13, WHITE);
}