#pragma once

#include "baseGameClass.h"
#include"menuClass.h"
#include "imageClass.h"
#include"fontClass.h"


class gameplayClass
{
private:
	baseGameClass base;
	
	int cursor_X = 0, cursor_Y = 0;

	bool game = true;
	bool menuFlag = true;
public:

	int start() {

		if (this->base.initModuls())
		{
			SDL_Event event;
			fontClass font; imageClass img;
			menuClass menu = menuClass(img.loadOneImg("./image/menu/mainBg.png"),img.loadOneImg("./image/menu/btnBg.png"), font.getFont());

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
					if (this->menuFlag)
					{

						switch (menu.checkButtonClick(this->cursor_X, this->cursor_Y)) {
						case menu.btnsEnum::playBtn:
							std::cout << "Menu::buttons::play\n";
							break;
						case menu.btnsEnum::loadBtn:
							std::cout << "Menu::buttons::load\n";
							break;
						case menu.btnsEnum::settingBtn:
							std::cout << "Menu::buttons::settings\n";
							break;
						case menu.btnsEnum::aboutGame:
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
				}



				if (this->menuFlag)
				{
					menu.blit();

				}



				SDL_Delay(1000 / 60);
			}


		}


		return 0;
	}
};

