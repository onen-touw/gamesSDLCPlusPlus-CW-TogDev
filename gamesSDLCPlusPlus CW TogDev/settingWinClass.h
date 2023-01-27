#pragma once

#include "interfaceObjects.h"

class settingWinClass : public interfaceObjects
{


public: enum btnsEnum
{
	easy,
	normal,
	hard,
	apply,
	cancel,
};
private:
	short positionStartX = gameSettings::winSetting.winW / 2 - gameSettings::menuSetting.btnW;
	short positionStartY = 500;
	std::vector< btnsStruct>btnsV = {
		{"ÏÐÈÍßÒÜ", {positionStartX, gameSettings::winSetting.header + positionStartY, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"ÎÒÌÅÍÀ", {positionStartX+ gameSettings::menuSetting.btnW, gameSettings::winSetting.header + positionStartY, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
	};
	SDL_Rect menuRect = { 0, 0 , gameSettings::winSetting.winW, gameSettings::winSetting.winH };

	
	short positionStartXforPict = gameSettings::winSetting.winW / 2 - gameSettings::menuSetting.btnW;
	short positionStartÍforPict = gameSettings::winSetting.header;
	short pictSize = 70;
	

public:
	settingWinClass(SDL_Surface* bgImg, SDL_Surface* btnImg, TTF_Font* font) :
		interfaceObjects(bgImg, btnImg, font) {
		this->btns = this->btnsV;
		this->objRect = this->menuRect;
	}
	~settingWinClass()
	{

	}

	void blit() {
		this->blitBg();
		this->blitBtns();

		SDL_UpdateWindowSurface(gameSettings::winSetting.win);
	}

};

