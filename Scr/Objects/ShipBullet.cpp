#include "Objects/ShipBullet.h"

#include "raylib.h"

ShipBullets CreateShipBullet(ShipBullets& shipBullets)
{
	shipBullets.position.x = 5000;
	shipBullets.position.y = 5000;
	shipBullets.direction.x = 0;
	shipBullets.direction.y = 0;
	shipBullets.radius = 7.0f;
	shipBullets.speed = 300.0f;
	shipBullets.isMoving = false;
	shipBullets.isActive = false;
	shipBullets.bulletTexture = LoadTexture("res/shipBullet.png");
	return shipBullets;
}

void DrawShipBullet(ShipBullets shipBullet)
{
	//DrawCircle(shipBullet.position.x + 10, shipBullet.position.y + 7, shipBullet.radius, RED);
	DrawTexture(shipBullet.bulletTexture, static_cast<int>(shipBullet.position.x) + 3, static_cast<int>(shipBullet.position.y), WHITE);
}