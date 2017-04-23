#include "Goal.h"

Goal::Goal(int x, int y)
{
	loc = { x,y };
}

void Goal::spawn(int x, int y)
{
	loc = { x,y };
}

void Goal::draw(Board & brd)
{
	brd.DrawCell(loc, c);
}

bool Goal::validspawn(Snek & snek)
{
	if (snek.isinTail(loc, 0, snek.getnseg())) {
		return true;
	}
	else {
		return false;
	}
}

bool Goal::isEaten(Snek & snek)
{
	return snek.getheadloc().equal(loc);
}
