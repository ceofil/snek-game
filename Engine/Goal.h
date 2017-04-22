#pragma once
#include "Graphics.h"
#include "Snek.h"
#include "Board.h"
#include <random>

class Goal
{
public:
	Goal(int x, int y);
	void spawn(int x, int y);
	void draw(Board& brd);
	bool validspawn(Snek& snek);
	bool isEaten(Snek& snek);
private:
	Location loc;
	Color c=Colors::Red;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xrange;
	std::uniform_int_distribution<int> yrange;
};