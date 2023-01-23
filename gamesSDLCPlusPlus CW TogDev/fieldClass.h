#pragma once

#include"settings.h"
#include"imageClass.h"

class fieldClass : public imageClass
{
private:
	std::vector<std::vector<cell>> fieldV;
	short int cellSize = 0;
public:
	fieldClass()
	{
		this->loadImages(gameSettings::fieldSetting.fieldImagesPathVector);
		this->logOut();
		if (gameSettings::fieldSetting.hardness == gameSettings::fieldSetting.hardnessEn::easy)
		{
			this->cellSize = gameSettings::winSetting.winW / gameSettings::fieldSetting.easyModeNumberOfCells;
			for (int i = 0; i < gameSettings::fieldSetting.easyModeNumberOfCells; i++)
			{
				std::vector<cell> temp;
				for (int j = 0; j < gameSettings::fieldSetting.easyModeNumberOfCells; j++)
				{
					point pos = { i * this->cellSize, j * this->cellSize + gameSettings::winSetting.header };
					temp.push_back({ pos, false });
				}
				this->fieldV.push_back(temp);
				temp.clear();
			}
		}
		else if (gameSettings::fieldSetting.hardness == gameSettings::fieldSetting.hardnessEn::normal)
		{
			this->cellSize = gameSettings::winSetting.winW / gameSettings::fieldSetting.normalModeNumberOfCells;
			for (int i = 0; i < gameSettings::fieldSetting.normalModeNumberOfCells; i++)
			{
				std::vector<cell> temp;
				for (int j = 0; j < gameSettings::fieldSetting.normalModeNumberOfCells; j++)
				{
					point pos = { i * this->cellSize, j * this->cellSize + gameSettings::winSetting.header  };
					temp.push_back({ pos, false });
				}
				this->fieldV.push_back(temp);
				temp.clear();
			}
		}
		else
		{
			this->cellSize = gameSettings::winSetting.winW / gameSettings::fieldSetting.hardModeNumberOfCells;
			for (int i = 0; i < gameSettings::fieldSetting.hardModeNumberOfCells; i++)
			{
				std::vector<cell> temp;
				for (int j = 0; j < gameSettings::fieldSetting.hardModeNumberOfCells; j++)
				{
					point pos = { i * this->cellSize, j * this->cellSize + gameSettings::winSetting.header };
					temp.push_back({ pos, false });
				}
				this->fieldV.push_back(temp);
				temp.clear();
			}
		}
	}
	~fieldClass()
	{
		this->fieldV.clear();
	}

	std::vector<std::vector<cell>>& getfieldV()
	{
		return this->fieldV;
	}

	void setfieldV(std::vector<std::vector<cell>> fieldV)
	{
		this->fieldV = fieldV;
	}

	short int getCellSize()
	{
		return this->cellSize;
	}

	point searchCellPosition(point pxPosition)
	{
		return { (short int)(pxPosition.p1 / cellSize), (short int)((pxPosition.p2 - 70) / cellSize) };
	}

	void playerChanges(point pxPosition)
	{
		point cellPosition = searchCellPosition(pxPosition);
		if (fieldV[cellPosition.p1][cellPosition.p2].live == true)
		{
			fieldV[cellPosition.p1][cellPosition.p2].live = false;
		}
		else
		{
			fieldV[cellPosition.p1][cellPosition.p2].live = true;
		}
	}

	void blit(int imageName, int i, int j) {
		SDL_Rect mr = { fieldV[i][j].pxPosition.p1, fieldV[i][j].pxPosition.p2, cellSize, cellSize };
		SDL_BlitScaled(this->imageVector[imageName], NULL, gameSettings::winSetting.surface, &mr);
	}

	void blitField()
	{
		for (int i = 0; i < fieldV.size(); i++)
		{
			for (int j = 0; j < fieldV[i].size(); j++)
			{
				if (gameSettings::fieldSetting.hardness == gameSettings::fieldSetting.hardnessEn::easy)
				{
					if (fieldV[i][j].live == false)
					{
						this->blit(gameSettings::fieldSetting.images::cellDeadEasy, i, j);
					}
					else
					{
						this->blit(gameSettings::fieldSetting.images::cellLiveEasy, i, j);
					}
				}
				else if (gameSettings::fieldSetting.hardness == gameSettings::fieldSetting.hardnessEn::normal)
				{
					if (fieldV[i][j].live == false)
					{
						this->blit(gameSettings::fieldSetting.images::cellDeadNormal, i, j);
					}
					else
					{
						this->blit(gameSettings::fieldSetting.images::cellLiveNormal, i, j);
					}
				}
				else
				{
					if (fieldV[i][j].live == false)
					{
						this->blit(gameSettings::fieldSetting.images::cellDeadHard, i, j);
					}
					else
					{
						this->blit(gameSettings::fieldSetting.images::cellLiveHard, i, j);
					}
				}
			}
		}
	}
};

