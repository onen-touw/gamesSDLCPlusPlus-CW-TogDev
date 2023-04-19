#pragma once

#include<vector>
#include<iostream>
#include<string>
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
	const short winH = 600+this->header;
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
};


struct point
{
	short p1 = 0;
	short p2 = 0;
};

enum ObjectID {
	p1_3x3,
	p2_3x3,
	p3_3x3,
	p4_3x3,
	p5_3x3,
	p6_3x3,
	p7_3x3,
	p8_3x3,
	p9_3x3,

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
		{"./image/pieces/3x3/1.png", p1_3x3},
		{"./image/pieces/3x3/2.png", p2_3x3},
		{"./image/pieces/3x3/3.png", p3_3x3},
		{"./image/pieces/3x3/4.png", p4_3x3},
		{"./image/pieces/3x3/5.png", p5_3x3},
		{"./image/pieces/3x3/6.png", p6_3x3},
		{"./image/pieces/3x3/7.png", p7_3x3},
		{"./image/pieces/3x3/8.png", p8_3x3},
		{"./image/pieces/3x3/9.png", p9_3x3}
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

