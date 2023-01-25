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
		statistic,
		about
	};
};
struct winSettings
{
	const short header = 70;
	const short block = 400;
	const short midSection = 200;
	const short winH = 600+this->header;
	const short winW = block*2 + this->midSection;
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

enum ObjectID {
	cat,
	python,
	cow,

	TOTAL
};
struct objCompParam
{
	SDL_Surface* img = nullptr;
	short lenth = 0;
	unsigned short id = 0;
};

struct objectsForCompair {
	std::vector<imagePath>objectsImgPath = {
		{"./image/objects/cat.png", cat},
		{"./image/objects/python.png", python},
		{"./image/objects/cow.png" , cow},
	};
};



struct cell
{
	point pxPosition = { 0,0 };
	bool live = false;
};



namespace gameSettings {

	extern winSettings winSetting;
	extern menuSettings menuSetting;
	extern objectsForCompair objectsFC;
}

