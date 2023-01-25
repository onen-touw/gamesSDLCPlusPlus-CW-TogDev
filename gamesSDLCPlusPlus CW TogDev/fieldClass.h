#pragma once

#include"interfaceObjects.h"
#include"imageClass.h"


class fieldClass : public interfaceObjects , public imageClass
{
private:

	std::vector<std::vector<cell>>fieldV;
    int fH = 0, fW = 0, cellSize = 0,
        wallEndueance = 0;
  
   
    
    std::vector<imagePath>fieldImagesPathVector = {
        {"./image/fieldImages/hardWall.png", Object::Empty},
        //{"./image/fieldImages/wall.png", Object::Wall},
        {"./image/fieldImages/wall.png", Object::Wall},
     /*   {"./image/fieldImages/brokenWall.png", Object::BrockenWall},
        {"./image/fieldImages/weekWall.png", Object::WeekWall},*/
    };



public:

	~fieldClass()
	{
		this->fieldV.clear();
        this->fieldImagesPathVector.clear();
	}

	fieldClass(){
        this->cellSize = gameSettings::winSetting.cellSize;
        this->fH = gameSettings::winSetting.countOfCells;
        this->fW = this->fH;        ///square field
        this->wallEndueance = gameSettings::fieldSetting.objEndurance;

        this->loadImages(this->fieldImagesPathVector);

        
    }

	std::vector<std::vector<cell>>&getFiledVectorLink() { return this->fieldV; }

    void generateFieldMatrix() {
        fieldV.resize(this->fH);
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
                fieldV[i][j].pxPosition = {x, y};
                x += gameSettings::winSetting.cellSize;
            }
            y += gameSettings::winSetting.cellSize;
        }
    }

    bool checkAround(int i, int j) {
        if (this->fieldV[i-1ll][j].objType == 0
            && this->fieldV[i-1ll][j].objType == 0
            && this->fieldV[i][j-1ll].objType == 0 
            && this->fieldV[i][j+1ll].objType == 0)
        {
            return true;
        }
        return false;
    }

    void randowWalls() {
        for (int i = 0; i < this->fieldV[0].size(); i++) ///отчищаем первую строку поля
        {
            this->fieldV[0][i].objType = Object::Empty;
        }

        srand(time(0));
        for (int i = 2; i < this->fieldV.size(); i += 2)
        {
            int position = rand()% 3;
            int theSetLenth = rand() % (6 - 3) + 3;

            while (position + theSetLenth < fieldV[0].size() - 1)
            {

                for (int k = position; k < theSetLenth + position; k++)
                {
                    this->fieldV[i][k].objType = Object::Empty;
                }

                int t = rand() % (theSetLenth-1) + position;
                this->fieldV[i - 1ll][t].objType = Object::Empty;

                if (position + 1ll + theSetLenth < this->fieldV[0].size())
                {
                    position = ++position + theSetLenth;

                }
                else break;
                int theSetLenth = rand() % (6 - 3) + 3;
            }
            if (position + 1ll < this->fieldV[0].size())
            {
               /* position;*/
                int l = 0;
                for (int k = position; k < this->fieldV[0].size(); k++)
                {
                    std::cout << "===== " << i << " " << k << "\n";
                    this->fieldV[i][k].objType = Object::Empty;
                    l++;
                }
                int t = rand() % (l-1) + position;
                this->fieldV[i - 1ll][t].objType = Object::Empty;
                std::cout << t << "   dfdjfkd << " << i << " \n";
            }
        }

    }

    void DEBUG() {
        
        for (int i = 0; i < this->fH; i++)
        {
            for (int j = 0; j < this->fW; j++)
            {

                if (this->fieldV[i][j].objType == Object::Empty)
                {
                    std::cout << "0 ";
                }
               /* else if (this->fieldV[i][j].objType == Object::Wall)
                {
                    std::cout << "+ ";
                }*/
                else
                {
                    std::cout << "= ";
                }
            }
            std::cout << "\n";
        }

    }

    void blitOneCell(point p) {
        if (this->fieldV[p.p1][p.p2].objType == Object::Empty)
        {
            this->_blit(this->imageVector[Object::Empty], { this->fieldV[p.p1][p.p2].pxPosition.p1,
                        this->fieldV[p.p1][p.p2].pxPosition.p2, this->cellSize, this->cellSize, });
        }
        else if (this->fieldV[p.p1][p.p2].objType == Object::Wall)
        {
            this->_blit(this->imageVector[Object::Wall], { this->fieldV[p.p1][p.p2].pxPosition.p1,
                            this->fieldV[p.p1][p.p2].pxPosition.p2, this->cellSize, this->cellSize, });
        }
        else/*(this->fieldV[p.p1][p.p2].objType == Object::BrockenWall)*/
        {
            this->_blit(this->imageVector[Object::BrockenWall], { this->fieldV[p.p1][p.p2].pxPosition.p1,
                          this->fieldV[p.p1][p.p2].pxPosition.p2, this->cellSize, this->cellSize, });
        }
    }

    void blitField() {
        for (int i = 0; i < this->fH; i++)
        {
            for (int j = 0; j < this->fW; j++)
            {
                switch (this->fieldV[i][j].objType)
                {
                case Object::Empty:
                    this->_blit(this->imageVector[Object::Empty], { this->fieldV[i][j].pxPosition.p1,
                        this->fieldV[i][j].pxPosition.p2, this->cellSize, this->cellSize, });
                    break;
                case Object::Wall:
                    if (this->fieldV[i][j].objLive == this->wallEndueance)
                    {
                        this->_blit(this->imageVector[Object::Wall], { this->fieldV[i][j].pxPosition.p1,
                            this->fieldV[i][j].pxPosition.p2, this->cellSize, this->cellSize, });
                    }
                    else if(this->fieldV[i][j].objLive < this->wallEndueance && this->fieldV[i][j].objLive> 0)
                    {
                        this->_blit(this->imageVector[Object::WeekWall], { this->fieldV[i][j].pxPosition.p1,
                           this->fieldV[i][j].pxPosition.p2, this->cellSize, this->cellSize, });
                    }
                    else
                    {
                        this->_blit(this->imageVector[Object::BrockenWall], { this->fieldV[i][j].pxPosition.p1,
                          this->fieldV[i][j].pxPosition.p2, this->cellSize, this->cellSize, });
                    }
                    break;

                default:
                    break;
                }
                
            }
        }
        SDL_UpdateWindowSurface(gameSettings::winSetting.win);
    }
};

