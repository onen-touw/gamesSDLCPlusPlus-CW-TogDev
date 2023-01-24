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
		save,
		about
	};
};
struct winSettings
{
	const short header = 70;
	const short winH = 670;
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
	short int p1 = 0;
	short int p2 = 0;
};


struct cell
{
	point pxPosition = { 0,0 };
	bool live = false;
};

struct fieldSettings
{
	enum hardnessEn
	{
		easy,normal,hard,
	};
	short int easyModeNumberOfCells = 12;
	short int normalModeNumberOfCells = 25;
	short int hardModeNumberOfCells = 50;
	short hardness = hardnessEn::easy;
	enum images
	{
		cellDeadEasy,
		cellLiveEasy,
		cellDeadNormal,
		cellLiveNormal,
		cellDeadHard,
		cellLiveHard,

		TOTAL
	};
	std::vector<imagePath>fieldImagesPathVector = {
		{"./image/fieldImages/cellDeadEasy.png", images::cellDeadEasy},
		{"./image/fieldImages/cellLiveEasy.png", images::cellLiveEasy},
		{"./image/fieldImages/cellDeadNormal.png", images::cellDeadNormal},
		{"./image/fieldImages/cellLiveNormal.png", images::cellLiveNormal},
		{"./image/fieldImages/cellDeadHard.png", images::cellDeadHard},
		{"./image/fieldImages/cellLiveHard.png", images::cellLiveHard}
	};

};

namespace gameSettings {

	extern winSettings winSetting;
	extern menuSettings menuSetting;
	extern fieldSettings fieldSetting;
}

