#pragma once

#include "baseGameClass.h"

#include"saveClass.h"
#include"menuClass.h"
#include"settingWinClass.h"
#include"aboutWinClass.h"
#include"headerClass.h"


#include "imageClass.h"
#include"fontClass.h"

#include"fieldClass.h"


class gameplayClass
{
private:
	baseGameClass base;
	fieldClass field;
	saveClass save;

	TTF_Font* fontT;
	SDL_Surface* bgMenuImg = nullptr;
	SDL_Surface* bgBtnImg = nullptr;

	
	int cursor_X = 0, cursor_Y = 0;

	bool game = true;
	bool pause = true;

	int menuFlag = gameSettings::menuSetting.close;

	short int gLoop = 0;
public:

	~gameplayClass()
	{
		SDL_FreeSurface(this->bgBtnImg);
		SDL_FreeSurface(this->bgMenuImg);
		//TTF_CloseFont(this->fontT);	////????
	}

	void restart()
	{
		this->field = fieldClass();
	}
	short int numberOfLivingCellsAround(short int i, short int j, fieldClass field)
	{

		short int counter = 0;
		if (i > 0)
		{
			if (field.getfieldV()[i - 1][j].live == true) { counter++; }
			if (j > 0) { if (field.getfieldV()[i - 1][j - 1].live == true) { counter++; } }
			if (j < gameSettings::winSetting.winW / field.getCellSize() - 1) { if (field.getfieldV()[i - 1][j + 1].live == true) { counter++; } }
		}
		if (i < gameSettings::winSetting.winW / field.getCellSize() - 1)
		{
			if (field.getfieldV()[i + 1][j].live == true) { counter++; }
			if (j > 0) { if (field.getfieldV()[i + 1][j - 1].live == true) { counter++; } }
			if (j < gameSettings::winSetting.winW / field.getCellSize() - 1) { if (field.getfieldV()[i + 1][j + 1].live == true) { counter++; } }
		}
		if (j > 0) { if (field.getfieldV()[i][j - 1].live == true) { counter++; } }
		if (j < gameSettings::winSetting.winW / field.getCellSize() - 1) { if (field.getfieldV()[i][j + 1].live == true) { counter++; } }

		return counter;
	}

	void oneTickAction()
	{
		std::vector<std::vector<cell>> fieldV = field.getfieldV();
		//std::cout << "start1" << std::endl;
		for (int i = 0; i < fieldV.size(); i++)
		{
			for (int j = 0; j < fieldV[i].size(); j++)
			{
				short int numberOfLivingNeighbors = numberOfLivingCellsAround(i, j, this->field);
				if (fieldV[i][j].live == true)
				{
					if (numberOfLivingNeighbors < 2 || numberOfLivingNeighbors > 3)
					{
						fieldV[i][j].live = false;
					}
				}
				else
				{
					if (numberOfLivingNeighbors == 3)
					{
						fieldV[i][j].live = true;
					}
				}
			}
		}
		//std::cout << "end1" << std::endl;
		field.setfieldV(fieldV);
	}

	int start() {

		if (this->base.initModuls())
		{
			SDL_Event event;
			fontClass font; imageClass img;

			this->fontT = font.getFont();
			this->bgMenuImg = img.loadOneImg("./image/menu/mainBg.png");
			this->bgBtnImg = img.loadOneImg("./image/menu/mainBg.png");

			menuClass menu = menuClass(this->bgMenuImg, this->bgBtnImg, this->fontT);
			settingWinClass settingWin = settingWinClass(this->bgMenuImg, this->bgBtnImg, img.loadOneImg("./image/menu/switchTemp.png"), this->fontT);
			aboutWinClass aboutWin = aboutWinClass(this->bgMenuImg, this->bgBtnImg, this->fontT);
			headerClass header = headerClass(this->bgMenuImg, this->bgBtnImg, this->fontT);


			header.blit();
			field.blitField();

			//tempBg.blit();
			SDL_UpdateWindowSurface(gameSettings::winSetting.win);


			while (SDL_PollEvent(&event) || this->game)
			{
				if (this->menuFlag == gameSettings::menuSetting.close)
				{
					if (!this->pause)
					{
				
						this->oneTickAction();
						field.blitField();
						SDL_UpdateWindowSurface(gameSettings::winSetting.win);

					}

				}
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
						if (this->cursor_Y > gameSettings::winSetting.header)
						{
							if (this->pause)
							{
								point pxPosition = { this->cursor_X, this->cursor_Y };
								field.playerChanges(pxPosition);
								field.blitField();
								SDL_UpdateWindowSurface(gameSettings::winSetting.win);
							};
						}
						else
						{
							switch (header.checkButtonClick(this->cursor_X, this->cursor_Y))
							{
								case header.btnsEnum::openMenu:
									menu.blit();
									this->menuFlag = gameSettings::menuSetting.mainMenuWindow;
									this->pause = true;
									break;
								case header.btnsEnum::play:
									this->pause = false;
									break;
								case header.btnsEnum::pause:
									this->pause = true;
									break;

							default:
								break;
							}
						}
					}
					else if (this->menuFlag == gameSettings::menuSetting.mainMenuWindow)
					{

						switch (menu.checkButtonClick(this->cursor_X, this->cursor_Y)) {
						case menu.btnsEnum::playBtn:
							std::cout << "Menu::buttons::play\n";
							header.blit();
							field.blitField();
							SDL_UpdateWindowSurface(gameSettings::winSetting.win);
							this->menuFlag = gameSettings::menuSetting.close;
							break;
						case menu.btnsEnum::loadBtn:
							std::cout << "Menu::buttons::load\n";
							field.setfieldV(save.getSave());
							field.blitField();
							break;
						case menu.btnsEnum::settingBtn:
							std::cout << "Menu::buttons::settings\n";
							this->menuFlag = gameSettings::menuSetting.setting;
							settingWin.blit();
							break;
						case menu.btnsEnum::save:
							std::cout << "Menu::buttons::save\n";
							save.setSave(field.getfieldV(), gameSettings::fieldSetting.hardness);
							break;
						case menu.btnsEnum::aboutGame:
							this->menuFlag = gameSettings::menuSetting.about;
							aboutWin.blit();
							std::cout << "Menu::buttons::about\n";
							break;
						case menu.btnsEnum::quitBtn:
							std::cout << "Menu::buttons::quit\n";
							header.blit();
							//tempBg.blit();

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
							restart();
							header.blit();
							field.blitField();
							SDL_UpdateWindowSurface(gameSettings::winSetting.win);
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
				}




				SDL_Delay(1000 / 60);
			}


		}


		return 0;
	}
};

