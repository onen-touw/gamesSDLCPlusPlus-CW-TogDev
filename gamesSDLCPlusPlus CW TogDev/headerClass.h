#pragma once

#include"interfaceObjects.h"

class headerClass : public interfaceObjects
{

public:const short openMenu = 0, reset = 1;
private:
	

	std::vector< btnsStruct>btnsV = {
		{"����", {20, 20, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
		{"��������", {gameSettings::menuSetting.btnW + 40, 20, gameSettings::menuSetting.btnW, gameSettings::menuSetting.btnH}},
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

	void blitCompairResult(int lLenth, int rLenth) {
		std::string text = "";
		if (lLenth > rLenth)
		{
			text = "� ����� ������� " + std::to_string((lLenth / (float)rLenth)) + " ������";
		}
		else if (lLenth < rLenth)
		{
			text = "� ������ ������� " + std::to_string((rLenth / (float)lLenth)) + " �����";
		}
		else
		{
			text = "������� �����";
		}
		this->blit();
		this->blitTxt(text.c_str(), { gameSettings::winSetting.winW /2, 30, 100, 40 });
	}
};

