#pragma once

#include "baseGameClass.h"

#include"menuClass.h"
#include"aboutWinClass.h"
#include"statisticWinClass.h"
#include"headerClass.h"

#include "rulerWinClass.h"
#include "midSectionClass.h"

#include "imageClass.h"
#include"fontClass.h"


class gameplayClass
{
private:
	baseGameClass base;
	
	SDL_Surface* tempImg = nullptr;

	int cursor_X = 0, cursor_Y = 0;

	bool game = true;
	bool pictChose = false;
	int pictRight = 0;
	int pictLeft = 0;

	int menuFlag = gameSettings::menuSetting.close;
	rulerWinClass* sections[2];
	midSectionClass* midSection = nullptr;

public:

	void transmitImg(SDL_Surface* img, int m_x, int m_y) {
		SDL_Rect mr = { m_x - img->w / 2, m_y - img->h / 2, img->w, img->h };
		SDL_BlitScaled(img, NULL, gameSettings::winSetting.surface, &mr);
		//SDL_UpdateWindowSurface(gameSettings::winSetting.win);
	}

	int start() {

		if (this->base.initModuls())
		{
			SDL_Event event;
			fontClass font; imageClass img;
			menuClass menu = menuClass(img.loadOneImg("./image/menu/mainBg.png"),img.loadOneImg("./image/menu/btnBg.png"), font.getFont());
			aboutWinClass aboutWin = aboutWinClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), font.getFont());
			statisticWinClass statisticWin = statisticWinClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), font.getFont());

			headerClass header = headerClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), font.getFont());

			this->sections[0] = new rulerWinClass(img.loadOneImg("./image/menu/mainBg.png"), font.getFont(),
				{0,gameSettings::winSetting.header, gameSettings::winSetting.block, 
				gameSettings::winSetting.winH-gameSettings::winSetting.header});
			this->sections[1] = new rulerWinClass(img.loadOneImg("./image/menu/mainBg.png"), font.getFont(),
				{gameSettings::winSetting.block + gameSettings::winSetting.midSection,gameSettings::winSetting.header, gameSettings::winSetting.block, 
				gameSettings::winSetting.winH-gameSettings::winSetting.header});
			this->midSection = new midSectionClass(img.loadOneImg("./image/menu/mainBg.png"), font.getFont(), { 
				gameSettings::winSetting.block,
				gameSettings::winSetting.header,
				gameSettings::winSetting.midSection,
				gameSettings::winSetting.winH - gameSettings::winSetting.header 
				});

			for (int i = 0; i < 2; i++)
			{
				sections[i]->blit();
			}
			this->midSection->blit();
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
					for (int i = 0; i < 2; i++)
					{
						sections[i]->blit();
					}
					this->midSection->blit();
					
					if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN) {
						SDL_GetMouseState(&this->cursor_X, &this->cursor_Y);
						if (!this->pictChose && this->pictLeft+this->pictRight<2)
						{
							this->tempImg = this->midSection->choseImgByClick(this->cursor_X, this->cursor_Y);
							if (this->tempImg)
							{
								this->pictChose = true;
							}
						}
					}
					else if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEMOTION)
					{
						if (this->pictChose)
						{
							this->cursor_X = event.motion.x;
							this->cursor_Y = event.motion.y;
							std::cout << "yeahboy\n";
							this->transmitImg(this->tempImg, this->cursor_X, this->cursor_Y);
						}
						SDL_UpdateWindowSurface(gameSettings::winSetting.win);						
					}
					else if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP)
					{
						SDL_GetMouseState(&this->cursor_X, &this->cursor_Y);
						if (this->pictChose) {
							if (this->cursor_Y > gameSettings::winSetting.header)
							{
								if (this->cursor_X < gameSettings::winSetting.block && this->pictLeft<1)
								{
									this->sections[0]->setPictureToCompaire(this->tempImg);
									this->pictLeft++;
									this->tempImg = nullptr;
									SDL_UpdateWindowSurface(gameSettings::winSetting.win);
									this->pictChose = false;
								}
								else if (this->cursor_X > gameSettings::winSetting.block + gameSettings::winSetting.midSection && this->pictRight<1)
								{
									this->sections[1]->setPictureToCompaire(this->tempImg);
									this->pictRight++;
									this->tempImg = nullptr;
									SDL_UpdateWindowSurface(gameSettings::winSetting.win);
									this->pictChose = false;
								}
							}
						}
					}
					
				}
				
				



				SDL_Delay(1000 / 60);
			}


		}


		return 0;
	}
};

