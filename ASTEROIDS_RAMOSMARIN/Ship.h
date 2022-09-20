#pragma once
#include "raylib.h"

struct Ship
{
	Vector2 size {};
	Vector2 speed {};
	Vector2 position {};
	float rotation;
	float radius;
	int lifes;
	Color color;
};

Ship CreateShip(Ship& spaceShip);

void DrawShip(Ship& spaceShip);