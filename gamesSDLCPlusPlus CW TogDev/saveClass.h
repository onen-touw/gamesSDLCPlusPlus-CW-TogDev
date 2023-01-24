#pragma once

#include"settings.h"
#include<fstream>

class saveClass
{
private:
	std::vector<std::vector<int>> save;
	short int hardness = 0;
	short int sizeW = 0;
	short int sizeH = 0;
public:
	saveClass()
	{
		hardness = gameSettings::fieldSetting.hardness;
		dataOpen();
	}
	~saveClass()
	{
		save.clear();
	}

	void setSave(std::vector<std::vector<cell>> field, short int hardness)
	{
		save.clear();
		for (int i = 0; i < field.size(); i++)
		{
			std::vector<int> tempSave;
			for (int j = 0; j < field[i].size(); j++)
			{
				if (field[i][j].live == true)
				{
					tempSave.push_back(1);
				}
				else
				{
					tempSave.push_back(0);
				}
			}
			this->save.push_back(tempSave);
			tempSave.clear();
		}
		this->sizeH = save.size();
		if (this->sizeH > 0)
		{
			this->sizeW = save[0].size();
		}
		this->hardness = hardness;
		dataSave();
	}

	std::vector<std::vector<cell>> getSave()
	{
		dataOpen();
		gameSettings::fieldSetting.hardness = this->hardness;
		std::vector<std::vector<cell>> field;
		short int cellSize = 0;
		if (this->hardness == gameSettings::fieldSetting.hardnessEn::easy)
		{
			cellSize = gameSettings::winSetting.winW / gameSettings::fieldSetting.easyModeNumberOfCells;
		}
		else if (this->hardness == gameSettings::fieldSetting.hardnessEn::normal)
		{
			cellSize = gameSettings::winSetting.winW / gameSettings::fieldSetting.normalModeNumberOfCells;
		}
		else
		{
			cellSize = gameSettings::winSetting.winW / gameSettings::fieldSetting.hardModeNumberOfCells;
		}
		for (int i = 0; i < this->save.size(); i++)
		{
			std::vector<cell> tempField;
			for (int j = 0; j < this->save[i].size(); j++)
			{
				point pxPosition = { i * cellSize, j * cellSize + gameSettings::winSetting.header };
				if (this->save[i][j] == 1)
				{
					tempField.push_back({ pxPosition, true });
				}
				else
				{
					tempField.push_back({ pxPosition, false });
				}
			}
			field.push_back(tempField);
			tempField.clear();
		}
		return field;
	}
	void dataOpen()
	{
		save.clear();
		std::ifstream file("save.txt");
		if (file.is_open())
		{
			file >> this->hardness;
			if (this->hardness == gameSettings::fieldSetting.hardnessEn::easy)
			{
				this->sizeH = gameSettings::fieldSetting.easyModeNumberOfCells;
				this->sizeW = gameSettings::fieldSetting.easyModeNumberOfCells;
			}
			else if (this->hardness == gameSettings::fieldSetting.hardnessEn::normal)
			{
				this->sizeH = gameSettings::fieldSetting.normalModeNumberOfCells;
				this->sizeW = gameSettings::fieldSetting.normalModeNumberOfCells;
			}
			else
			{
				this->sizeH = gameSettings::fieldSetting.hardModeNumberOfCells;
				this->sizeW = gameSettings::fieldSetting.hardModeNumberOfCells;
			}
			for (int i = 0; i < this->sizeH; i++)
			{
				std::vector<int> tempSave;
				for (int j = 0; j < this->sizeW; j++)
				{
					int cell;
					file >> cell;
					tempSave.push_back(cell);
				}
				this->save.push_back(tempSave);
				tempSave.clear();
			}
		}
	}

	void dataSave()
	{
		std::ofstream file("save.txt", std::ios::out);

		if (file.is_open())
		{
			file << hardness << "\n";
			for (int i = 0; i < sizeH; i++)
			{
				for (int j = 0; j < sizeW; j++)
				{
					file << save[i][j] << " ";
				}
				file << "\n";
			}
		}
		file.close();
	}
};



