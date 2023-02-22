#pragma once

#include"settings.h"
#include <windows.h>

class baseGameClass
{
public:
	baseGameClass() {
		
		//this->calculateWinParametrs();
	}
	~baseGameClass(){}

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

