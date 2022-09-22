#include "Asteroid.h"

Asteroid CreateAsteroid(Asteroid& asteroid)
{
	asteroid.size.x = 20;
	asteroid.size.y = 20;
	asteroid.position.x = 800;
	asteroid.position.y = 384;
	asteroid.radius = 20;
	asteroid.speed.x = 10;
	asteroid.color = WHITE;
	return asteroid;
}

void DrawAsteroid(Asteroid& asteroid)
{
	DrawCircle((int)asteroid.position.x, (int)asteroid.position.y, asteroid.radius, asteroid.color);
}