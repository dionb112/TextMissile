#pragma once
#include <iostream>

enum class Screen
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

class Game
{
public:
	Game();
	void run();
private:
	Screen currScr;
};