#include "Snek.h"


Snek::Snek(Location & loc)
{
	segmentz[0].inHead(loc);
	for (int i = 1; i < nsegmax; i++) {
		Color col(0, 255-patternlen*gradient + abs(i%patternlen-patternlen/2)*gradient, 0);
		segmentz[i].c = col;
	}
}
void Snek::newgame(Location& loc)
{
	nseg = 1;
	segmentz[0].inHead(loc);
	delta = { 1,0 };
}

void Snek::draw(Board& brd)
{
	for (int i = 1; i < nseg; i++) {
		segmentz[i].Draw(brd);
	}
	DrawHead(brd);
	
}

int Snek::Segment::getlocx()
{
	return loc.x;
}
int Snek::Segment::getlocy()
{
	return loc.y;
}

void Snek::Segment::Draw(Board& brd)
{

	if (edge) {
		brd.DrawCellStroke(loc, 4, 4, c);
	}
	else {
		if (vertical) {
			brd.DrawCellStroke(loc, 5, 2, c);
		}
		else {
			brd.DrawCellStroke(loc, 2, 5, c);
		}
	}
}
void Snek::DrawHead(Board& brd)
{
	brd.DrawCellStroke(getheadloc(), 1,1, chead);
}

void Snek::Segment::follow(Segment& target)
{
	loc = target.loc;
	vertical = target.vertical;
	edge = target.edge;
}
void Snek::Segment::moveby(Location & del)
{
	loc.add(del);
}
void Snek::Segment::inHead(Location & inputloc)
{
	loc = inputloc;
	vertical = false;
	edge = false;
	c = Snek::chead;
}
void Snek::Segment::inTail()
{
	//c = Snek::ctail;

}
bool Snek::Segment::isinTail(Location & test)
{
	return loc.equal(test);
}
void Snek::moveTail()
{
	for (int i = nseg - 1; i > 0; i--)
	{
		segmentz[i].follow(segmentz[i - 1]);
	}
}

void Snek::moveHead()
{
	segmentz[0].moveby(delta);
}

void Snek::update()
{
	moveTail();
	moveHead();
	if (nseg > 0) {
		segmentz[nseg - 1].edge = false;
	}
	
}

void Snek::setdelta(int x, int y)
{
	delta.x = x;
	delta.y = y;
}

Location Snek::getheadloc()
{
	return {segmentz[0].getlocx(), segmentz[0].getlocy()};
}

int Snek::getheadx()
{
	return segmentz[0].getlocx();
}
int Snek::getheady()
{
	return segmentz[0].getlocy();
}

int Snek::getnseg()
{
	return nseg;
}

void Snek::grow()
{
	nseg++;
	segmentz[nseg - 1].inTail();
	segmentz[nseg - 1].follow(segmentz[nseg - 2]);
}

bool Snek::isinTail(Location& loc, int start, int end)
{
	bool test = false;
	for (int i = start; i < end; i++) {
		test = test || segmentz[i].isinTail(loc);
	}
	return test;
}

void Snek::setheadvertical(bool input)
{
	segmentz[0].vertical = input;
}

void Snek::setneckedge()
{
	segmentz[1].edge = true;
}



