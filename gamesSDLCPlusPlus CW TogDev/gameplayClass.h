#pragma once

#include "baseGameClass.h"

#include"menuClass.h"
#include"settingWinClass.h"
#include"aboutWinClass.h"
#include"statisticWinClass.h"
#include"headerClass.h"

#include"tempBgAllClass.h"

#include "imageClass.h"
#include"fontClass.h"

#include"fieldClass.h"


class gameplayClass
{
private:
	baseGameClass base;
	fieldClass field;
	
	int cursor_X = 0, cursor_Y = 0;

	bool game = true;
	bool pause = true;

	int menuFlag = gameSettings::menuSetting.close;

	short int gLoop = 0;
public:
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
			menuClass menu = menuClass(img.loadOneImg("./image/menu/mainBg.png"),img.loadOneImg("./image/menu/btnBg.png"), font.getFont());
			settingWinClass settingWin = settingWinClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), img.loadOneImg("./image/menu/switchTemp.png"), font.getFont());
			aboutWinClass aboutWin = aboutWinClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), font.getFont());
			statisticWinClass statisticWin = statisticWinClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), font.getFont());

			headerClass header = headerClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), font.getFont());
			tempBgAllClass tempBg = tempBgAllClass(img.loadOneImg("./image/menu/mainBg.png"));


			header.blit();
			field.blitField();

			//tempBg.blit();
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
							this->menuFlag = gameSettings::menuSetting.load;
							///=PASS=
							break;
						case menu.btnsEnum::settingBtn:
							std::cout << "Menu::buttons::settings\n";
							this->menuFlag = gameSettings::menuSetting.setting;
							settingWin.blit();
							break;
						case menu.btnsEnum::save:
							std::cout << "Menu::buttons::save\n";
							this->menuFlag = gameSettings::menuSetting.save;
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
					else if (this->menuFlag == gameSettings::menuSetting.load)
					{
						///=PASS=

						///TEMP
						this->menuFlag = gameSettings::menuSetting.mainMenuWindow;
						menu.blit();
						///TEMP
					}
					else if (this->menuFlag == gameSettings::menuSetting.save)
					{
						///=PASS=

						///TEMP
						this->menuFlag = gameSettings::menuSetting.mainMenuWindow;
						menu.blit();
						///TEMP
					}
				}



				if (this->menuFlag == gameSettings::menuSetting.close)
				{
					if (!this->pause)
					{
				
						this->oneTickAction();
						//gLoop = 0;
						field.blitField();
						SDL_UpdateWindowSurface(gameSettings::winSetting.win);

					}

				}

				SDL_Delay(1000 / 60);
			}


		}


		return 0;
	}
};

