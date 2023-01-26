#pragma once

#include "baseGameClass.h"

#include"menuClass.h"
#include"settingWinClass.h"
#include"aboutWinClass.h"
#include"statisticWinClass.h"
#include"headerClass.h"

#include "imageClass.h"
#include"fontClass.h"


class gameplayClass : public baseGameClass
{
private:
	//baseGameClass base;
	
	SDL_Surface* imgBgMenu = nullptr;
	SDL_Surface* btnsImg = nullptr;
	SDL_Surface* settingsSwitchImg = nullptr;
	TTF_Font* font = nullptr;

	int cursor_X = 0, cursor_Y = 0;

	bool game = true;
	bool tempMenuStop = false;

	int menuFlag = gameSettings::menuSetting.close;


public:

	gameplayClass() {
		fontClass font; imageClass img;
		this->initModuls();
		this->imgBgMenu = img.loadOneImg("./image/menu/mainBg.png");
		this->btnsImg = img.loadOneImg("./image/menu/btnBg.png");
		this->btnsImg = img.loadOneImg("./image/menu/btnBg.png");

		this->font = font.getFont();

	}
	~gameplayClass()
	{
		SDL_FreeSurface(gameSettings::winSetting.surface);
		SDL_DestroyWindow(gameSettings::winSetting.win);

		IMG_Quit();
		SDL_Quit();
	}

	int mainLoop() {
		SDL_Event event;

		menuClass menu = menuClass(this->imgBgMenu, this->btnsImg, this->font);
		settingWinClass settingWin = settingWinClass(this->imgBgMenu, this->btnsImg, this->btnsImg, this->font);
		aboutWinClass aboutWin = aboutWinClass(this->imgBgMenu, this->btnsImg, this->font);
		statisticWinClass statisticWin = statisticWinClass(this->imgBgMenu, this->btnsImg, this->font);

		headerClass header = headerClass(this->imgBgMenu, this->btnsImg, this->font);



		header.blit();
		SDL_UpdateWindowSurface(gameSettings::winSetting.win);


		while (SDL_PollEvent(&event) || this->game)
		{
			if (event.type == SDL_QUIT)
			{
				this->game = false;
				return 0;
			}
			else if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&this->cursor_X, &this->cursor_Y);

				if (this->menuFlag == gameSettings::menuSetting.close)
				{
					if (header.checkButtonClick(this->cursor_X, this->cursor_Y) == header.openMenu)
					{
					menu.blit();
					this->menuFlag = gameSettings::menuSetting.mainMenuWindow;
					}
				}
				else if (this->menuFlag == gameSettings::menuSetting.mainMenuWindow)
				{

					switch (menu.checkButtonClick(this->cursor_X, this->cursor_Y)) {
					case menu.btnsEnum::playBtn:
						this->menuFlag = gameSettings::menuSetting.about;
						std::cout << "Menu::buttons::play\n";
						///start game or other =PASS=
						this->menuFlag = gameSettings::menuSetting.close;
						break;
					case menu.btnsEnum::loadBtn:
						std::cout << "Menu::buttons::load\n";
						///=PASS=
						break;
					case menu.btnsEnum::settingBtn:
						std::cout << "Menu::buttons::settings\n";
						this->menuFlag = gameSettings::menuSetting.setting;
						settingWin.blit();
						break;
					case menu.btnsEnum::statistic:
						std::cout << "Menu::buttons::statistic\n";
						this->menuFlag = gameSettings::menuSetting.statistic;
						statisticWin.loadStatistic();
						statisticWin.blit();
						break;
					case menu.btnsEnum::aboutGame:
						this->menuFlag = gameSettings::menuSetting.about;
						aboutWin.blit();
						std::cout << "Menu::buttons::about\n";
						break;
					case menu.btnsEnum::quitBtn:
						std::cout << "Menu::buttons::quit\n";
						header.blit();
					

						///temp
						//this->menuFlag = gameSettings::menuSetting.close;
						return 0;
						break;
						
					default:
						break;
					}
				}
				else if (this->menuFlag == gameSettings::menuSetting.setting)
				{
					switch (settingWin.checkButtonClick(this->cursor_X, this->cursor_Y))
					{
					case settingWin.btnsEnum::easy:
						std::cout << "setting::buttons::easy\n";
						settingWin.changeHardness(settingWin.btnsEnum::easy);
						break;
					case settingWin.btnsEnum::normal:
						std::cout << "setting::buttons::normal\n";
						settingWin.changeHardness(settingWin.btnsEnum::normal);
						break;
					case settingWin.btnsEnum::hard:
						std::cout << "setting::buttons::hard\n";
						settingWin.changeHardness(settingWin.btnsEnum::hard);
						break;
					case settingWin.btnsEnum::apply:
						std::cout << "setting::buttons::apply\n";
						this->menuFlag = gameSettings::menuSetting.close;
						settingWin.applyHardness();
						///blitGameFieldAndOther =PASS=
						break;
					case settingWin.btnsEnum::cancel:
						std::cout << "setting::buttons::cancel\n";
						settingWin.resetHardness();
						this->menuFlag = gameSettings::menuSetting.mainMenuWindow;
						menu.blit();

						break;


					default:
						break;
					}
				}
				else if (this->menuFlag == gameSettings::menuSetting.about)
				{
					if (aboutWin.checkButtonClick(this->cursor_X, this->cursor_Y) == aboutWin.cancelBtn)
					{
						std::cout << "aboutWin::buttons::cancel\n";
						this->menuFlag = gameSettings::menuSetting.mainMenuWindow;
						menu.blit();
					}
				}
				else if (this->menuFlag == gameSettings::menuSetting.statistic)
				{
					if (statisticWin.checkButtonClick(this->cursor_X, this->cursor_Y) == statisticWin.cancelBtn)
					{
						std::cout << "statisticWin::buttons::cancel\n";
						this->menuFlag = gameSettings::menuSetting.mainMenuWindow;
						menu.blit();
					}
				}
			}



			if (this->menuFlag == gameSettings::menuSetting.close)
			{
				header.blit();
				SDL_UpdateWindowSurface(gameSettings::winSetting.win);



			}

			SDL_Delay(1000 / 60);
		}


		


		return 0;
	}
};

