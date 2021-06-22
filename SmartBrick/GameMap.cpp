#include "GameMap.h"

bool GameMap::FillVector(vector<Vector2i>& vectorToFill, string tagName, string value)
{
	if (value == ("</" + tagName + ">"))
		return false;


	char val1[8] = "\0";
	char val2[8] = "\0";
	int j = 0;
	for (int i = 1; i < value.length(); ++i)
	{
		if (isdigit(value[i]))
		{
			val1[j++] = value[i];
		}
		else
		{
			val1[j] = '\0';
			j = 0;
			for (int l = i + 1; l < value.length(); ++l)
			{
				if (isdigit(value[l]))
				{
					val2[j++] = value[l];
				}
				else
				{
					val2[j] = '\0';
					break;
				}
			}
			break;
		}
	}

	vectorToFill.push_back(Vector2i(atoi(val1), atoi(val2)));

	return true;
}

GameMap::GameMap()
{
	LoadMap("Levels/level1.gamemap");
}

void GameMap::LoadMap(string path)
{
	Blocks.clear();
	Walls.clear();
	Goals.clear();

	Player = Vector2i();

	ifstream ifs;
	ifs.open(path);
	while (!ifs.eof())
	{
		string line;
		ifs >> line;

		if (line == "<Walls>")
		{
			ifs >> line;
			while (FillVector(Walls, "Walls", line))
			{
				ifs >> line;
			}
		}
		else if (line == "<Blocks>")
		{
			ifs >> line;
			while (FillVector(Blocks, "Blocks", line))
			{
				ifs >> line;
			}

		}
		else if (line == "<Goals>")
		{
			ifs >> line;
			while (FillVector(Goals, "Goals", line))
			{
				ifs >> line;
			}
		}
		else if (line == "<Player>")
		{
			ifs >> line;
			Player.x = line[1] - '0';
			Player.y = line[3] - '0';
		}
		else if (line == "<Size>")
		{
			ifs >> line;
			this->TileSize = atoi(line.c_str());
		}
	}
	ifs.close();
}

void GameMap::MovePlayer(int dirX, int dirY)
{
	bool IsWall = false;
	for (auto i : Walls)
	{
		if (Player.x + dirX == i.x && Player.y + dirY == i.y)
		{
			IsWall = true;
			break;
		}
	}
	for (auto& i : Blocks)
	{
		if (Player.x + dirX == i.x && Player.y + dirY == i.y)
		{
			bool IsBlocked = false;
			for (auto j : Walls)
			{
				if (i.x + dirX == j.x && i.y + dirY == j.y)
				{
					IsBlocked = true;
					break;
				}
			}
			for (auto j : Blocks)
			{
				if (i.x + dirX == j.x && i.y + dirY == j.y)
				{
					IsBlocked = true;
					break;
				}
			}
			if (IsBlocked)
			{
				IsWall = true;
				break;
			}
			else
			{
				i.x += dirX;
				i.y += dirY;
			}
		}
	}

	if (!IsWall)
	{
		Player.x += dirX;
		Player.y += dirY;
	}
}

bool GameMap::IsEnd() const
{
	bool OnGoal = false;
	for (auto i : Blocks)
	{
		OnGoal = false;
		for (auto j : Goals)
		{
			if (i.x == j.x && i.y == j.y)
			{
				OnGoal = true;
				break;
			}
		}
		if (!OnGoal)
		{
			break;
		}
	}
	return OnGoal;
}

void GameMap::RenderBlocks(RenderWindow * target)
{
	for (auto i : Blocks)
	{
		RectangleShape shape(Vector2f(this->TileSize, this->TileSize));
		shape.setPosition(i.x * this->TileSize, i.y * this->TileSize);
		Texture texture;
		texture.loadFromFile("Tiles/block.png");
		shape.setTexture(&texture);
		target->draw(shape);
	}
}

void GameMap::RenderWalls(RenderWindow * target)
{
	for (auto i : Walls)
	{
		RectangleShape shape(Vector2f(this->TileSize, this->TileSize));
		shape.setPosition(i.x * this->TileSize, i.y * this->TileSize);
		Texture texture;
		texture.loadFromFile("Tiles/wall.png");
		shape.setTexture(&texture);
		target->draw(shape);
	}
}

void GameMap::RenderGoals(RenderWindow * target)
{
	for (auto i : Goals)
	{
		CircleShape shape(this->TileSize / 6);
		shape.setPosition(i.x * this->TileSize + this->TileSize / 3, i.y * this->TileSize + this->TileSize / 3);
		shape.setFillColor(Color(214, 149, 133));
		target->draw(shape);
	}
}

void GameMap::RenderPlayer(RenderWindow * target)
{
	RectangleShape player(Vector2f(this->TileSize, this->TileSize));
	player.setPosition(Player.x * this->TileSize, Player.y * this->TileSize);
	Texture texture;
	texture.loadFromFile("Tiles/player.png");
	player.setTexture(&texture);
	target->draw(player);
}
