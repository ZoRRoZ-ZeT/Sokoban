#include "Game.h"

Game::Game(int width, int height)
{
	window = new GameWindow(width, height);
}

Game::~Game()
{
	this->window = nullptr;
}

void Game::Run()
{
	while (true)
	{
		window->UpdateInput();

		if (window->Closed())
			break;

		window->Update();
	}
}
