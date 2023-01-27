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
	std::vector<std::pair<std::string, std::pair<short int, short int>>> statisticEasy;
	std::vector<std::pair<std::string, std::pair<short int, short int>>> statisticNormal;
	std::vector<std::pair<std::string, std::pair<short int, short int>>> statisticHard;

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

	void setStat(std::vector<std::pair<std::string, std::pair<short int, short int>>> statistic, short int hardness)
	{
		if (hardness == gameSettings::fieldSetting.hardnessEnum::easy)
		{
			this->statisticEasy = statistic;
		}
		else if (hardness == gameSettings::fieldSetting.hardnessEnum::normal)
		{
			this->statisticNormal = statistic;
		}
		else if (hardness == gameSettings::fieldSetting.hardnessEnum::hard)
		{
			this->statisticHard = statistic;
		}
	}

	void updateStatistic() {
		this->text = "Статистика:\n";
		text += "Легкий уровень сложности:\n";
		for (int i = 0; i < statisticEasy.size(); i++)
		{
			text += std::to_string(i + 1) + " " + statisticEasy[i].first + " levels: " + std::to_string(statisticEasy[i].second.first) + ", kills: " + std::to_string(statisticEasy[i].second.second) + "\n";
		}
		text += "Средний уровень сложности:\n";
		for (int i = 0; i < statisticNormal.size(); i++)
		{
			text += std::to_string(i + 1) + " " + statisticNormal[i].first + " levels: " + std::to_string(statisticNormal[i].second.first) + ", kills: " + std::to_string(statisticNormal[i].second.second) + "\n";
		}
		text += "Высокий уровень сложности:\n";
		for (int i = 0; i < statisticHard.size(); i++)
		{
			text += std::to_string(i + 1) + " " + statisticHard[i].first + " levels: " + std::to_string(statisticHard[i].second.first) + ", kills: " + std::to_string(statisticHard[i].second.second) + "\n";
		}
	}

	void blit() {
		this->blitWithTxt(this->text.c_str());
		this->blitBtns();
		SDL_UpdateWindowSurface(gameSettings::winSetting.win);
	}

};

