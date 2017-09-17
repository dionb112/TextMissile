/// <summary>
/// Dion Buckley
/// C00220868
/// Missile Text Based Game
/// Select warhead, Acquire target, Launch code, Arm Missile, Collison ? Valid ? 
/// </summary>
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>

enum Screen {
	Main,
	Select,
	Intel,
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

struct Missile {
	WarHead payload;
	Coordinates coordinates;
	Target target;


	bool isArmed = false;

	void arm(int type)
	{
		if (isArmed)
		{
			isArmed = false;
		}
		else
		{
			isArmed = true;
		}
		if (type == 1)
		{
			payload = EXPLOSIVE;
		}
		else
		{
			payload = NUCLEAR;
		}
	}
	void update()
	{
		if (payload == EXPLOSIVE)
		{
			//40 % chance of success
		}
		else
		{
			//if (civ < 80km) Fail
			//else 100% success
		}
	}
};
struct Game {
	Missile missile;
	Screen currScr;
	int choice = 0;
	int intel = 20;
	int counter = 0;
	int civDistance = 0;

	void run()
	{
		///deWiTTERS Game Loop helped immensly here, I was trying to do it with clock_t etc. and it was updating way too frequently.
		const int FRAMES_PER_SECOND = 60;
		const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

		DWORD nextGameTick = GetTickCount(); //returns current no. of ms elapsed since system started.
		int sleepTime = 0;
		bool gameOver = false;
		
		mainScr();
		while (!gameOver)
		{
			update();
			print();
			nextGameTick += SKIP_TICKS;
			sleepTime = nextGameTick - GetTickCount();
			if (sleepTime >= 0)
			{
				Sleep(sleepTime);
			}
		}
	}
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
			currScr = Select;
			break;
		case 2:
			currScr = Intel;
			break;
		case 3:
			currScr = Launch;
			break;
		case 4:
			system("exit");
		default:
			break;
		}
	}
	void selectScr()
	{
		std::cout << "1. Explosive (0.5km explosion radius, 40% accuracy)" << std::endl;
		std::cout << "2. Nuclear (80km explosion radius, 100% accuracy)" << std::endl;
		std::cin >> choice;
		missile.arm(choice);
		switch (choice)
		{
		case 1:
			std::cout << "You have armed the Explosive warhead!" <<std::endl;
			break;
		case 2:
			std::cout << "You have armed the Nuclear warhead!" << std::endl;
			break;
		default:
			break;
		}
		currScr = Main;
	}
	void intelScr()
	{

		std::cout << "New Intel incoming.";
		for (int i = 0; i < 3; i++)
		{
			Sleep(1000);
			std::cout << ".";
			Sleep(500);
		}
		std::cout << std::endl;
		std::cout << "Hostiles discovered at x,y." << std::endl;
		std::cout << "Locking on.";
		for (int i = 0; i < 3; i++)
		{
			Sleep(1000);
			std::cout << ".";
			Sleep(500);
		}
		std::cout << std::endl << "Target locked on." << std::endl;
		civDistance = rand() % 400 + 1;
		std::cout << "Be aware! Civilians within " << civDistance << "km of target." << std::endl;
		system("pause");
		currScr = Main;

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
			currScr = Main;
		}
	}
	void update()
	{
		counter++;
		if (counter == 60)
		{
			intel--;
			counter = 0;
		}
		missile.update();
	}
	void print()
	{
		system("CLS");
		//std::cout << "Current Intel Valid for " << intel << std::endl;
		if (currScr == Main)
		{
			mainScr();
		}
		else if (currScr == Select)
		{
			selectScr();
		}
		else if (currScr == Intel )
		{
			intelScr();
		}
		else if (currScr == Launch )
		{
			launchScr();
		}
	}
};
int main()
{
	Game game;
	game.run();
	return 1;
}

