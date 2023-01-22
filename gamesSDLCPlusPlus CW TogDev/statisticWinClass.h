#pragma once

#include"interfaceObjects.h"

class statisticWinClass : public interfaceObjects
{
public:const short cancelBtn = 0;
private:
	short positionStartX = gameSettings::winSetting.winW / 2 - gameSettings::menuSetting.btnW / 2;
	short positionStartY = 50;
	std::vector< btnsStruct>btnsV = {
		{"ОТМЕНА", {positionStartX, positionStartY * 9, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
	};
	SDL_Rect menuRect = { 0, 0 , gameSettings::winSetting.winW, gameSettings::winSetting.winH };

	std::string text = "";

public:
	statisticWinClass(SDL_Surface* bgImg, SDL_Surface* btnImg, TTF_Font* font) :
		interfaceObjects(bgImg, btnImg, font) {
		this->btns = this->btnsV;
		this->objRect = this->menuRect;
	}
	~statisticWinClass()
	{
		this->text.clear();
		this->btnsV.clear();
	}

	void loadStatistic(/*std::vector<std::vector<int>> stat*/) {
		this->text = "Статистика:\n"
			"Легкий уровень:\n"
			"ЧТо-То 0000      и еще что то 0000\n"
			"Средний уровень:\n"
			"ЧТо-То 0000      и еще что то 0000\n"
			"Сложный уровень:\n"
			"ЧТо-То 0000      и еще что то 0000\n"

			"ВОТЬ\n";
	}

	void blit() {
		this->blitWithTxt(this->text.c_str());
		this->blitBtns();
		SDL_UpdateWindowSurface(gameSettings::winSetting.win);
	}

};

