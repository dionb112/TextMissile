/// <summary>
/// Dion Buckley
/// C00220868
/// Missile Text Based Game
/// Select warhead, Acquire target, Launch code, Arm Missile, Collion ? Valid ? 
/// 45 mins into #96
/// </summary>
#include <iostream>

enum Screen
{
	Main,
	Select,
	Acquire,
	Launch
};

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
struct Game {
	Screen currScr;
	int choice = 0;
	void mainScr()
	{
		std::cout << "1. Select War Head" << std::endl;
		std::cout << "2. Check Intel" << std::endl;
		std::cout << "3. Launch Missile" << std::endl;
		std::cout << "4. Quit" << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			selectScr();
			break;
		case 2:
			intelScr();
			break;
		default:
			break;
		}
	}
	void selectScr()
	{
		std::cout << "1. Explosive" << std::endl;
		std::cout << "2. Nuclear" << std::endl;
		std::cin >> choice;
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
	}
	void explosive()
	{
	}
	void nuclear()
	{
	}
	void intelScr()
	{
		int counter = 0;
		//doing cmd window timer here for intel
	}

};
struct Missile {
	WarHead payload;
	Coordinates coordinates;
	Target target;


	bool isArmed;

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
int main()
{
	Game game;
	game.mainScr();
	std::system("pause");
	return 1;
}

