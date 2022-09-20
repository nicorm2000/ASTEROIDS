#include "Asteroid.h"

Asteroid CreateAsteroid(Asteroid& asteroid)
{
	asteroid.size.x = 10;
	asteroid.size.y = 10;
	asteroid.position.x = 800;
	asteroid.position.y = 384;
	asteroid.radius = 20;
	asteroid.speed.x = 10;
	return asteroid;
}

void DrawAsteroid(Asteroid& asteroid)
{
	DrawCircle((int)asteroid.position.x, (int)asteroid.position.y, asteroid.radius, WHITE);
}