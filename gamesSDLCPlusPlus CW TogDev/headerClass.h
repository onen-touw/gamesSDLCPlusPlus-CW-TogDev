#pragma once

#include"interfaceObjects.h"

class headerClass : public interfaceObjects
{


	
public:const short openMenu = 0;
private:
	//short positionStartX = gameSettings::winSetting.winW / 2 - gameSettings::menuSetting.btnW / 2;
	//short positionStartY = 50;
	std::vector< btnsStruct>btnsV = {
		{"МЕНЮ", {20, 20, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
	};
	SDL_Rect Rect = { 0, 0 , gameSettings::winSetting.winW, gameSettings::winSetting.headerHeight };

	
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

	void blitInfo(short int killcount, short int lcount)
	{
		std::string text = "Уровень: " + std::to_string(lcount) + "   Убийств: " + std::to_string(killcount);
		blit();
		this->blitWithTxt2(text.c_str(), { gameSettings::winSetting.winW / 2, 30 });
	}

};

