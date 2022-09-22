#include "Asteroid.h"
#include "raylib.h"

Asteroid CreateAsteroid(Asteroid& asteroid)
{
	asteroid.size.x = 20;
	asteroid.size.y = 20;
	asteroid.position.x = GetRandomValue(0, 1024);
	asteroid.position.y = GetRandomValue(0, 768);
	asteroid.radius = 40;
	asteroid.speed.x = GetRandomValue(-200, 200);
	asteroid.speed.y = GetRandomValue(-200, 200);
	asteroid.color = WHITE;
	asteroid.isActive = true;
	return asteroid;
}

void DrawAsteroid(Asteroid& asteroid)
{
	DrawCircle((int)asteroid.position.x, (int)asteroid.position.y, asteroid.radius, asteroid.color);
}