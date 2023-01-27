#pragma once

#include"imageClass.h"

class fieldClass : public imageClass
{

private:

    int camI = 0;
    int camJ = 0;
    int cellsInLineScreen = 0;
    int cellsInColumScreen = 0;
    int cellSize = 0;
    std::vector<std::vector<cellV>>fieldV;

public:
	fieldClass(){
        this->loadImages(gameSettings::fieldSetting.fieldImagesPathVector);
        this->cellSize = gameSettings::fieldSetting.cellSize;
        this->cellsInLineScreen = gameSettings::winSetting.winW / this->cellSize;
        this->cellsInColumScreen = gameSettings::winSetting.winH / this->cellSize;
	}
	~fieldClass()
	{
        this->fieldV.clear();
	}

    void generateFieldMatrix() {
       fieldV.resize(gameSettings::fieldSetting.fieldSizeH);
        for (int k = 0; k < fieldV.size(); k++)
        {
            fieldV[k].resize(gameSettings::fieldSetting.fieldSizeW);
        }


        for (int i = 0; i < fieldV.size(); i++)
        {   
            for (int j = 0; j < fieldV[i].size(); j++)
            {
                this->fieldV[i][j].i = i;
                this->fieldV[i][j].i = j;
            }
        }
    }


    void blitField(point headPos, int headDirection) {
        switch (headDirection)
        {



        case _directions::UP:
            if (headPos.p1 > 5)
            {
                this->camI--;
            }
            break;
        case _directions::DOWN:

            if (headPos.p1 < this->fieldV.size() - this->cellsInColumScreen)
            {
                this->camI++;
            }

            break;

        default:
            break;
        }
        
        int y = gameSettings::winSetting.header;
        for (int i = this->camI; i < this->cellsInColumScreen + this->camI; i++)
        {
            int x = 0;
            for (int j = this->camJ; j < this->cellsInLineScreen + this->camJ; j++)
            {
                SDL_Rect mr = { x, y,this->cellSize,this->cellSize };
                SDL_BlitScaled(imageVector[gameSettings::fieldSetting.empty], NULL, gameSettings::winSetting.surface, &mr);
                x += this->cellSize;
            }
            y += cellSize;
        }
    }


    std::vector<std::vector<cellV>>& getFieldVector() { return this->fieldV; }


};

