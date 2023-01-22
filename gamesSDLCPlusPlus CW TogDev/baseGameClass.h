#pragma once

#include"settings.h"
#include <windows.h>

class baseGameClass
{
private:


	//short safePadingTop = 100;

public:
	baseGameClass() {
		
		//this->calculateWinParametrs();
	}
	~baseGameClass(){}

	//void calculateWinParametrs() {
	//	gameSettings::fieldSetting.minCountCellInWin.height = 
	//		int((GetSystemMetrics(SM_CYSCREEN) - this->safePadingTop - gameSettings::winObjSize.winTopBorder - 
	//			gameSettings::winObjSize.menuHeader) / gameSettings::winObjSize.cellSize);

	//	gameSettings::fieldSetting.minCountCellInWin.width = int(GetSystemMetrics(SM_CXSCREEN) / gameSettings::winObjSize.cellSize);
	//	
	//	this->winSize.width = gameSettings::fieldSetting.minCountCellInWin.width * gameSettings::winObjSize.cellSize;

	//	this->winSize.height = gameSettings::fieldSetting.minCountCellInWin.height * gameSettings::winObjSize.cellSize + gameSettings::winObjSize.menuHeader;

	//	std::cout << gameSettings::fieldSetting.minCountCellInWin.height << "x" <<
	//		gameSettings::fieldSetting.minCountCellInWin.width << "\n" <<
	//		this->winSize.height << "x" <<
	//		this->winSize.width << "\n";
	//}

	

	bool initModuls() {
		bool success = true;

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::cout << "problem::SDL_Init\n" << SDL_GetError << "\n";
			success = false;
		}

		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags)) {
			std::cout << "Can't init image: " << IMG_GetError() << std::endl;
			success = false;
		}

		gameSettings::winSetting.win = SDL_CreateWindow("GameLive", 0, gameSettings::winSetting.winTopBorder,
			 gameSettings::winSetting.winW, gameSettings::winSetting.winH, SDL_WINDOW_SHOWN);

		if (gameSettings::winSetting.win == nullptr) {
			std::cout << "Can't create window: " << SDL_GetError() << std::endl;
			success = false;
		}
		gameSettings::winSetting.surface = SDL_GetWindowSurface(gameSettings::winSetting.win);
		if (gameSettings::winSetting.surface == nullptr)
		{
			std::cout << "problem::surface\n";
			success = false;
		}

		if (TTF_Init()!=0)
		{
			std::cout << "problem::ttfInit\n";
			success = false;
		}

		return success;
	}
};

