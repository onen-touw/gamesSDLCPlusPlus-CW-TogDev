#pragma once

#include"interfaceObjects.h"

class headerClass : public interfaceObjects
{


	
public:const short openMenu = 0;
private:
	//short positionStartX = gameSettings::winSetting.winW / 2 - gameSettings::menuSetting.btnW / 2;
	//short positionStartY = 50;
	std::vector< btnsStruct>btnsV = {
		{"лемч", {20, 20, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
	};
	SDL_Rect Rect = { 0, 0 , gameSettings::winSetting.winW, gameSettings::winSetting.header };

	
public:
	headerClass(SDL_Surface* bgImg, SDL_Surface* btnImg, TTF_Font* font) :
		interfaceObjects(bgImg, btnImg, font) {
		this->btns = this->btnsV;
		this->objRect = this->Rect;
	}
	~headerClass()
	{
		this->btnsV.clear();

	}
	void blit() {
		this->blitBg();
		this->blitBtns();
	}



};

