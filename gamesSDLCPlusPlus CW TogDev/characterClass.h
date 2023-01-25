#pragma once

#include"imageClass.h"
#include"interfaceObjects.h"

class characterClass : public imageClass, public interfaceObjects 
{
private:

	int lastDirection = _direction::down;
	std::vector<SDL_Surface*>characterImg;
	short characterImgSize = 0;
	int charactI = 0;
	int charactJ = 0;
	SDL_Rect chRect = { 0,0,0,0 };

public:
	characterClass() {
		this->characterImg.resize(_direction::TOTAL);
		this->characterImg[_direction::down] = this->loadOneImg("./image/character/down.png");
		this->characterImg[_direction::up] = this->loadOneImg("./image/character/up.png");
		this->characterImg[_direction::left] = this->loadOneImg("./image/character/left.png");
		this->characterImg[_direction::right] = this->loadOneImg("./image/character/right.png");
		this->characterImgSize = gameSettings::winSetting.cellSize;
		this->chRect = { this->charactI,this->charactJ + gameSettings::winSetting.headerHeight, this->characterImgSize,this->characterImgSize };
	}



	void transmit(int direction, std::vector<std::vector<cell>>&V) {
		switch (direction)
		{
		case _direction::up:
			if (this->charactI- 1 >= 0 )
			{
				if (V[this->charactI - 1ll][this->charactJ].objType != Object::Wall)
				{
					std::cout << "transmit::UP\n";
					this->charactI--;
					this->chRect.y = this->charactI * this->characterImgSize + gameSettings::winSetting.headerHeight;
					this->_blit(characterImg[_direction::up], this->chRect);
					SDL_UpdateWindowSurface(gameSettings::winSetting.win);
				}
			}
			break;
		case _direction::left:
			if (this->charactJ - 1 >= 0)
			{
				if (V[this->charactI][this->charactJ - 1ll].objType != Object::Wall)
				{
					std::cout << "transmit::LEFT\n";
					this->charactJ--;
					this->chRect.x = this->charactJ * this->characterImgSize;
					this->_blit(characterImg[_direction::left], this->chRect);
					SDL_UpdateWindowSurface(gameSettings::winSetting.win);
				}
			}
			break;
		case _direction::down:
			if (this->charactI + 1ll < V.size())
			{
				if (V[this->charactI + 1ll][this->charactJ].objType != Object::Wall)
				{
					std::cout << "transmit::DOWN\n";
					this->charactI++;
					this->chRect.y = this->charactI * this->characterImgSize + gameSettings::winSetting.headerHeight;
					this->_blit(characterImg[_direction::down], this->chRect);
					SDL_UpdateWindowSurface(gameSettings::winSetting.win);
				}
			}
			break;
		case _direction::right:
			if (this->charactJ +1ll <V[0].size())
			{
				if (V[this->charactI][this->charactJ + 1ll].objType != Object::Wall)
				{
					std::cout << "transmit::RIGHT\n";

					this->charactJ++;
					this->chRect.x = this->charactJ * this->characterImgSize;
					this->_blit(characterImg[_direction::right], this->chRect);
					SDL_UpdateWindowSurface(gameSettings::winSetting.win);
				}
			}
			break;


		default:
			break;
		}
	}

	point getPosition() { return { this->charactI,this->charactJ }; }

	void characterBlit() {
		this->_blit(this->characterImg[this->lastDirection], this->chRect);
	}

	~characterClass()
	{
		this->characterImg.clear();
	}


};

