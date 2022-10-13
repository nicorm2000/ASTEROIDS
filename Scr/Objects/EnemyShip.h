#pragma once

#include "raylib.h"

struct EnemyShip
{
	Vector2 position{};
	Vector2 size{};
	Vector2 speed{};
	Vector2 origin{};
	float rotation;
	bool isActive;
	Rectangle source{};
	Rectangle dest{};
	Texture2D enemyTexture;
};

EnemyShip CreateEnemyShip(EnemyShip& enemyShip);

void DrawEnemyShip(EnemyShip& enemyShip);
