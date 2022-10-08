#include "Asteroid.h"
#include "raylib.h"

Asteroid CreateAsteroid(Asteroid& asteroid, Size asteroidSize)
{
	switch (asteroidSize)
	{
	case Size::BIG:
		asteroid.size.x = 20;
		asteroid.size.y = 20;
		asteroid.position.x = GetRandomValue(0, 1024);
		asteroid.position.y = GetRandomValue(0, 768);
		asteroid.radius = 50;
		asteroid.speed.x = GetRandomValue(-100, 100);
		asteroid.speed.y = GetRandomValue(-100, 100);
		asteroid.color = WHITE;
		asteroid.isActive = true;
		asteroid.asteroidTexture = LoadTexture("../resources/enemy1.png");
		asteroid.asteroidDirection = { asteroid.position.x, asteroid.position.y };
		return asteroid;
		break;
	case Size::MEDIUM:
		asteroid.size.x = 20;
		asteroid.size.y = 20;
		asteroid.position.x = GetRandomValue(0, 1024);
		asteroid.position.y = GetRandomValue(0, 768);
		asteroid.radius = 35;
		asteroid.speed.x = GetRandomValue(-100, 100);
		asteroid.speed.y = GetRandomValue(-100, 100);
		asteroid.color = WHITE;
		asteroid.isActive = false;
		asteroid.asteroidTexture = LoadTexture("../resources/enemy2.png");
		asteroid.asteroidDirection = { asteroid.position.x, asteroid.position.y };
		return asteroid;
		break;
	case Size::SMALL:
		asteroid.size.x = 20;
		asteroid.size.y = 20;
		asteroid.position.x = GetRandomValue(0, 1024);
		asteroid.position.y = GetRandomValue(0, 768);
		asteroid.radius = 20;
		asteroid.speed.x = GetRandomValue(-100, 100);
		asteroid.speed.y = GetRandomValue(-100, 100);
		asteroid.color = WHITE;
		asteroid.isActive = false;
		asteroid.asteroidTexture = LoadTexture("../resources/enemy3.png");
		asteroid.asteroidDirection = { asteroid.position.x, asteroid.position.y };
		return asteroid;
		break;
	}
}

void DrawAsteroid(Asteroid& asteroid, Size asteroidSize)
{
	//hitbox
	if (asteroid.asteroidSize == Size::SMALL)
	{
		DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, WHITE);
		//DrawTexture(asteroid.asteroidTexture, asteroid.position.x - asteroid.radius, asteroid.position.y - asteroid.radius, asteroid.color);
	}
	else if (asteroid.asteroidSize == Size::MEDIUM)
	{
		DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, WHITE);
		//(asteroid.asteroidTexture, asteroid.position.x - asteroid.radius, asteroid.position.y - asteroid.radius, asteroid.color);
	}
	else if (asteroid.asteroidSize == Size::BIG)
	{
		DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, WHITE);
		//DrawTexture(asteroid.asteroidTexture, asteroid.position.x - asteroid.radius, asteroid.position.y - asteroid.radius, asteroid.color);
	}
}
