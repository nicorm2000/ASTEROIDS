#include "Asteroid.h"
#include "raylib.h"

Asteroid CreateAsteroid(Asteroid& asteroid)
{
	asteroid.size.x = 20;
	asteroid.size.y = 20;
	asteroid.position.x = 800;
	asteroid.position.y = 384;
	asteroid.radius = 40;
	asteroid.speed.x = GetRandomValue(100, 200);
	asteroid.speed.y = GetRandomValue(100, 200);
	asteroid.color = WHITE;
	return asteroid;
}

void DrawAsteroid(Asteroid& asteroid)
{
	DrawCircle((int)asteroid.position.x, (int)asteroid.position.y, asteroid.radius, asteroid.color);
}