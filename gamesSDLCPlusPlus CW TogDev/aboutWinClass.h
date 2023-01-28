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

	std::string text = "Линейка — простое интерактивное приложение для использования его в развлекательных целях.Данное приложение представляет собой инструмент"
		"для вычисления длинны объектов, заданные пользователем.Из - за большой погрешности измерений и не возможности объективной оценки условий проведения расчетов длин.\n"
		"“Линейка” является приложением для использования исключительно в развлекательных целях.\n"
		"Автор: Марченко В.А.";

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

