#pragma once

#include"imageClass.h"

class fieldClass : public imageClass
{

private:

	SDL_Surface* cellImg = nullptr;
	SDL_Surface* borderImg = nullptr;


public:
	fieldClass(){
		this->cellImg = this->loadOneImg("./image/field/emptyCell.png");
		this->borderImg = this->loadOneImg("./image/field/borderWall.png");

	}
	~fieldClass()
	{
		SDL_FreeSurface(this->cellImg);
		SDL_FreeSurface(this->borderImg);
	}


};

