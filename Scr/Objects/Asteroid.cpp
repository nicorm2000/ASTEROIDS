#include "Asteroid.h"
#include "raylib.h"

Asteroid CreateAsteroid(Asteroid& asteroid, Size asteroidSize, Texture2D texture)
{
	asteroid.size.x = 20;
	asteroid.size.y = 20;
	asteroid.position.x = GetRandomValue(0, 1024);
	asteroid.position.y = GetRandomValue(0, 768);
	asteroid.speed.x = GetRandomValue(-100, 100);
	asteroid.speed.y = GetRandomValue(-100, 100);
	asteroid.color = WHITE;
	asteroid.isActive = true;
	asteroid.asteroidTexture = texture;
	asteroid.asteroidDirection = { asteroid.position.x, asteroid.position.y };

	switch (asteroidSize)
	{
	case Size::BIG:
		asteroid.radius = 50;
		return asteroid;
		break;
	case Size::MEDIUM:
		asteroid.radius = 35;
		return asteroid;
		break;
	case Size::SMALL:
		asteroid.radius = 20;
		return asteroid;
		break;
	}
}

void DrawAsteroid(Asteroid& asteroid)
{
	//hitbox
	DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, RED);
	DrawTexture(asteroid.asteroidTexture, asteroid.position.x - asteroid.radius, asteroid.position.y - asteroid.radius, asteroid.color);
}
