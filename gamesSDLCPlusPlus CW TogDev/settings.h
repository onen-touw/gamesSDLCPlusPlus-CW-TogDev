#pragma once

#include<vector>
#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include <time.h>

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
	short pading20 = 20;
	short btnH=45, btnW = 150;
	enum menuState
	{
		close,
		mainMenuWindow,
		setting,
		about
	};
};
struct winSettings
{
	const short header = 70;
	const short block = 400;
	const short midSection = 200;
	const short winH = 620+this->header;
	const short winW = block*2 + this->midSection;
	const short winTopBorder = 31;

	SDL_Window* win = nullptr;
	SDL_Surface* surface = nullptr;
};
///========================================================================================



struct objParams
{
	std::string path;
	short int position;
	short lenth;
};


struct point
{
	short p1 = 0;
	short p2 = 0;
};

enum ObjectID {
	g2,
	g5,
	g10,
	g,

	TOTAL
};
//struct objCompParam
//{
//	SDL_Surface* img = nullptr;
//	short lenth = 0;
//	unsigned short id = 0;
//};

struct objectsForCompair {
	std::vector<objParams>objParam = {
		{"./image/objects/g2.png",g2, 2},
		{"./image/objects/g5.png", g5, 5},
		{"./image/objects/g10.png" , g10, 10},
		{"./image/objects/g.png" , g, short(rand()%50)},
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

