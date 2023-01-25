#pragma once

#include"imageClass.h"
#include"interfaceObjects.h"
#include"veaponClass.h"
#include"fieldClass.h"

class characterClass : public imageClass, public interfaceObjects 
{
private:

	int lastDirection = _direction::down;
	std::vector<SDL_Surface*>characterImg;

	SDL_Surface* fireImg = nullptr;
	SDL_Surface* bombImg = nullptr;

	short characterImgSize = 0;
	int charactI = 0;
	int charactJ = 0;
	SDL_Rect chRect = { 0,0,0,0 };

	veaponClass* bomb = nullptr;
	bool caboom = false;

public:
	characterClass() {
		this->characterImg.resize(_direction::TOTAL);
		this->characterImg[_direction::down] = this->loadOneImg("./image/character/down.png");
		this->characterImg[_direction::up] = this->loadOneImg("./image/character/up.png");
		this->characterImg[_direction::left] = this->loadOneImg("./image/character/left.png");
		this->characterImg[_direction::right] = this->loadOneImg("./image/character/right.png");
		this->characterImgSize = gameSettings::winSetting.cellSize;
		this->chRect = { this->charactI,this->charactJ + gameSettings::winSetting.headerHeight, this->characterImgSize,this->characterImgSize };

		this->bombImg = this->loadOneImg("./image/character/bomb.png");
		this->fireImg = this->loadOneImg("./image/character/fire.png");
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
					this->lastDirection = _direction::up;
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
					this->lastDirection = _direction::left;
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
					this->lastDirection = _direction::down;
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
					this->lastDirection = _direction::right;
					SDL_UpdateWindowSurface(gameSettings::winSetting.win);
				}
			}
			break;
		default:
			break;
		}
	}

	void setBomb() {
		std::cout << "bombSet::constructor\n";
		if (!this->caboom)
		{
			this->bomb = new veaponClass(this->fireImg, this->bombImg, this->charactI, this->charactJ);
			this->caboom = true;
			std::cout << "bombSet::constructor\n";
		}
	}
	void bombChecking(std::vector<std::vector<cell>>& V, fieldClass*F) {
		if (this->caboom)
		{
			if (this->bomb->CABOOOOOM(V)) {
				std::cout << "caboomEnd\n";
				delete this->bomb;
				F->blitField();
				this->caboom = false;
			}
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
