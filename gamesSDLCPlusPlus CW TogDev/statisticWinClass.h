#pragma once

#include"interfaceObjects.h"
#include<string>

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
	short int easyKillCount = 0;
	short int normalKillCount = 0;
	short int hardKillCount = 0;

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

	void setStat(short int killCount, short int hardness)
	{
		if (hardness == gameSettings::fieldSetting.hardnessEnum::easy)
		{
			this->easyKillCount = killCount;
		}
		else if (hardness == gameSettings::fieldSetting.hardnessEnum::normal)
		{
			this->normalKillCount = killCount;
		}
		else if (hardness == gameSettings::fieldSetting.hardnessEnum::hard)
		{
			this->hardKillCount = killCount;
		}
	}

	void updateStatistic() {
		this->text = "Статистика:\n"
			"Легкий уровень:\n"
			"кол-во пройденных уровней" + std::to_string(easyKillCount) + "\n"
			"Средний уровень:\n"
			"кол-во пройденных уровней" + std::to_string(normalKillCount) + "\n"
			"Сложный уровень:\n"
			"кол-во пройденных уровней" + std::to_string(hardKillCount) + "\n"

			"ВОТЬ\n";
	}

	void blit() {
		this->blitWithTxt(this->text.c_str());
		this->blitBtns();
		SDL_UpdateWindowSurface(gameSettings::winSetting.win);
	}

};

