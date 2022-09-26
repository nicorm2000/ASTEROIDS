#include "Asteroid.h"
#include "raylib.h"

Asteroid CreateAsteroid(Asteroid& asteroid, Size asteroidSize)
{
	switch (asteroidSize)
	{
	case BIG:
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
		return asteroid;
		break;
	case MEDIUM:
		asteroid.size.x = 20;
		asteroid.size.y = 20;
		asteroid.position.x = GetRandomValue(0, 1024);
		asteroid.position.y = GetRandomValue(0, 768);
		asteroid.radius = 35;
		asteroid.speed.x = GetRandomValue(-100, 100);
		asteroid.speed.y = GetRandomValue(-100, 100);
		asteroid.color = WHITE;
		asteroid.isActive = true;
		asteroid.asteroidTexture = LoadTexture("../resources/enemy2.png");
		return asteroid;
		break;
	case SMALL:
		asteroid.size.x = 20;
		asteroid.size.y = 20;
		asteroid.position.x = GetRandomValue(0, 1024);
		asteroid.position.y = GetRandomValue(0, 768);
		asteroid.radius = 20;
		asteroid.speed.x = GetRandomValue(-100, 100);
		asteroid.speed.y = GetRandomValue(-100, 100);
		asteroid.color = WHITE;
		asteroid.isActive = true;
		asteroid.asteroidTexture = LoadTexture("../resources/enemy3.png");
		return asteroid;
		break;
	}
}

void DrawAsteroid(Asteroid& asteroid, Size asteroidSize)
{
	//hitbox
	if (asteroid.asteroidSize ==  SMALL)
	{
		DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, RED);
		DrawTexture(asteroid.asteroidTexture, asteroid.position.x - asteroid.radius, asteroid.position.y - asteroid.radius, asteroid.color);
	}
	else if (asteroid.asteroidSize == MEDIUM)
	{
		DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, RED);
		DrawTexture(asteroid.asteroidTexture, asteroid.position.x - asteroid.radius, asteroid.position.y - asteroid.radius, asteroid.color);
	}
	else if (asteroid.asteroidSize == BIG)
	{
		DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, RED);
		DrawTexture(asteroid.asteroidTexture, asteroid.position.x - asteroid.radius, asteroid.position.y - asteroid.radius, asteroid.color);
	}
}
