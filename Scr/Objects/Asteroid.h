#pragma once
#include "raylib.h"

struct Asteroid
{
	Vector2 size{};
	Vector2 speed{};
	Vector2 position{};
	float rotation;
	float radius;
	int variants;
	Color color;
};

Asteroid CreateAsteroid(Asteroid& asteroid);

void DrawAsteroid(Asteroid& asteroid);
