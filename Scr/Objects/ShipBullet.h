#pragma once
#include "raylib.h"
#include "Objects/Ship.h"

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