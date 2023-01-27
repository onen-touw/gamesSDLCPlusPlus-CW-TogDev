#pragma once

#include"interfaceObjects.h"


class endGameWinClass : public interfaceObjects
{

public: int cancel = 1, saveAndRestart = 0;

private:
	short positionStartX = gameSettings::winSetting.winW / 2 - gameSettings::menuSetting.btnW;
	short positionStartY = 500;
	std::vector< btnsStruct>btnsV = {
		{"ÑÎÕÐÀÍÈÒÜ", {positionStartX, positionStartY, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"ÎÒÌÅÍÀ", {positionStartX + gameSettings::menuSetting.btnW, positionStartY, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
	};

	SDL_Rect winRect = { 4*this->pading, 2*this->pading + gameSettings::winSetting.headerHeight,
		gameSettings::winSetting.winW  - 8* this->pading,
		gameSettings::winSetting.winH - gameSettings::winSetting.headerHeight - 4*this->pading };

public:
	endGameWinClass(SDL_Surface* bgImg, SDL_Surface* btnImg, TTF_Font* font): interfaceObjects(bgImg, btnImg, font) {
		this->btns = this->btnsV;
		this->objRect = this->winRect;
	}
	~endGameWinClass()
	{
		this->btnsV.clear();
	}

	void blit() {
		std::cout << winRect.x << " " << winRect.y << " " << winRect.w << " " << winRect.h << " \n";
		this->blitBg();
		this->blitBtns();
	}

};

