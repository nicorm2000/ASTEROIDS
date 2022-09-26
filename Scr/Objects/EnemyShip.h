#pragma once
#include "raylib.h"

struct EnemyShip
{
	Vector2 position{};
	Vector2 size{};
	Vector2 speed{};
	float rotation;
	bool isActive;
	Texture2D enemyTexture;
};

EnemyShip CreateEnemyShip(EnemyShip& enemyShip);

void DrawEnemyShip(EnemyShip& enemyShip)
