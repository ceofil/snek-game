/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <cmath>
#include <random>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(rd()),
	xrange(0, gfx.ScreenWidth - 30),
	yrange(0, gfx.ScreenHeight - 30),
	xgoal(2, xnrcells-3),
	ygoal(2, ynrcells-3),
	brd(gfx,xboard,yboard,cellsize,cellsize,xnrcells,ynrcells),
	nr(gfx, xboard + cellsize + 10, yboard + cellsize + 10, 2, 2, 100, 7),
	text(gfx, xboard + cellsize + 10, yboard + cellsize + 10, 1, 1, 100, 7),
	gameoverscreen(gfx,sw/2,sh/2-40,10,10,10,10),
	snek(start),
	goal(5,5)
{	
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		if (lastmove.equal( right ) == false) {
			snek.delta = left;
			snek.setheadvertical(false);
			
		}
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		if (lastmove.equal( left ) == false) {
			snek.delta = right;
			snek.setheadvertical(false);
		}
	}
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		if (lastmove.equal( down ) == false) {
			snek.delta = up;
			snek.setheadvertical(true);
		}
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		if (lastmove.equal( up ) == false) {
			snek.delta = down;
			snek.setheadvertical(true);
		}
	}

	if (!gameover) {
		if (snek.getnseg()>startlen) {
			kframe++;
			fps = sqrt(snek.getnseg()) + 3;
			if (kframe >= 60 / fps) {
				if (goal.isEaten(snek)) {
					snek.grow();
					spawnGoal();
				}
				snek.update();
				if (lastmove.equal(snek.delta) == false) {
					snek.setneckedge();
				}
				lastmove = snek.delta;
				std::cout << 1;

				kframe = 0;
			}
			
			if (wnd.kbd.KeyIsPressed(VK_CONTROL)) {
				snek.grow();
				snek.update();
			}
			
			snek.dead = snek.dead || (snek.getheadx() < 1 || snek.getheady() < 1 || snek.getheadx() > xnrcells - 2 || snek.getheady() > ynrcells - 2);
			snek.dead = snek.dead || snek.isinTail(snek.getheadloc(), 1, snek.getnseg());
			gameover = snek.dead;
		}
		else {
			for (int i = 1; i <= startlen; i++) {
				snek.grow();
				snek.update();
			}
		}

	}
	else {
		wall = Colors::Red;
		if (snek.getnseg() > maxscore) {
			maxscore = snek.getnseg();
		}
		
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			snek.newgame(start);
			gameover = false;
			wall = Colors::Blue;
			snek.dead = false;
		}
	}
}





void Game::ComposeFrame()
{

	drawthinwallz();

	goal.draw(brd);

	snek.draw(brd);
	
	if (!gameover) {
		text.drawstring("length", 0, 5, Colors::White);
		nr.drawint(snek.getnseg(), 20, 0, Colors::White);
		text.drawstring("speed", 7, 28, Colors::White);
		nr.drawint(fps, 20, 12, Colors::White);

		if (maxscore > 0) {

			text.drawstring("high score", 7, 500, Colors::White);
			nr.drawint(maxscore, 14 - nrcifre(maxscore) * 5 / 2, 237, Colors::White);
		}
	}
	else {
		gameoverscreen.drawint(snek.getnseg(), 0-nrcifre(snek.getnseg())*5/2, 0, Colors::White);
		text.drawstring("press enter", 330, 501, Colors::White);
	}

	
}




void Game::drawthinwallz()
{
	gfx.DrawRectPoints(xboard + cellsize - wallthick, yboard + cellsize-wallthick, xboard + (xnrcells - 1)*cellsize+wallthick, yboard + (ynrcells - 1)*cellsize+wallthick, wall);
	
	
	gfx.DrawRectPoints(xboard+cellsize, yboard+cellsize, xboard+(xnrcells-1)*cellsize, yboard + (ynrcells - 1)*cellsize, bg);
}
void Game::spawnGoal()
{
	goal.spawn(xgoal(rng), ygoal(rng));
	while (goal.validspawn(snek)) {
		goal.spawn(xgoal(rng), ygoal(rng));
	}
}

int Game::nrcifre(int n)
{
	if (n == 0) return 1;
	else{
		int k = 0;
		while (n) {
			n = n / 10;
			k++;
		}
		return k;///
	}
}
