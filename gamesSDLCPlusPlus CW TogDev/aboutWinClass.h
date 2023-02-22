#pragma once

#include"interfaceObjects.h"

class aboutWinClass : public interfaceObjects
{
public:const short cancelBtn = 0;
private:
	short positionStartX = gameSettings::winSetting.winW / 2 - gameSettings::menuSetting.btnW / 2;
	short positionStartY = 50;
	std::vector< btnsStruct>btnsV = {
		{"ОТМЕНА", {positionStartX, positionStartY * 9, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
	};
	SDL_Rect menuRect = { 0, 0 , gameSettings::winSetting.winW, gameSettings::winSetting.winH };

	std::string text = "Чтобы найти массу предмета, сделайте следующее:\n"
		"1. Перетащите предмет неизвестной массы на правую чашу весов, зажав правую кнопку мыши\n"
		"2. Начните перетягивать гири с известной массой на левую чашу весов, зажав правую кнопку"
		"мыши, пока не найдете равновесие обеих чаш\n"
		"3. Нажмите кнопку \"сбросить\", чтобы начать сначала\n"
		"Автор Абрусевич В.А.";

public:
	aboutWinClass(SDL_Surface* bgImg, SDL_Surface* btnImg, TTF_Font* font) :
		interfaceObjects(bgImg, btnImg, font) {
		this->btns = this->btnsV;
		this->objRect = this->menuRect;
	}
	~aboutWinClass()
	{
		this->btnsV.clear();
		this->text.clear();

	}
	void blit() {
		this->blitWithTxt(this->text.c_str());
		this->blitBtns();
		SDL_UpdateWindowSurface(gameSettings::winSetting.win);
	}

};

