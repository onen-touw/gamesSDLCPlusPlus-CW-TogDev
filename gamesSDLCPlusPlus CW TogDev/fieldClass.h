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

    void generateFieldMatrix() {
       /* fieldV.resize(this->fH);
        for (int k = 0; k < this->fH; k++)
        {
            fieldV[k].resize(this->fW);
        }

        short y = gameSettings::winSetting.headerHeight;
        for (int i = 0; i < fieldV.size(); i++)
        {
            short x = 0;
            for (int j = 0; j < fieldV[0].size(); j++)
            {
                fieldV[i][j].pxPosition = { x, y };
                x += gameSettings::winSetting.cellSize;
            }
            y += gameSettings::winSetting.cellSize;
        }*/
    }


};

