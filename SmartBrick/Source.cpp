#include "Game.h"
#include <Windows.h>

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	Game* game = new Game(800, 900);
	game->Run();
	return 0;
}
