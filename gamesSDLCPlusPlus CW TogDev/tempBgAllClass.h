#pragma once
#include"interfaceObjects.h"



class tempBgAllClass : public interfaceObjects
{



public:const short openMenu = 0;
private:
	//short positionStartX = gameSettings::winSetting.winW / 2 - gameSettings::menuSetting.btnW / 2;
	//short positionStartY = 50;
	/*std::vector< btnsStruct>btnsV = {
		{"лемч", {20, 20, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
	};*/
	SDL_Rect Rect = { 0, gameSettings::winSetting.header , gameSettings::winSetting.winW, gameSettings::winSetting.winH - gameSettings::winSetting.header };


public:
	tempBgAllClass(SDL_Surface* bgImg) :
		interfaceObjects(bgImg) {
		//this->btns = this->btnsV;
		this->objRect = this->Rect;
	}
	~tempBgAllClass()
	{
		//this->btnsV.clear();

	}
	void blit() {
		this->blitBg();
		/*this->blitBtns();*/
		SDL_UpdateWindowSurface(gameSettings::winSetting.win);
	}



};

