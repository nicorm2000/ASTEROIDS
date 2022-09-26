#include "Asteroid.h"
#include "raylib.h"

Asteroid CreateAsteroid(Asteroid& asteroid)
{
	asteroid.size.x = 20;
	asteroid.size.y = 20;
	asteroid.position.x = GetRandomValue(0, 1024);
	asteroid.position.y = GetRandomValue(0, 768);
	asteroid.radius = 50;
	asteroid.speed.x = GetRandomValue(-100, 100);
	asteroid.speed.y = GetRandomValue(-100, 100);
	asteroid.color = WHITE;
	asteroid.isActive = true;
	return asteroid;
}

void DrawAsteroid(Asteroid& asteroid, Texture2D asteroidBigTexture)
{
	//hitbox
	DrawCircleLines(asteroid.position.x, asteroid.position.y, asteroid.radius, asteroid.color);
	DrawTextureTiled(asteroidBigTexture, asteroid.source, asteroid.dest, asteroid.origin, 0, 1, WHITE);
}