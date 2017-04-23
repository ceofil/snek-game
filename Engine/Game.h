/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <cmath>
#include <random>
#include "Board.h"
#include "Snek.h"
#include "Goal.h"
#include <iostream>
#include "Text.h"
#include "FrameTimer.h"



class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	
	/********************************/
	/*  User Functions              */
	void drawthinwallz();

	void spawnGoal();
	int nrcifre(int n);
	
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	FrameTimer ft;

	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xrange;
	std::uniform_int_distribution<int> yrange;
	std::uniform_int_distribution<int> vrange;
	std::uniform_int_distribution<int> xgoal;
	std::uniform_int_distribution<int> ygoal;

	Board brd;
	Text nr;
	Text text;
	Text gameoverscreen;
	Location start = { 3,3 };
	Snek snek;
	Goal goal;

	int xsc = -2;
	int test = 0;
	int kframe = 0;
	int fps = 3;
	int maxkframes = 60 / fps;
	static constexpr int sw = Graphics::ScreenWidth;
	static constexpr int sh = Graphics::ScreenHeight;
	static constexpr int cellsize = 20;
	static constexpr int xnrcells = sw / cellsize - 1;   //fullscreen
	static constexpr int ynrcells = sh / cellsize - 1;	 //fullscreen
	static constexpr int xboard = (sw - xnrcells* cellsize) / 2;
	static constexpr int yboard = (sh - ynrcells* cellsize) / 2;
	static constexpr int xwall = cellsize + xboard;
	static constexpr int ywall = cellsize + yboard;
	Color wall = Colors::Blue;
	Color bg = { 0,0,0 };
	int wallthick = cellsize / 2;
	bool gameover = false;
	int startlen = 5;
	int maxscore = 0;
	Location up = { 0,-1 };
	Location down = { 0,1 };
	Location right = { 1,0 };
	Location left = { -1,0 };
	Location lastmove;
	/********************************/
};


