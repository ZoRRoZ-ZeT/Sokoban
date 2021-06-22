#include "GameWindow.h"

GameWindow::GameWindow(int width, int height)
{
	this->window = new RenderWindow(sf::VideoMode(800, 900), "SmartBrick");
	this->window->setFramerateLimit(60);
	this->map = new GameMap();
	this->levels.push_back("Levels/level1.gamemap");
	this->levels.push_back("Levels/level2.gamemap");
	this->levels.push_back("Levels/level3.gamemap");
	this->currentMap = 0;
	this->IsOpen = true;
	this->GameEnded = false;
	this->TimeElapsed = Clock();
	this->TimeElapsed.restart(); 
}

GameWindow::~GameWindow()
{
	this->window = nullptr;
}

void GameWindow::UpdateInput()
{
	Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
			this->IsOpen = false;
		}

		if (!GameEnded)
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::A))
			{
				dirX = -1;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::D))
			{
				dirX = 1;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::W))
			{
				dirY = -1;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::S))
			{
				dirY = 1;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::R))
			{
				this->map->LoadMap(this->levels[this->currentMap]);
			}
		}
		else
		{
			for (int k = -1; k < sf::Keyboard::KeyCount; ++k)
			{
				if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
				{
					window->close();
					this->IsOpen = false;
				}
			}
		}
	}
}

void GameWindow::Update()
{
	this->map->MovePlayer(dirX, dirY);
	dirX = 0;
	dirY = 0;

	if(!GameEnded)
		Render();
}

void GameWindow::Render()
{

	if (this->map->IsEnd())
	{
		this->currentMap++;
		if (this->currentMap >= this->levels.size())
		{
			window->clear();
			Font font;
			font.loadFromFile("Fonts/Dosis-Light.ttf");
			Text text(String("You Are Winner!"),font,48);
			text.setPosition((this->window->getSize().x - text.getGlobalBounds().width) / 2, this->window->getSize().y / 2 - 100);
			window->draw(text);

			Int64 currentTime = this->TimeElapsed.getElapsedTime().asSeconds();

			string minutes = to_string(currentTime / 60);
			string seconds = to_string(currentTime % 60);
			Text time(String(minutes + ":" + seconds),font);
			time.setPosition((this->window->getSize().x - time.getGlobalBounds().width) / 2, this->window->getSize().y / 2 - 50);
			window->draw(time);

			GameEnded = true;
		}
		else
		{
			this->map->LoadMap(this->levels[this->currentMap]);
		}
		
	}
	else
	{
		window->clear();
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				RectangleShape road(Vector2f(100, 100));
				Texture texture;
				texture.loadFromFile("Tiles/road.png");
				road.setTexture(&texture);
				road.setPosition(i * 100, j * 100);
				window->draw(road);
			}
		}

		this->map->RenderWalls(this->window);
		this->map->RenderGoals(this->window);
		this->map->RenderBlocks(this->window);

		this->map->RenderPlayer(this->window);
	}

	window->display();
}

bool GameWindow::Closed() const
{
	return !IsOpen;
}
