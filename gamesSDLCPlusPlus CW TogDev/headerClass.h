#pragma once

#include"interfaceObjects.h"

class headerClass : public interfaceObjects
{

public:const short openMenu = 0, reset = 1;
private:
	

	std::vector< btnsStruct>btnsV = {
		{"лемч", {20, 20, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"яапняхрэ", {gameSettings::menuSetting.btnW + 40, 20, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
	};
	SDL_Rect Rect = { 0, 0 , gameSettings::winSetting.winW, gameSettings::winSetting.header };
	std::string text1 = "";
	std::string text2 = "";
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
		int W = gameSettings::winSetting.winW / 3;
		this->blitTxt(text1.c_str(), { gameSettings::winSetting.winW - 2 * W + W / 2, 30, 100, 40 });
		this->blitTxt(text2.c_str(), { gameSettings::winSetting.winW - W + W / 2, 30, 100, 40 });
	}

	void blitLeftWeight(int lWeight) {
		text1 = std::to_string((lWeight));
		this->blit();
	}
	void blitRightWeight(int RWeight) {
		text2 = std::to_string((RWeight));
		this->blit();
	}
	void resetH()
	{
		this->text1 = "";
		this->text2 = "";
		blit();
	}
};

