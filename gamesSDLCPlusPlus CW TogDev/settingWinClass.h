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
	short positionStartX = gameSettings::winSetting.winW / 2 - gameSettings::menuSetting.btnW / 2;
	short positionStartY = 50;
	std::vector< btnsStruct>btnsV = {
		{"ËÅÃÊÎ", {positionStartX, positionStartY, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"ÍÎÐÌÀËÜÍÎ", {positionStartX, positionStartY * 2, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"ÑËÎÆÍÎ", {positionStartX, positionStartY * 3, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"ÏÐÈÍßÒÜ", {positionStartX, positionStartY * 5, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"ÎÒÌÅÍÀ", {positionStartX, positionStartY * 6, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
	};
	SDL_Rect winRect = { 0, 0 , gameSettings::winSetting.winW, gameSettings::winSetting.winH };
	

	short tempHardness = gameSettings::fieldSetting.hardness;

	SDL_Surface* switchImg = nullptr;
	SDL_Rect switchRect = { int(positionStartX - 1.5 * gameSettings::menuSetting.btnH), (tempHardness + 1) * positionStartY,
		gameSettings::menuSetting.btnH,gameSettings::menuSetting.btnH };

public:
	settingWinClass(SDL_Surface* bgImg, SDL_Surface* btnImg,SDL_Surface* switchImg, TTF_Font* font) :
		interfaceObjects(bgImg, btnImg, font) {
		this->btns = this->btnsV;
		this->objRect = this->winRect;
		this->switchImg = switchImg;
	}
	~settingWinClass()
	{
		this->btnsV.clear();
		SDL_FreeSurface(this->switchImg);
	}

	void changeHardness(int i) {
		this->tempHardness = i;
		this->blit();
		SDL_UpdateWindowSurface(gameSettings::winSetting.win);
	}
	void applyHardness() {
		gameSettings::fieldSetting.hardness = this->tempHardness;
	}
	void resetHardness() {
		this->tempHardness = gameSettings::fieldSetting.hardness;
	}

	void blit() {
		this->blitBg();
		this->blitBtns();
		this->switchRect.y = (tempHardness + 1) * positionStartY;
		SDL_BlitScaled(this->switchImg, NULL, gameSettings::winSetting.surface, &switchRect);
		SDL_UpdateWindowSurface(gameSettings::winSetting.win);
	}

};

