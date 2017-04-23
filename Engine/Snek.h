#pragma once
#include "Graphics.h"
#include "Board.h"
#include "Location.h"

class Snek
{
private:
	class Segment
	{
	public:
		int getlocx();
		int getlocy();
		void Draw(Board& brd);
		void follow(Segment& target);
		void moveby(Location& del);
		void inHead(Location& loc);
		void inTail();
		bool isinTail(Location& test);
		bool vertical = false;
		bool edge = false;
		int index;
		Color c;
	private:
		Location loc = { 3,3 };
	};


public:
	Snek(Location& loc);
	//Board& brd;
	void draw(Board& brd);
	void DrawHead(Board & brd);
	void moveTail();
	Location delta = { 1,0 };
	void moveHead();
	void update();
	void setdelta(int x, int y);
	Location getheadloc();
	int getheadx();
	int getheady();
	int getnseg();
	void grow();
	bool dead = false;
	bool isinTail(Location& loc, int start, int end);
	void setheadvertical(bool input);
	void setneckedge();
	static constexpr int patternlen = 5;
	static constexpr int gradient = 25;
	void newgame(Location& loc);
	
private:
	static constexpr Color chead = { 0, 135, 0 };
	int nseg = 1;
	static constexpr int nsegmax = 500;
	Segment segmentz[nsegmax];
	Color v[nsegmax];
};