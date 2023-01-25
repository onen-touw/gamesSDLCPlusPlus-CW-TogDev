#pragma once

#include"imageClass.h"
#include"interfaceObjects.h"

class veaponClass : public imageClass , public interfaceObjects
{
private:
	int i = 0, j = 0;

	SDL_Surface* fireImg = nullptr;
	SDL_Surface* bombImg = nullptr;

	int bombWaiting = 2000;	/// 2c
	int fireTime = 1500;
	Uint32 setTime = 0;

	short int cabom = 0;

	SDL_Rect bombRect = { 0,0,0,0 };
	short cellSize = 0;
	short headerH = gameSettings::winSetting.headerHeight;

public:
	veaponClass(SDL_Surface* fireImg,SDL_Surface* bombImg, int i, int j) {
		this->fireImg = fireImg;
		this->bombImg = bombImg;
		this->setTime = SDL_GetTicks();
		this->i = i; this->j = j;
		this->cellSize = gameSettings::winSetting.cellSize;
		this->bombRect = { j* this->cellSize,i* this->cellSize+headerH, this->cellSize, this->cellSize };
	}
	~veaponClass()
	{
		/*SDL_FreeSurface(this->fireImg);
		SDL_FreeSurface(this->bombImg);*/
	}
	void setCabom()
	{
		this->cabom = 0;
	}
	point getBombPos(){return{i, j}; }
	short int CABOOOOOM(std::vector<std::vector<cell>>& V) {				/// return true when bomb is "died"
		if (this->cabom != 1) //TODO: еном добавить
		{
			if (SDL_GetTicks() - this->setTime >= this->bombWaiting)
			{
				this->cabom = 1;
				this->setTime = SDL_GetTicks();
				V[i][j].objType = Object::bomb;
			}
			SDL_BlitScaled(this->bombImg, NULL, gameSettings::winSetting.surface, &this->bombRect);
		}
		else
		{
			V[i][j].objType = Object::Empty;

			if (SDL_GetTicks() - this->setTime <= this->fireTime)
			{
				SDL_BlitScaled(this->fireImg, NULL, gameSettings::winSetting.surface, &this->bombRect);
				//this->_blit(this->fireImg, this->bombRect);
				if (this->i + 1ll < V.size())
				{ 
					if (V[this->i+1ll][this->j].objType != Object::Empty)
					{
						V[this->i + 1ll][this->j].objType = Object::Empty;
					}
					this->bombRect.y = (this->i+1) * this->cellSize + this->headerH;
					SDL_BlitScaled(this->fireImg, NULL, gameSettings::winSetting.surface, &this->bombRect);

					//this->_blit(this->fireImg, this->bombRect);
					this->bombRect.y = (this->i) * this->cellSize + this->headerH;
				}
				if (this->i - 1 >= 0)
				{
					if (V[this->i - 1ll][this->j].objType != Object::Empty)
					{
						V[this->i - 1ll][this->j].objType = Object::Empty;
					}
					this->bombRect.y = (this->i-1) * this->cellSize  + this->headerH;

					SDL_BlitScaled(this->fireImg, NULL, gameSettings::winSetting.surface, &this->bombRect);
					this->bombRect.y = (this->i) * this->cellSize + this->headerH;
				}
				if (this->j + 1ll < V[0].size())
				{
					if (V[this->i][this->j + 1ll].objType != Object::Empty)
					{
						V[this->i][this->j + 1ll].objType = Object::Empty;
					}
					this->bombRect.x = (this->j + 1) * this->cellSize;
					SDL_BlitScaled(this->fireImg, NULL, gameSettings::winSetting.surface, &this->bombRect);
					this->bombRect.x = (this->j) * this->cellSize;
				}
				if (this->j - 1 >= 0)
				{
					if (V[this->i][this->j - 1ll].objType != Object::Empty)
					{
						V[this->i][this->j - 1ll].objType = Object::Empty;
					}
					this->bombRect.x = (this->j - 1) * this->cellSize;
					SDL_BlitScaled(this->fireImg, NULL, gameSettings::winSetting.surface, &this->bombRect);
					this->bombRect.x = (this->j) * this->cellSize;
				}

				if (this->i + 2ll < V.size())
				{ 
					if (V[this->i+2ll][this->j].objType != Object::Empty)
					{
						V[this->i + 2ll][this->j].objType = Object::Empty;
					}
					this->bombRect.y = (this->i+2) * this->cellSize + this->headerH;
					SDL_BlitScaled(this->fireImg, NULL, gameSettings::winSetting.surface, &this->bombRect);

					//this->_blit(this->fireImg, this->bombRect);
					this->bombRect.y = (this->i) * this->cellSize + this->headerH;
				}
				if (this->i - 2 >= 0)
				{
					if (V[this->i - 2ll][this->j].objType != Object::Empty)
					{
						V[this->i - 2ll][this->j].objType = Object::Empty;
					}
					this->bombRect.y = (this->i-2) * this->cellSize  + this->headerH;

					SDL_BlitScaled(this->fireImg, NULL, gameSettings::winSetting.surface, &this->bombRect);
					this->bombRect.y = (this->i) * this->cellSize + this->headerH;
				}
				if (this->j + 2ll < V[0].size())
				{
					if (V[this->i][this->j + 2ll].objType != Object::Empty)
					{
						V[this->i][this->j + 2ll].objType = Object::Empty;
					}
					this->bombRect.x = (this->j + 2) * this->cellSize;
					SDL_BlitScaled(this->fireImg, NULL, gameSettings::winSetting.surface, &this->bombRect);
					this->bombRect.x = (this->j) * this->cellSize;
				}
				if (this->j - 2 >= 0)
				{
					if (V[this->i][this->j - 2ll].objType != Object::Empty)
					{
						V[this->i][this->j - 2ll].objType = Object::Empty;
					}
					this->bombRect.x = (this->j - 2) * this->cellSize;
					SDL_BlitScaled(this->fireImg, NULL, gameSettings::winSetting.surface, &this->bombRect);
					this->bombRect.x = (this->j) * this->cellSize;
				}
			}
			else
			{
				this->cabom = 2;
				return this->cabom;
			}
			SDL_UpdateWindowSurface(gameSettings::winSetting.win);
		}
		return this->cabom;
	}

};

