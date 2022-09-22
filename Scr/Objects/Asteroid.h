#pragma once
#include "raylib.h"

struct Asteroid
{
	Vector2 size{};
	Vector2 speed{};
	Vector2 position{};
	Vector2 origin{};
	float rotation;
	float radius;
	int variants;
	Color color;
	Rectangle source;
	Rectangle dest;
	bool isActive;
};

Asteroid CreateAsteroid(Asteroid& asteroid);

void DrawAsteroid(Asteroid& asteroid, Texture2D asteroidBigTexture);
