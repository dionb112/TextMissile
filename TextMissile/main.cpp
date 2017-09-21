/// <summary>
/// Dion Buckley
/// C00220868
/// Missile Text Based Game
/// Select warhead, Acquire target, Launch code, Arm Missile, Collison ? Valid ? 
/// Known Bugs: Need to learn about threading so I can keep the clock updating while system is paused.
/// Time taken: Average 20 hours ?
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
	RESET,
	WAITING
};
typedef struct Position
{
	int x;
	int y;
	std::string coordCheck ="";
	void print()
	{
		std::cout << x << "North, " << y <<"East."<< std::endl;
	}
	void setTarget()
	{
		x = rand() % 400 + 1;
		y = rand() % 400 + 1;
		coordCheck = x + "," + y;
	}
	void centreMissile()
	{
		x = 200;
		y = 200;
	}
}Coordinates;

typedef struct Enemy {
	Coordinates coordinates; //enemy pos
}Target;

enum WarHead { EXPLOSIVE, NUCLEAR, SAFETY };

struct Missile {
	Coordinates coordinates; //missile pos
	Target target; //missiles attempted target (enemies)
	bool isArmed = false;
	void arm()
	{
		if (!isArmed)
		{
			isArmed = true;
		}
		else
		{
			isArmed = false;
		}
	}
};

struct Game {
	WarHead payload;
	Screen currScr;
	Missile missile;
	std::string input;
	std::string launchCode = "0000";
	std::string coords = "";
	int choice = 0;
	int intel = 5;
	int counter = 0;
	int civDistance = 0;
	bool intelValid = false;
	bool gameOver = false;
	bool isArmed = false;
	bool launched = false;
	bool collision = false;

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
		missile.coordinates.centreMissile();
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
		std::cout << "1. Explosive (<1km explosion radius)" << std::endl;
		std::cout << "2. Nuclear   (40km explosion radius + 40km fallout radius)" << std::endl;
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
			std::cout << "By the way Mr. President, the launch code has been changed.. against the better judgement of all our experts.. to: ";
			dotDotDot();
			std::cout << "\n'0000'" << std::endl;
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
		std::string launch;
		if (intelValid)
		{
			if (isArmed)
			{
				while (launch != launchCode)
				{

					std::cout << "Please enter Launch Code now [or enter 1 to go back(where you can check Intel)]: ";
					std::getline(std::cin, launch);
					if (launch == "1")
					{
						currScr = MAIN;
						break;
					}
				}
				std::cout << "Please enter gps coordinates for target now in the format 'X,Y'\n[or enter 1 to go back(where you can check Intel)]: ";
				std::getline(std::cin, coords);
				if (coords == "1")
				{
					currScr = MAIN;
				}
				if (launch == launchCode && coords != "1")
				{
					std::cout << std::endl << "Arming missile now!";
					dotDotDot();
					std::cout << "Missile Launched!" << std::endl;

					currScr = WAITING;
					launched = true;

					dotDotDot();
					missile.arm();
					if (coords != missile.target.coordinates.coordCheck)
					{
						Sleep(3000);
						collision = false;
						currScr = AFTERMATH;
					}
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
	void waitingScr()
	{
		std::cout << ".";
	}
	void afterScr()
	{
		if (payload == EXPLOSIVE)
		{
			if (collision)
			{
				std::cout << "Direct Hit! And you avoided all civilian casualties, GREAT job!" << std::endl;
				currScr = RESET;
			}
			else
			{
				isArmed = false;
				launched = false;
				payload = SAFETY;
				std::cout << "Current Intel Valid for " << intel << " minutes! So act fast!" << std::endl << std::endl;
				std::cout << "Near Miss! Please check intel fully before loading up another warhead if do you want to try again!" << std::endl;
				currScr = MAIN;
			}
		}
		else if (payload == NUCLEAR)
		{
			if (civDistance > 80 && collision)
			{
				std::cout << "Direct Hit! And you avoided all civilian casualties, GREAT job!" << std::endl;
				currScr = RESET;
			}
			else if (collision && civDistance < 80)
			{
				std::cout << "Did you NOT read the Intel?!\nYou anihalted the target AND all of the nearby civilians, you Monster!" << std::endl;
				currScr = RESET;
			}
			else
			{
				isArmed = false;
				launched = false;
				std::cout << "Current Intel Valid for " << intel << " minutes! So act fast!" << std::endl << std::endl;
				payload = SAFETY; 
				std::cout << "You missed.. with a Nuke.. please check all intel fully before firing again!" << std::endl;
				currScr = MAIN;
			}
		}
		missile.arm();
		std::cout << std::endl;
		system("pause");
	}
	void reset()
	{
		std::cout << "1: Play again" << std::endl;
		std::cout << "2: Quit" << std::endl;
		userInput();
		if (choice == 1)
		{
			coords = "";
			choice = 0;
			intel = 5;
			counter = 0;
			civDistance = 0;
			intelValid = false;
			isArmed = false;
			launched = false;
			collision = false; 
			payload = SAFETY;
			currScr = MAIN;
			missile.coordinates.centreMissile();
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
		if (missile.isArmed)
		{
			//missile updating
			if (missile.coordinates.x < missile.target.coordinates.x)
			{
				missile.coordinates.x++;
			}
			if (missile.coordinates.x > missile.target.coordinates.x)
			{
				missile.coordinates.x--;
			}
			if (missile.coordinates.y < missile.target.coordinates.y)
			{
				missile.coordinates.y++;
			}
			if (missile.coordinates.y > missile.target.coordinates.y)
			{
				missile.coordinates.y--;
			}
			//collisions
			if (missile.coordinates.x == missile.target.coordinates.x && missile.coordinates.y == missile.target.coordinates.y)
			{
				collision = true;
				currScr = AFTERMATH;
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
		else if (currScr == WAITING)
		{
			waitingScr();
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

