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
	const short header = 70;
	const short winH = 600 + this->header;
	const short winW = 900;
	const short winTopBorder = 31;

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
struct snakePaaram
{
	point lastPos = { 0,0 };
	point pos = { 0,0 };
};


enum _directions {
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

struct cellV
{
	int x = 0, y = 0;	///px
	int i = 0, j = 0;	///cell in matrix

};

struct fieldSettings
{
	enum imagesField
	{
		empty,
		border,

		TOTAL
	};

	const int fieldSizeH = 40;		///cells
	const int fieldSizeW = 60;		///cells
	const int cellSize = 30;		///px

	std::vector<imagePath>fieldImagesPathVector = {
		{"./image/field/emptyCell.png", imagesField::empty},
		{"./image/field/borderWall.png", imagesField::border},
	};


	enum imagesSnake
	{
		head, body, tail, emptyCell
	};
	std::vector<imagePath>snakeImagesPathVector = {
		{"./image/snake/head.png", imagesSnake::head},
		{"./image/snake/body.png", imagesSnake::body},
		{"./image/snake/tail.png", imagesSnake::tail},
		{"./image/snake/empty.png", imagesSnake::emptyCell},
	};

};

namespace gameSettings {

	extern winSettings winSetting;
	extern menuSettings menuSetting;
	extern fieldSettings fieldSetting;
}

