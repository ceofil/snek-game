#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx, int xup, int yup, int xd, int yd, int wi, int he);
	bool cellinside(int x, int y);
	void DrawCell(int x, int y, Color c);
	void DrawCell(Location loc, Color c);
	void DrawCellStroke(Location loc, int stroke,int ostroke, Color c);
	void DrawLine(int x, Color c);
	void Draw4Line(int poz, int y, Color c);
	void DrawCol(int y, Color c);
	void DrawColUp(int y, Color c);
	void DrawColDown(int y, Color c);
	
		void draw1(int poz, Color c);
		void draw2(int poz, Color c);
		void draw3(int poz, Color c);
		void draw4(int poz, Color c);
		void draw5(int poz, Color c);
		void draw6(int poz, Color c);
		void draw7(int poz, Color c);
		void draw8(int poz, Color c);
		void draw9(int poz, Color c);
		void draw0(int poz, Color c);

		void drawint(int n, Color c, int poz);
	
	int getw();
	int geth();
private:
	int xboard=1;
	int yboard=1;
	int xdim=10;
	int ydim=10;
	int w;
	int h;
	Graphics& gfx;
};