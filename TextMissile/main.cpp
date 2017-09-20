/// <summary>
/// Dion Buckley
/// C00220868
/// Missile Text Based Game
/// Select warhead, Acquire target, Launch code, Arm Missile, Collison ? Valid ? 
/// Known Bugs: Need to learn about threading so I can keep the clock updating while system is paused.
/// Time taken: Average 5 - 20 hours ?
/// </summary>
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>

enum Screen {
	MAIN,
	SELECT,
	INTEL,
	LAUNCH,
	AFTERMATH,
	RESET
};
typedef struct Position
{
	int x;
	int y;
	void print()
	{
		std::cout << x << "North, " << y <<"East."<< std::endl;
	}
	void setTarget()
	{
		x = rand() % 400 + 1;
		y = rand() % 400 + 1;
	}
}Coordinates;

typedef struct Enemy {
	Coordinates coordinates; //enemy pos
}Target;

enum WarHead { EXPLOSIVE, NUCLEAR, SAFETY };

struct Missile {
	Coordinates coordinates; //missile pos
	Target target; //missiles attempted target (enemies)
};

struct Game {
	WarHead payload;
	Screen currScr;
	Missile missile;
	std::string input;
	int choice = 0;
	int intel = 5;
	int counter = 0;
	int civDistance = 0;
	int launchCode = 0000;
	bool intelValid = false;
	bool gameOver = false;
	bool isArmed = false;
	bool launched = false;

