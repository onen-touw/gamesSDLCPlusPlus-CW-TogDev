#pragma once

#include "baseGameClass.h"

#include"menuClass.h"
#include"settingWinClass.h"
#include"aboutWinClass.h"
#include"statisticWinClass.h"
#include"headerClass.h"
#include"endGameWinClass.h"

#include"characterClass.h"
#include"botsClass.h"
#include"saveClass.h"


#include"fieldClass.h"
#include "imageClass.h"
#include"fontClass.h"


class gameplayClass : public baseGameClass
{
private:
	//baseGameClass base;
	
	characterClass* character = nullptr;
	fieldClass* field = nullptr;
	botsClass* bots = nullptr;
	saveClass* save = nullptr;

	int cursor_X = 0, cursor_Y = 0;

	bool game = true;
	bool tempMenuStop = false;
	short int gloop = 0;
	short int botsNumber = 5;
	short int botsKillCounter = 0;
	short int levelCounter = 0;

	int menuFlag = gameSettings::menuSetting.close;

public:
	gameplayClass() {
		this->character = new characterClass();
		this->field = new fieldClass();
		this->bots = new botsClass();
		this->save = new saveClass();
	}
	~gameplayClass()
	{
		delete this->character;
		delete this->field;
		delete this->bots;
		delete this->save;
	}

	void restart()
	{
		delete this->character;
		delete this->field;
		delete this->bots;
		this->character = new characterClass();
		this->field = new fieldClass();
		this->bots = new botsClass();
		this->game = true;
		this->tempMenuStop = false;
		this->gloop = 0;

		this->menuFlag = gameSettings::menuSetting.close;


		this->field->generateFieldMatrix();
		this->field->randowWalls();
		this->field->DEBUG();
		this->field->blitField();

		for (int i = 0; i < this->botsNumber; i++)
		{
			this->bots->spawnBot(this->field->getPositionForBot());
		}
		this->bots->blitBots(this->field->getFiledVectorLink());
		this->character->characterBlit();
	}

	int mainLoop() 
	{
		if (this->initModuls())
		{
			SDL_Event event;
			fontClass font; imageClass img; 
			menuClass menu = menuClass(img.loadOneImg("./image/menu/mainBg.png"),img.loadOneImg("./image/menu/btnBg.png"), font.getFont());
			settingWinClass settingWin = settingWinClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), img.loadOneImg("./image/menu/switchTemp.png"), font.getFont());
			aboutWinClass aboutWin = aboutWinClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), font.getFont());
			statisticWinClass statisticWin = statisticWinClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), font.getFont());
			headerClass header = headerClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), font.getFont());
			endGameWinClass egw = endGameWinClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), font.getFont());


			this->field->generateFieldMatrix();
			this->field->randowWalls();
			this->field->DEBUG();
			this->field->blitField();

			for (int i = 0; i < this->botsNumber; i++)
			{
				this->bots->spawnBot(this->field->getPositionForBot());
			}
			this->bots->blitBots(this->field->getFiledVectorLink());
			this->character->characterBlit();
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
							std::cout << "Menu::buttons::play\n";
							///start game or other =PASS=
							restart();
							header.blit();
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
							statisticWin.setStat(this->save->getStat(gameSettings::fieldSetting.easy), gameSettings::fieldSetting.easy);
							statisticWin.setStat(this->save->getStat(gameSettings::fieldSetting.normal), gameSettings::fieldSetting.normal);
							statisticWin.setStat(this->save->getStat(gameSettings::fieldSetting.hard), gameSettings::fieldSetting.hard);
							statisticWin.updateStatistic();
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
							botsKillCounter = 0;
							botsNumber = 5;
							restart();
							header.blit();
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
					else if (this->menuFlag == gameSettings::menuSetting.gameEndWin)
					{
						if (egw.checkButtonClick(this->cursor_X, this->cursor_Y) == egw.cancel) {
							///restartWithoutSaveUser
						}
						else if(egw.checkButtonClick(this->cursor_X, this->cursor_Y) == egw.saveAndRestart)
						{
							///restartWithSaveUser
							this->restart();
						}
							//		egw.blit();
							//	SDL_UpdateWindowSurface(gameSettings::winSetting.win);
					}
				}

				if (this->menuFlag == gameSettings::menuSetting.close)
				{

					if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
					{
						this->field->blitOneCell(this->character->getPosition());
						this->character->transmit(_direction::down, this->field->getFiledVectorLink());
						//this->bots->updateBots(this->field->getFiledVectorLink(), this->character->getPosition());
					}
					else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
					{
						std::cout << "keydown::RIGHT\n";
						this->field->blitOneCell(this->character->getPosition());
						this->character->transmit(_direction::right, this->field->getFiledVectorLink());
						//this->bots->updateBots(this->field->getFiledVectorLink(), this->character->getPosition());
					}
					else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
					{
						this->field->blitOneCell(this->character->getPosition());
						this->character->transmit(_direction::up, this->field->getFiledVectorLink());
						//this->bots->updateBots(this->field->getFiledVectorLink(), this->character->getPosition());
					}
					else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
					{

						this->field->blitOneCell(this->character->getPosition());
						this->character->transmit(_direction::left, this->field->getFiledVectorLink());
						//this->bots->updateBots(this->field->getFiledVectorLink(), this->character->getPosition());
					}
					else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
					{
						this->character->setBomb();
					}
					
					if (gloop >= 30/(gameSettings::fieldSetting.hardness + 1))
					{
						this->bots->updateBots(this->field->getFiledVectorLink(), this->character->getPosition());
						gloop = 0;
					}
					gloop++;
					this->field->blitField();
					if (this->character->bombChecking(this->field->getFiledVectorLink(), this->field) == 1)
					{
						botsKillCounter += this->bots->killBots(this->character->getBombPos());
						if (this->character->characterDeadBomb())
						{
							this->save->updateStat("hui", levelCounter, botsKillCounter, gameSettings::fieldSetting.hardness);
							botsKillCounter = 0;
							levelCounter = 0;
							botsNumber = 5;
							restart();
							header.blit();
						}
						else if (this->bots->getBotsSize() == 0)
						{
							levelCounter ++;
							this->botsNumber += 3;
							restart();
							header.blit();
						}
					}
					if (this->bots->killCharacter(this->character->getPosition()))
					{
						this->save->updateStat("yakov_koshkin", levelCounter, botsKillCounter, gameSettings::fieldSetting.hardness);
						botsKillCounter = 0;
						levelCounter = 0;
						botsNumber = 5;
						restart();
						header.blit();
					}
					this->bots->blitBots(this->field->getFiledVectorLink());
					this->character->characterBlit();
					SDL_UpdateWindowSurface(gameSettings::winSetting.win);
				}
				SDL_Delay(1000 / 60);
			}


		}
		else
		{
			return 1;	///Error initialization
		}

		return 0;
	}
};

