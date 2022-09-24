#include "raylib.h"
#include "Objects/ShipBullet.h"

ShipBullets CreateShipBullets(ShipBullets& shipBullets)
{
	shipBullets.position.x = 0;
	shipBullets.position.y = 0;
	shipBullets.direction.x = 0;
	shipBullets.direction.y = 0;
	shipBullets.radius = 10.0f;
	shipBullets.speed = 300.0f;
	shipBullets.isMoving = false;

	return shipBullets;

}