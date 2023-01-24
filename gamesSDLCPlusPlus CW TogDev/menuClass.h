#pragma once

#include "interfaceObjects.h"

class menuClass : public interfaceObjects
{
public:/*const*/ enum btnsEnum
	{
		playBtn,
		loadBtn,
		settingBtn,
		save,
		aboutGame,
		quitBtn,
	};
private:
	short positionStartX = gameSettings::winSetting.winW / 2 - gameSettings::menuSetting.btnW / 2;
	short positionStartY = 50;
	std::vector< btnsStruct>btnsV = {
		{"ÈÃÐÀÒÜ", {positionStartX, positionStartY, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"ÇÀÃÐÓÇÈÒÜ", {positionStartX, positionStartY*2, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"ÍÀÑÒÐÎÉÊÈ", {positionStartX, positionStartY * 3, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"ÑÎÕÐÀÍÈÒÜ", {positionStartX, positionStartY * 4, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"ÎÁ ÈÃÐÅ", {positionStartX, positionStartY * 5, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"ÂÛÕÎÄ", {positionStartX,positionStartY * 6, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
	};
	SDL_Rect menuRect = { 0, 0 , gameSettings::winSetting.winW, gameSettings::winSetting.winH};
	
public:
	menuClass(SDL_Surface* bgImg, SDL_Surface* btnImg, TTF_Font* font) :
		interfaceObjects(bgImg, btnImg, font) {
		this->btns = this->btnsV;
		this->objRect = this->menuRect;
	}
	~menuClass()
	{
		this->btnsV.clear();

	}
	void blit() {
		this->blitBg();
		this->blitBtns();
		SDL_UpdateWindowSurface(gameSettings::winSetting.win);
	}
};

