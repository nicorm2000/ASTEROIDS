#include "Objects/EnemyShip.h"

EnemyShip CreateEnemyShip(EnemyShip& enemyShip)
{
	enemyShip.size.x = 100;
	enemyShip.size.y = 50;
	enemyShip.position.x = GetRandomValue(0, 1024);
	enemyShip.position.y = GetRandomValue(150, 650);
	//if (enemyShip.position.y <= GetScreenHeight() / 2.0f && enemyShip.position.y >= 284)
	//{
	//	enemyShip.position.y = GetRandomValue(150, 283);
	//}
	//else if (enemyShip.position.y >= GetScreenHeight() / 2.0f && enemyShip.position.y <= 484)
	//{
	//	enemyShip.position.y = GetRandomValue(485, 650);
	//}
	enemyShip.speed.x = GetRandomValue(-150, 150);
	enemyShip.rotation = 0;
	enemyShip.isActive = true;
	enemyShip.enemyTexture = LoadTexture("../resources/enemyship1.png");
	return enemyShip;
}

void DrawEnemyShip(EnemyShip& enemyShip)
{
	//DrawRectangleLines(enemyShip.position.x, enemyShip.position.y, enemyShip.size.x * 2, enemyShip.size.y * 2, RED);
	DrawTextureEx(enemyShip.enemyTexture, { enemyShip.position.x, enemyShip.position.y }, enemyShip.rotation, 2, WHITE);
}