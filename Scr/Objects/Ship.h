#pragma once
#include "raylib.h"

struct Ship
{
	Vector2 size {};
	Vector2 speed {};
	Vector2 position {};
	Vector2 origin{};
	float rotation;
	float radius;
	int lifes;
	Rectangle source;
	Rectangle dest;
	Color color;
	bool isActive;
};

Ship CreateShip(Ship& spaceShip);

void DrawShip(Ship& spaceShip, float angle, Texture2D shipTexture);