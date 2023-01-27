#pragma once

#include"settings.h"
#include <windows.h>

class baseGameClass
{
private:


public:
	baseGameClass() {
	}
	~baseGameClass(){
	
	}


	

	void initModuls() {
		bool success = true;
		std::string error = "baseGameClass::initModuls::\n";
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			//std::cout << "problem::SDL_Init\n" << SDL_GetError << "\n";
			error += "\tproblem::SDL_Init\n";
			success = false;
		}

		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags)) {
			std::cout << "Can't init image: " << IMG_GetError() << std::endl;
			error += "\tproblem::IMGL_Init\n"; 

			success = false;
		}

		gameSettings::winSetting.win = SDL_CreateWindow("GameLive", 0, gameSettings::winSetting.winTopBorder,
			 gameSettings::winSetting.winW, gameSettings::winSetting.winH, SDL_WINDOW_SHOWN);

		if (gameSettings::winSetting.win == nullptr) {
			std::cout << "Can't create window: " << SDL_GetError() << std::endl;
			error += "\tproblem::window creating\n";

			success = false;
		}
		gameSettings::winSetting.surface = SDL_GetWindowSurface(gameSettings::winSetting.win);
		if (gameSettings::winSetting.surface == nullptr)
		{
			//std::cout << "problem::surface\n";
			error += "\tproblem::surface creating\n";

			success = false;
		}

		if (TTF_Init() != 0)
		{
			//std::cout << "problem::ttfInit\n";
			error += "\tproblem::TTF_Init\n";
			success = false;
		}
		if (!success)
		{
			std::cout << error << "\n";
			system("pause");
			exit(-1);
		}
		return;
	}
};

