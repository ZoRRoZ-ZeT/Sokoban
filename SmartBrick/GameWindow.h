#pragma once
#include "GameMap.h"
#include <math.h>

class GameWindow
{
private:
	RenderWindow * window;
	GameMap* map;
	int dirX, dirY;
	vector<string> levels;
	int currentMap;
	bool IsOpen;
	bool GameEnded;

	Clock TimeElapsed;

public:
	GameWindow(int width, int height);
	~GameWindow();

	void UpdateInput();
	void Update();
	void Render();

	bool Closed() const;
};

