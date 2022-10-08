#include "Asteroid.h"
#include "raylib.h"

Asteroid CreateAsteroid(Asteroid& asteroid, Size asteroidSize, Texture2D texture)
{
	asteroid.size.x = 20;
	asteroid.size.y = 20;
	asteroid.position.x = static_cast<float>(GetRandomValue(0, 1024));
	asteroid.position.y = static_cast<float>(GetRandomValue(0, 768));
	asteroid.speed.x = static_cast<float>(GetRandomValue(-100, 100));
	asteroid.speed.y = static_cast<float>(GetRandomValue(-100, 100));
	asteroid.color = WHITE;
	asteroid.isActive = true;
	asteroid.asteroidTexture = texture;
	asteroid.asteroidDirection = { asteroid.position.x, asteroid.position.y };
	asteroid.origin = { 0,0 };
	asteroid.rotation = 0;
	asteroid.source = { 0,0,0,0 };
	asteroid.dest = { 0,0,0,0 };

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
	//DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, RED);
	DrawTexture(asteroid.asteroidTexture, static_cast<int>(asteroid.position.x) - static_cast<int>(asteroid.radius), static_cast<int>(asteroid.position.y) - static_cast<int>(asteroid.radius), asteroid.color);
}
