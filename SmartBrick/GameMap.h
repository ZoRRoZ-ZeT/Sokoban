#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace sf;
using namespace std;

class GameMap
{
private:
	vector<Vector2i> Blocks;
	vector<Vector2i> Walls;
	vector<Vector2i> Goals;

	Vector2i Player;

	int TileSize;

	bool FillVector(vector<Vector2i>& vectorToFill, string tagName, string value);
public:
	GameMap();

	void LoadMap(string path);

	void MovePlayer(int dirX, int dirY);

	bool IsEnd() const;

	void RenderBlocks(RenderWindow* target);
	void RenderWalls(RenderWindow* target);
	void RenderGoals(RenderWindow* target);

	void RenderPlayer(RenderWindow* target);
};

