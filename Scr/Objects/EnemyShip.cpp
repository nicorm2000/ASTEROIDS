#include "Objects/EnemyShip.h"

EnemyShip CreateEnemyShip(EnemyShip& enemyShip)
{
	enemyShip.size.x = 100;
	enemyShip.size.y = 50;
	enemyShip.position.x = static_cast<float>(GetRandomValue(0, 1024));
	enemyShip.position.y = static_cast<float>(GetRandomValue(150, 650));
	if (enemyShip.position.y <= GetScreenHeight() / 2.0f && enemyShip.position.y >= 284)
	{
		enemyShip.position.y = static_cast<float>(GetRandomValue(150, 283));
	}
	else if (enemyShip.position.y >= GetScreenHeight() / 2.0f && enemyShip.position.y <= 484)
	{
		enemyShip.position.y = static_cast<float>(GetRandomValue(485, 650));
	}
	enemyShip.speed.x = static_cast<float>(GetRandomValue(-300, 300));
	do
	{
		enemyShip.speed.x = static_cast<float>(GetRandomValue(-300, 300));
	} while (enemyShip.speed.x == 0);
	enemyShip.rotation = 0;
	enemyShip.isActive = true;
	enemyShip.enemyTexture = LoadTexture("../resources/enemyship1.png");
	return enemyShip;
}

void DrawEnemyShip(EnemyShip& enemyShip)
{
	//DrawRectangleLines(static_cast<int>(enemyShip.position.x), static_cast<int>(enemyShip.position.y), static_cast<int>(enemyShip.size.x) * 2, static_cast<int>(enemyShip.size.y) * 2, RED);
	DrawTextureEx(enemyShip.enemyTexture, { enemyShip.position.x, enemyShip.position.y }, enemyShip.rotation, 2, WHITE);
}