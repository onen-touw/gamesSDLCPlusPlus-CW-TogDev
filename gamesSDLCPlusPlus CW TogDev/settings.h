#pragma once

#include<vector>
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>


///nessesary for menu work
///========================================================================================
struct btnsStruct
{
	std::string btnText = "";
	SDL_Rect rect = { 0,0,0,0 };
};
struct menuSettings
{
	//short padding5 = 5;	///px
	short btnH=45, btnW = 150;
	enum menuState
	{
		close,
		mainMenuWindow,
		load,
		setting,
		statistic,
		about
	};
};
struct winSettings
{
	const short	cellSize = 35;							///px
	const short	countOfCells = 21;
	const short headerHeight = 70;						///px
	const short winW = cellSize * countOfCells;			///px
	const short winH = winW + headerHeight;				///px
	const short winTopBorder = 31;						///px 

	SDL_Window* win = nullptr;
	SDL_Surface* surface = nullptr;
};
///========================================================================================



struct imagePath
{
	std::string path;
	short int position;
};


struct point
{
	short p1 = 0;
	short p2 = 0;
};


struct cell
{
	point pxPosition = { 0,0 };
	int objType = 1;
	int objLive = 3;	///for walls only
};

struct fieldSettings
{
	enum hardnessEnum
	{
		easy,normal,hard,
	};
	short hardness = hardnessEnum::easy;
	const short objEndurance = 3;
	const short maxWallLenth = 5;
	const short minWallLenth = 3;



	///fireImg, bombImg,

};

struct character
{
	short HP = 3;
	short CD = 3;

};

namespace gameSettings {

	extern winSettings winSetting;
	extern menuSettings menuSetting;
	extern fieldSettings fieldSetting;
}

