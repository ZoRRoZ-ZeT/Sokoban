#pragma once
#include "GameWindow.h"

class Game
{
private:
	GameWindow* window;

public:
	Game(int width, int height);
	~Game();

	void Run();
};

