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
};
struct winSettings
{
	const short header = 70;
	const short winH = 600;
	const short winW = 600;
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


struct cell
{
	point pxPosition = { 0,0 };
	bool live = false;
};

struct fieldStruct
{
	enum images
	{
		cellDead,
		cellLive,

		TOTAL
	};
	std::vector<imagePath>fieldImagesPathVector = {
		{"", images::cellDead},
		{"", images::cellLive},
	};

};

namespace gameSettings {

	extern winSettings winSetting;
	extern menuSettings menuSetting;
}

