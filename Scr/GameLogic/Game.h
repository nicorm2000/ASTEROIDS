#pragma once

enum class GameScreen
{
	GAMETITLE = 0,
	GAME,
	HOWTOPLAY,
	CREDITS,
	EXIT
};

//struct ButtonsAndUI
//{
//	Vector2 size{};
//	const char* name;
//	int width;
//	Rectangle RectButton{};
//	Texture2D TextureButton;
//};

void RunGame();