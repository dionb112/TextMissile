/// <summary>
/// Dion Buckley
/// C00220868
/// Missile Text Based Game
/// Select warhead, Acquire target, Launch code, Arm Missile, Collison ? Valid ? 
/// </summary>
#include <iostream>
#include <Windows.h>
#include <time.h>

typedef struct Position
{
	int x;
	int y;
	void print()
	{
		std::cout << x << y << std::endl;
	}
}Coordinates;

enum WarHead { EXPLOSIVE, NUCLEAR };

typedef struct Enemy {
	Coordinates coordinates;
}Target;

struct Missile {
	WarHead payload;
	Coordinates coordinates;
	Target target;


	bool isArmed = false;

	void arm()
	{
		if (isArmed)
		{
			isArmed = false;
		}
		else
		{
			isArmed = true;
		}
	}
	void update()
	{
		coordinates.x += 1;
		coordinates.y += 1;
	}
};
struct Game {
	Missile missile;
	int choice = 0;
	int intelCounter = 20;
	void mainScr()
	{
		std::cout << "1. Select War Head" << std::endl;
		std::cout << "2. Check Intel" << std::endl;
		std::cout << "3. Launch Missile" << std::endl;
		std::cout << "4. Quit" << std::endl;
		std::cin >> choice;
		system("CLS");
		switch (choice)
		{
		case 1:
			selectScr();
			break;
		case 2:
			intelScr();
			break;
		case 3:
			launchScr();
			break;
		case 4:
			system("exit");
		default:
			break;
		}
	}
	void selectScr()
	{
		std::cout << "1. Explosive" << std::endl;
		std::cout << "2. Nuclear" << std::endl;
		std::cin >> choice;
		missile.arm();
		system("CLS");
		switch (choice)
		{
		case 1:
			explosive();
			break;
		case 2:
			nuclear();
			break;
		default:
			break;
		}
		mainScr();
	}
	void intelScr()
	{

		std::cout << "Current Intel will be valid for: " <<intelCounter << " seconds." << std::endl;
		
		//doing cmd window timer here for intel
	}
	void launchScr()
	{
		if (missile.isArmed)
		{
			std::cout << "Launch Code: ****\nLaunching Missile!" << std::endl;
		}
		else
		{
			std::cout << "Please select, and arm, a War Head first" << std::endl;
			system("pause");
			system("CLS");
			mainScr();
		}
	}
	void explosive()
	{
	}
	void nuclear()
	{
	}
	void update()
	{
		if (intelCounter > 0)
		{
			Sleep(1000);
			intelCounter--;
		}
		else
		{
			intelCounter = 20;
		}
	}
};
int main()
{
	clock_t time;
	time = clock();
	Game game;
	game.mainScr();
	return 1;
}

