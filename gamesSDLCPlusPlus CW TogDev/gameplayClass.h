#pragma once

#include "baseGameClass.h"

#include"menuClass.h"
#include"aboutWinClass.h"
#include"settingWinClass.h"
#include"headerClass.h"
#include<sstream>

#include "scalesWinClass.h"
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
	float rightPosY = 420;
	float leftPosY = 420;
	SDL_Surface* CH = nullptr;
	float speed = 0;

	int menuFlag = gameSettings::menuSetting.close;
	scalesWinClass* sections[2];
	midSectionClass* midSection = nullptr;

public:

	void transmitImg(SDL_Surface* img, int m_x, int m_y) {
		SDL_Rect mr = { m_x - img->w / 2, m_y - img->h / 2, img->w, img->h };
		SDL_BlitScaled(img, NULL, gameSettings::winSetting.surface, &mr);
	}

	void setSpeedAndYPos()
	{
		this->leftPosY += speed;
		this->rightPosY -= speed;
		if (this->sections[0]->tempGetL() > this->sections[1]->tempGetL())
		{
			if (this->leftPosY <= 620)
			{
				speed += 0.4;
			}
			else
			{
				speed = 0;
				this->leftPosY = 620;
				this->rightPosY = 220;
			}

		}
		else if (this->sections[0]->tempGetL() < this->sections[1]->tempGetL())
		{
			if (this->rightPosY <= 620)
			{
				speed -= 0.4;
			}
			else
			{
				speed = 0;
				this->leftPosY = 220;
				this->rightPosY = 620;
			}
		}
		else
		{
			if (this->leftPosY > this->rightPosY)
			{
				speed -= 0.4;
			}
			else
			{
				speed += 0.4;
			}
			if (this->leftPosY < 430 && this->leftPosY > 410)
			{
				speed *= 0.9;
			}
			if (this->leftPosY < 422 && this->leftPosY >= 418 && fabs(speed) < 1)
			{
				speed = 0;
				leftPosY = 420;
				rightPosY = 420;
			}
		}
	}

	int start() {

		srand(time(0));
		gameSettings::objectsFC.objParam[3].lenth = short(rand() % 50);

		if (this->base.initModuls())
		{
			SDL_Event event;
			fontClass font; imageClass img;
			menuClass menu = menuClass(img.loadOneImg("./image/menu/mainBg.png"),img.loadOneImg("./image/menu/btnBg.png"), font.getFont());
			aboutWinClass aboutWin = aboutWinClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), font.getFont());
			settingWinClass settingsWin= settingWinClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), font.getFont());

			this->CH = img.loadOneImg("./image/objects/CH.png");

			headerClass header = headerClass(img.loadOneImg("./image/menu/mainBg.png"), img.loadOneImg("./image/menu/btnBg.png"), font.getFont());

			this->sections[0] = new scalesWinClass(img.loadOneImg("./image/menu/mainBg.png"), font.getFont(),
				{0,gameSettings::winSetting.header, gameSettings::winSetting.block, 
				gameSettings::winSetting.winH-gameSettings::winSetting.header});
			this->sections[1] = new scalesWinClass(img.loadOneImg("./image/menu/mainBg.png"), font.getFont(),
				{gameSettings::winSetting.block + gameSettings::winSetting.midSection,gameSettings::winSetting.header, gameSettings::winSetting.block, 
				gameSettings::winSetting.winH-gameSettings::winSetting.header});
			this->midSection = new midSectionClass(img.loadOneImg("./image/menu/mainBg.png"), font.getFont(), { 
				gameSettings::winSetting.block,
				gameSettings::winSetting.header,
				gameSettings::winSetting.midSection,
				gameSettings::winSetting.winH - gameSettings::winSetting.header 
				});

			
			
			sections[0]->blit();
			sections[1]->blit();
			this->midSection->blit();
			header.blit();
			this->sections[0]->blitCH(1, leftPosY, CH);
			this->sections[1]->blitCH(2, rightPosY, CH);
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
						else if (header.checkButtonClick(this->cursor_X, this->cursor_Y) == header.reset)
						{
							this-> pictChose = false;
							this->pictRight = 0;
							this->pictLeft = 0;
							sections[0]->resetWin();
							sections[0]->blit();
							sections[1]->resetWin();
							sections[1]->blit();
							leftPosY = 420;
							rightPosY = 420;
							speed = 0;
							this->sections[0]->blitCH(1, leftPosY, CH);
							this->sections[1]->blitCH(2, rightPosY, CH);
							this->midSection->blit();
							header.resetH();
							SDL_UpdateWindowSurface(gameSettings::winSetting.win);
						}
					}
					else if (this->menuFlag == gameSettings::menuSetting.mainMenuWindow)
					{

						switch (menu.checkButtonClick(this->cursor_X, this->cursor_Y)) {
						case menu.btnsEnum::playBtn:
							std::cout << "Menu::buttons::play\n";
							///start game or other =PASS=
							this->menuFlag = gameSettings::menuSetting.close;
							header.blit();
							sections[0]->blit();
							sections[1]->blit();
							this->midSection->blit();

							SDL_UpdateWindowSurface(gameSettings::winSetting.win);
							break;	
						case menu.btnsEnum::setting:
							std::cout << "Menu::buttons::statistic\n";
							this->menuFlag = gameSettings::menuSetting.setting;
							rightPosY = 420;

							settingsWin.blit();
							break;
						case menu.btnsEnum::aboutGame:
							this->menuFlag = gameSettings::menuSetting.about;
							aboutWin.blit();
							std::cout << "Menu::buttons::about\n";
							break;
						case menu.btnsEnum::quitBtn:
							std::cout << "Menu::buttons::quit\n";
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
				}
				if (this->menuFlag == gameSettings::menuSetting.setting)
				{

					std::stringstream sars;
					SDL_StartTextInput();
					std::string text = "¬ведите массу гири в килограммах (ремендуетс€ в пределах 100):";
					SDL_Rect tempRect = { gameSettings::winSetting.winW / 2 - 350, 200, };
					SDL_Surface* tempSurf = TTF_RenderText_Solid(font.getFont(), text.c_str(), { 0,0,0 });
					SDL_BlitSurface(tempSurf, NULL, gameSettings::winSetting.surface, &tempRect);
					SDL_UpdateWindowSurface(gameSettings::winSetting.win);
					SDL_FreeSurface(tempSurf);
					SDL_UpdateWindowSurface(gameSettings::winSetting.win);

					text = "";
					while (true)
					{
						SDL_PollEvent(&event);
						if (event.type == SDL_TEXTINPUT)
						{
							text += event.text.text;
							tempRect = { gameSettings::winSetting.winW / 2 - 70, 250, };
							SDL_Surface* tempSurf = TTF_RenderText_Solid(font.getFont(), text.c_str(), { 0,0,0 });
							SDL_BlitSurface(tempSurf, NULL, gameSettings::winSetting.surface, &tempRect);
							SDL_UpdateWindowSurface(gameSettings::winSetting.win);
							SDL_FreeSurface(tempSurf);
							SDL_UpdateWindowSurface(gameSettings::winSetting.win);
						}
						else if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN)
						{
							SDL_GetMouseState(&this->cursor_X, &this->cursor_Y);
							if (settingsWin.checkButtonClick(this->cursor_X, this->cursor_Y) == settingsWin.cancel)
							{
								std::cout << "aboutWin::buttons::cancel\n";
								this->menuFlag = gameSettings::menuSetting.mainMenuWindow;
								menu.blit();
								break;
							}
							if (settingsWin.checkButtonClick(this->cursor_X, this->cursor_Y) == settingsWin.apply)
							{
								std::cout << "aboutWin::buttons::cancel\n";
								int size = std::stoi(text);
								gameSettings::objectsFC.objParam[3].lenth = size;
								std::cout << size << std::endl;
								text = "";
								this->menuFlag = gameSettings::menuSetting.mainMenuWindow;
								menu.blit();
								break;
							}
						}
					}
					SDL_StopTextInput();
				}


				if (this->menuFlag == gameSettings::menuSetting.close)
				{
					sections[0]->blit();
					sections[1]->blit();
					this->midSection->blit();
					
					if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN) {
						SDL_GetMouseState(&this->cursor_X, &this->cursor_Y);
						if (!this->pictChose)
						{
							std::cout << "yeahboy\n";
							this->tempImg = this->midSection->choseImgByClick(this->cursor_X, this->cursor_Y);
							if (this->tempImg)
							{
								this->pictChose = true;
							}
						}else std::cout << "nayboy\n";
					}
					else if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEMOTION)
					{
						if (this->pictChose)
						{
							this->cursor_X = event.motion.x;
							this->cursor_Y = event.motion.y;
							
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
								if (this->cursor_X < gameSettings::winSetting.block)
								{
									this->sections[0]->setPictureToCompaire(this->tempImg, this->midSection->getImgLenth());
									this->pictLeft++;
									this->tempImg = nullptr;
									SDL_UpdateWindowSurface(gameSettings::winSetting.win);
									this->pictChose = false;
								}
								else if (this->cursor_X > gameSettings::winSetting.block + gameSettings::winSetting.midSection)
								{
									this->sections[1]->setPictureToCompaire(this->tempImg, this->midSection->getImgLenth());
									this->pictRight++;
									this->tempImg = nullptr;
									SDL_UpdateWindowSurface(gameSettings::winSetting.win);
									this->pictChose = false;
								}
							}
						}
					}
					this->sections[0]->blitCH(1, leftPosY, CH);
					this->sections[1]->blitCH(2, rightPosY, CH);
					if (this->pictLeft || this->pictRight )
					{
						setSpeedAndYPos();
						if (this->pictLeft)
						{
							//std::cout << this->sections[0]->tempGetL() << " lLeft\n";
							this->sections[0]->blitPicts(1, leftPosY);
							header.blitLeftWeight(this->sections[0]->tempGetL());
						}
						if (this->pictRight)
						{
							//std::cout << this->sections[1]->tempGetL() << " lRight\n";
							this->sections[1]->blitPicts(2, rightPosY);
							header.blitRightWeight(this->sections[1]->tempGetL());
						}
						/*if (this->pictLeft + this->pictRight == 2)
						{
							header.blitCompairResult(this->sections[0]->tempGetL(), this->sections[1]->tempGetL());
							SDL_UpdateWindowSurface(gameSettings::winSetting.win);
						}*/
						SDL_UpdateWindowSurface(gameSettings::winSetting.win);

					}
				}
				
				



				SDL_Delay(1000 / 60);
			}


		}


		return 0;
	}
};

