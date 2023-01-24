#pragma once

#include"interfaceObjects.h"

class headerClass : public interfaceObjects
{

public:
	  enum btnsEnum
	  {
		  openMenu,
		  play,
		  pause
	  };
	
private:
	std::vector<btnsStruct>btnsV = {
		{"ÌÅÍÞ", {20, 20, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"ÑÒÀÐÒ", {20+ gameSettings::menuSetting.btnW*2, 20, gameSettings::menuSetting.btnW/2, gameSettings::menuSetting.btnH}},
		{"ÏÀÓÇÀ", {20+ gameSettings::menuSetting.btnW * 3, 20, gameSettings::menuSetting.btnW/2, gameSettings::menuSetting.btnH}},
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

