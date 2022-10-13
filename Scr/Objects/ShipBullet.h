#pragma once

#include "Objects/Ship.h"

#include "raylib.h"

struct ShipBullets
{
	Vector2 position{};
	Vector2 direction{};
	float radius;
	float speed;
	bool isMoving;
	bool isActive;
	Texture2D bulletTexture;
};

ShipBullets CreateShipBullet(ShipBullets& shipBullets);

void DrawShipBullet(ShipBullets shipBullet);