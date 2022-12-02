#pragma once

#include "raylib.h"

struct Ship
{
	Vector2 size {};
	Vector2 speed {};
	Vector2 position {};
	Vector2 origin{};
	Vector2 normalizeDir{};
	float rotation;
	float radius;
	bool isAlive;
	int lives;
	int score;
	Rectangle source;
	Rectangle dest;
	Color color;
	bool isActive;
	Texture2D shipTexture;
	Texture2D shipOriginalTexture;
	Texture2D shipTextureMovement;
};

Ship CreateShip(Ship& spaceShip);

void DrawShip(Ship& spaceShip, float angle);