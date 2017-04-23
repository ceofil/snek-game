#include "Board.h"
#include "Location.h"

Board::Board(Graphics & gfx, int xup, int yup, int xd, int yd,int wi,int he)
	:
	gfx(gfx)
{
	xboard = xup;
	yboard = yup;
	xdim = xd;
	ydim = yd;
	w = wi;
	h = he;
}

bool Board::cellinside(int x, int y)
{
	return
		x >= 0 &&
		y >= 0 &&
		x <= w &&
		y <= h
	;
}

void Board::DrawCell(int x, int y, Color c)
{
	//if (cellinside(x, y)) {
		gfx.DrawRectPoints(xboard + xdim*x, yboard + ydim*y, xboard + xdim*(x + 1), yboard + ydim*(y + 1), c);
	//}

}

void Board::DrawCell(Location loc, Color c)
{
	//if (cellinside(loc.x, loc.y)) {
		gfx.DrawRectPoints(xboard + xdim*loc.x, yboard + ydim*loc.y, xboard + xdim*(loc.x + 1), yboard + ydim*(loc.y + 1), c);
	//}

}
void Board::DrawCellStroke(Location loc, int stroke,int ostroke, Color c)
{
	//if (cellinside(loc.x, loc.y)) {
	gfx.DrawRectPoints(xboard + xdim*loc.x+stroke, yboard + ydim*loc.y+ostroke, xboard + xdim*(loc.x + 1)-stroke, yboard + ydim*(loc.y + 1) - ostroke, c);
	//}

}

void Board::DrawLine(int x, Color c)
{
	for (int i = 0; i < w; i++) {
		DrawCell(i, x, c);
	}
}
void Board::Draw4Line(int poz, int y, Color c)
{
	for (int i = poz; i < poz + 4; i++) {
		DrawCell(i, y, c);
	}
}

void Board::DrawCol(int y, Color c)
{
	for (int j = 0; j < h; j++) {
		DrawCell(y, j, c);
	}
}
void Board::DrawColUp(int y, Color c)
{
	for (int j = 0; j <= h / 2; j++) {
		DrawCell(y, j, c);
	}
}
void Board::DrawColDown(int y, Color c)
{
	for (int j = h / 2 + 1; j < h; j++) {
		DrawCell(y, j, c);
	}
}


void Board::draw1(int poz, Color c)
{
	DrawCol(poz+1 , c);
	/*
	DrawCell(poz, 2, c);
	DrawCell(poz+1, 1, c);
	DrawCell(poz+2, 0, c);
	*/
}
void Board::draw2(int poz, Color c)
{
	Draw4Line(poz, 0, c);
	Draw4Line(poz, 3, c);
	Draw4Line(poz, 6, c);

	DrawColUp(poz + 3, c);
	DrawColDown(poz, c);
}
void Board::draw3(int poz, Color c)
{
	Draw4Line(poz, 0, c);
	Draw4Line(poz, 3, c);
	Draw4Line(poz, 6, c);

	DrawColUp(poz + 3, c);
	DrawColDown(poz + 3, c);
}
void Board::draw4(int poz, Color c)
{
	DrawColUp(poz, c);
	DrawCol(poz + 3, c);
	Draw4Line(poz, 3, c);
}
void Board::draw5(int poz, Color c)
{
	Draw4Line(poz, 0, c);
	Draw4Line(poz, 3, c);
	Draw4Line(poz, 6, c);


	DrawColUp(poz, c);
	DrawColDown(poz + 3, c);
}
void Board::draw6(int poz, Color c)
{
	Draw4Line(poz, 0, c);
	Draw4Line(poz, 3, c);
	Draw4Line(poz, 6, c);

	DrawCol(poz, c);
	DrawColDown(poz + 3, c);
}
void Board::draw7(int poz, Color c)
{
	Draw4Line(poz, 0, c);
	//Draw4Line(poz, 3, c);

	DrawCol(poz + 3, c);

}
void Board::draw8(int poz, Color c)
{
	Draw4Line(poz, 0, c);
	Draw4Line(poz, 3, c);
	Draw4Line(poz, 6, c);

	DrawCol(poz, c);
	DrawCol(poz + 3, c);

}
void Board::draw9(int poz, Color c)
{
	Draw4Line(poz, 0, c);
	Draw4Line(poz, 3, c);
	Draw4Line(poz, 6, c);

	DrawCol(poz + 3, c);
	DrawColUp(poz, c);

}
void Board::draw0(int poz, Color c)
{
	Draw4Line(poz, 0, c);
	Draw4Line(poz, 6, c);

	DrawCol(poz, c);
	DrawCol(poz + 3, c);
}

void Board::drawint(int n, Color c, int poz) 
{

	if (n)
	{
		int cn = n;
		int nr = 0;
		int v[8];

		if(n<0){
			DrawCell(poz, 3, c);
			DrawCell(poz + 1, 3, c);
			DrawCell(poz + 2, 3, c);
			poz += 4;
			cn = -cn;
		}

		while (cn) {
			v[nr] = cn % 10;
			cn = cn / 10;
			nr++;
		}
		for (int i = nr - 1; i >= 0; i--,poz+=5) {
			if (v[i] == 1) {
				draw1(poz, c);
				poz -= 1;
			}
			else if (v[i] == 2) {
				draw2(poz, c);
			}
			else if (v[i] == 3) {
				draw3(poz, c);
			}
			else if (v[i] == 4) {
				draw4(poz, c);
			}
			else if (v[i] == 5) {
				draw5(poz, c);
			}
			else if (v[i] == 6) {
				draw6(poz, c);
			}
			else if (v[i] == 7) {
				draw7(poz, c);
			}
			else if (v[i] == 8) {
				draw8(poz, c);
			}
			else if (v[i] == 9) {
				draw9(poz, c);
			}
			else if (v[i] == 0) {
				draw0(poz, c);
			}
		}

	}
	else
	{
		draw0(poz, c);
	}
	
}

int Board::getw()
{
	return w;
}

int Board::geth()
{
	return h;
}