	void run()
	{
		///deWiTTERS Game Loop helped immensly here, I was trying to do it with clock_t etc. and it was updating way too frequently.
		const int FRAMES_PER_SECOND = 60;
		const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

		DWORD nextGameTick = GetTickCount(); //returns current no. of ms elapsed since system started.
		int sleepTime = 0;

		std::cout << "Welcome to Missile, Intel, Terrorist Attack Game!" << std::endl;
		std::cout << std::endl;
		system("pause"); 

		currScr = MAIN;
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
	void userInput()
	{
		while (!false)
		{
			std::getline(std::cin, input);
			std::stringstream myStream(input);
			if (myStream >> choice)
				break;
			std::cout << "Invalid entry, please try again" << std::endl;
		}
	}
	void mainScr()
	{
		std::cout << "1. Select War Head" << std::endl;
		std::cout << "2. Acquire Target / Check Intel" << std::endl;
		std::cout << "3. Prepare for Launch" << std::endl;
		std::cout << "4. Quit" << std::endl;
		userInput();
		switch (choice)
		{
		case 1:
			currScr = SELECT;
			break;
		case 2:
			currScr = INTEL;
			break;
		case 3:
			currScr = LAUNCH;
			break;
		case 4:
			gameOver = true;
			break;
		default:
			std::cout << "You have four choices.. choose one!" << std::endl;
			std::cout << std::endl;
			system("pause");
			break;
		}

	}
	void selectScr()
	{
		std::cout << "1. Explosive (<1km explosion radius, 40 % accuracy)" << std::endl;
		std::cout << "2. Nuclear   (80km explosion radius, 100% accuracy)" << std::endl;
		userInput();
		switch (choice)
		{
		case 1:
			std::cout << "You have prepared the Explosive warhead!" << std::endl;
			payload = EXPLOSIVE;
			break;
		case 2:
			std::cout << "You have prepared the Nuclear warhead!" << std::endl;
			payload = NUCLEAR;
			break;
		default:
			std::cout << "There is only two warheads to chose from, it really couldn't be much more simple." << std::endl;
			std::cout << std::endl;
			system("pause");
			break;
		}
		isArmed = true;
		std::cout << std::endl;
		system("pause");
		currScr = MAIN;
	}
	void intelScr()
	{
		if (intelValid)
		{
			std::cout << "Current Intel - Launch Code: " << launchCode << "; Civilians within " << civDistance << "km of hostiles;" << " Hostiles at gps coordinates: ";
			missile.target.coordinates.print(); 
		}
		else
		{
			std::cout << "New Intel incoming";
			dotDotDot();

			missile.target.coordinates.setTarget();
			std::cout << "\nHostiles discovered at gps coordinates: ";
			missile.target.coordinates.print();
			Sleep(250);
			std::cout << "Locking on now";
			dotDotDot();
			std::cout << std::endl << "Target locked on." << std::endl;
			Sleep(500);
			civDistance = rand() % 400 + 1;
			std::cout << std::endl << "Be aware! Civilians within " << civDistance << "km of target." << std::endl;
			intelValid = true;
			intel = 5;
		}
		std::cout << std::endl;
		system("pause");
		currScr = MAIN;
	}
	void launchScr()
	{
		if (intelValid)
		{
			if (isArmed)
			{
				std::cout << "Please enter Launch Code: ";
				userInput();
				std::cout << std::endl << "Close enough, I guess...Arming missile now!";
				dotDotDot();
				std::cout << std::endl << "\nMissile armed and ready for Launch sir!\n";
				std::cout << "1. Launch already!!!" << std::endl;
				std::cout << "2. Abort!!!" << std::endl;
				userInput();
				switch (choice)
				{
				case 1:
					dotDotDot();
					std::cout << "Missile Launched!" << std::endl; 
					launched = true;
					currScr = AFTERMATH;					
					break;
				case 2:
					dotDotDot();
					std::cout << "Launch aborted" << std::endl;
					currScr = MAIN;					
					break;
				default:
					std::cout << "You have two choices.. choose one!" << std::endl;
					std::cout << std::endl;
					system("pause");
					break;
				}

			}
			else
			{
				std::cout << "Please select, and arm, a War Head first" << std::endl;
				currScr = MAIN;
			}
		}
		else
		{
			std::cout << "Currently attempting to fire blind..\n Please aquire valid intel before lauching death tubes.." << std::endl;
			currScr = MAIN;
		}
		std::cout << std::endl;
		system("pause");

	}
	void afterScr()
	{
		if (payload == EXPLOSIVE)
		{
			int temp = rand() % 10 + 1;
			if (temp < 5)
			{
				std::cout << "Direct Hit! And you avoided all civilian casualties, GREAT job!" << std::endl;
				std::cout << std::endl;
				system("pause");
				currScr = RESET;
			}
			else
			{
				isArmed = false;
				launched = false;
				payload = SAFETY;
				std::cout << "Current Intel Valid for " << intel << " minutes! So act fast!" << std::endl << std::endl;
				std::cout << "Near Miss! Load up another warhead if you want to try again!" << std::endl;
				std::cout << std::endl;
				system("pause"); 
				currScr = MAIN;
			}
		}
		else
		{
			if (civDistance > 80)
			{
				std::cout << "Direct Hit! And you avoided all civilian casualties, GREAT job!" << std::endl;
			}
			else
			{
				std::cout << "Did you NOT read the Intel?!\nYou anihalted the target AND all of the nearby civilians, you Monster!" << std::endl;
			}
			std::cout << std::endl;
			system("pause");
			currScr = RESET;
		}
	}
	void reset()
	{
		std::cout << "1: Play again" << std::endl;
		std::cout << "2: Quit" << std::endl;
		userInput();
		if (choice == 1)
		{
			choice = 0;
			intel = 5;
			counter = 0;
			civDistance = 0;
			intelValid = false;
			isArmed = false;
			launched = false;
			payload = SAFETY;
			currScr = MAIN;
		}
		else if (choice == 2)
		{
			gameOver = true;
		}
		else
		{
			std::cout << "If you're not going to play along at this point just close the window." << std::endl;
			std::cout << std::endl;
			system("pause");
		}
	}
	void update()
	{
		if (intelValid)
		{
			counter++;
			if (counter == 2)
			{
				intel--;
				counter = 0;
			}
		}
		if (intel == 0)
		{
			intelValid = false;
		}
	}
	void print()
	{
		system("CLS");
		if (intelValid && !launched)
		{
			std::cout << "Current Intel Valid for " << intel << " minutes! So act fast!" << std::endl << std::endl;
		}
		if (currScr == MAIN)
		{
			mainScr();
		}
		else if (currScr == SELECT)
		{
			selectScr();
		}
		else if (currScr == INTEL )
		{
			intelScr();
		}
		else if (currScr == LAUNCH )
		{
			launchScr();
		}
		else if (currScr == AFTERMATH)
		{
			afterScr();
		}
		else if (currScr == RESET)
		{
			reset();
		}
	}
	void dotDotDot()
	{
		for (int i = 0; i < 3; i++)
		{
			Sleep(1000);
			std::cout << ".";
			Sleep(250);
		}
	}
};
int main()
{
	srand(time(NULL));
	Game game;
	game.run();
	return 1;
}

