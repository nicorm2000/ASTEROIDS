#include "Asteroid.h"

#include "raylib.h"

Asteroid CreateAsteroid(Asteroid& asteroid, Size asteroidSize, Texture2D texture)
{
	float aboveThePlayerX = 0;
	float aboveThePlayerY = 0;
	asteroid.size.x = 20;
	asteroid.size.y = 20;
	aboveThePlayerX = static_cast<float>(GetRandomValue(0, 10));
	if (aboveThePlayerX > 5)
	{
		asteroid.position.x = static_cast<float>(GetRandomValue(0, 450));
	}
	else
	{
		asteroid.position.x = static_cast<float>(GetRandomValue(700, 1024));
	}
	aboveThePlayerY = static_cast<float>(GetRandomValue(0, 10));
	if (aboveThePlayerY > 5)
	{
		asteroid.position.y = static_cast<float>(GetRandomValue(0, 250));
	}
	else
	{
		asteroid.position.y = static_cast<float>(GetRandomValue(650, 768));
	}
	asteroid.position.y = static_cast<float>(GetRandomValue(0, 768));
	asteroid.speed.x = static_cast<float>(GetRandomValue(-100, 100));
	asteroid.speed.y = static_cast<float>(GetRandomValue(-100, 100));
	asteroid.color = WHITE;
	asteroid.isActive = true;
	asteroid.asteroidTexture = texture;
	asteroid.asteroidDirection = { asteroid.position.x, asteroid.position.y };

	switch (asteroidSize)
	{
	case Size::BIG:
		asteroid.radius = 50;
		break;
	case Size::MEDIUM:
		asteroid.radius = 35;
		break;
	case Size::SMALL:
		asteroid.radius = 20;
		break;
	}
	return asteroid;
}

void DrawAsteroid(Asteroid& asteroid)
{
	//hitbox
	//DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, RED);
	DrawTexture(asteroid.asteroidTexture, static_cast<int>(asteroid.position.x) - static_cast<int>(asteroid.radius), static_cast<int>(asteroid.position.y) - static_cast<int>(asteroid.radius), asteroid.color);
}
