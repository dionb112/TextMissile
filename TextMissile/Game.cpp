#include "Game.h"
Game::Game()
{
}

void Game::run()
{
	currScr = (Screen::Main);
	int choice = 0;
	if (currScr == Screen::Main)
	{
		std::cout << "1. Select War Head" << std::endl;
		std::cout << "2. Acquire Target" << std::endl;
		std::cout << "3. Launch Missile" << std::endl;
		std::cout << "4. Quit" << std::endl;
	}
	else if (currScr == Screen::Select)
	{
		std::cout << "1. Explosive" << std::endl;
		std::cout << "2. Nuclear" << std::endl;
	}
	else if (currScr == Screen::Acquire)
	{
		std::cout << "Enter and X Coordinate between 0 - 400" << std::endl;
		//std::cin >> coordinates.x;

		std::cout << "2. Nuclear" << std::endl;
	}

	std::cin >> choice;
}



