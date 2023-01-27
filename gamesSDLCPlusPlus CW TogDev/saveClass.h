#pragma once
#include"settings.h"
#include<fstream>
class saveClass
{
private:
	std::string path = "save/data.txt";
	short int statSize = 5;
	std::vector<std::pair<std::string, std::pair<short int, short int>>> statisticEasy;
	std::vector<std::pair<std::string, std::pair<short int, short int>>> statisticNormal;
	std::vector<std::pair<std::string, std::pair<short int, short int>>> statisticHard;
public:
	saveClass()
	{
		loadStatFromFile();
	}
	~saveClass()
	{
		setStatToFile();
		statisticEasy.clear();
		statisticHard.clear();
		statisticNormal.clear();
	}

	void updateStat(std::string name, short int lCount, short int kCount, short int hardness)
	{
		short int newPosition = -1;
		if (hardness == gameSettings::fieldSetting.hardnessEnum::easy)
		{
			for (short int i = 0; i < statisticEasy.size(); i++)
			{
				if (lCount > statisticEasy[i].second.first)
				{
					newPosition = i;
					break;
				}
				else if (lCount == statisticEasy[i].second.first)
				{
					if (kCount > statisticEasy[i].second.second)
					{
						newPosition = i;
						break;
					}
					else if (kCount == statisticEasy[i].second.second)
					{
						if (i + 1 < statisticEasy.size())
						{
							newPosition = i + 1;
						}
						break;
					}
				}
			}
			if (newPosition != -1)
			{
				for (int i = statisticEasy.size() - 1; i >= 0; i--)
				{
					if (newPosition < i)
					{
						statisticEasy[i] = statisticEasy[i - 1];
					}
					else if (newPosition == i)
					{
						statisticEasy[i] = { name, {lCount, kCount} };
						break;
					}
				}
			}
		}
		else if (hardness == gameSettings::fieldSetting.hardnessEnum::normal)
		{
			short int newPosition = -1;
			for (short int i = 0; i < statisticNormal.size(); i++)
			{
				if (lCount > statisticNormal[i].second.first)
				{
					newPosition = i;
					break;
				}
				else if (lCount == statisticNormal[i].second.first)
				{
					if (kCount > statisticNormal[i].second.second)
					{
						newPosition = i;
						break;
					}
					else if (kCount == statisticNormal[i].second.second)
					{
						if (i + 1 < statisticNormal.size())
						{
							newPosition = i + 1;
						}
						break;
					}
				}
			}
			if (newPosition != -1)
			{
				for (int i = statisticNormal.size() - 1; i >= 0; i--)
				{
					if (newPosition < i)
					{
						statisticNormal[i] = statisticNormal[i - 1];
					}
					else if (newPosition == i)
					{
						statisticNormal[i] = { name, {lCount, kCount} };
						break;
					}
				}
			}
		}
		else
		{
			short int newPosition = -1;
			for (short int i = 0; i < statisticHard.size(); i++)
			{
				if (lCount > statisticHard[i].second.first)
				{
					newPosition = i;
					break;
				}
				else if (lCount == statisticHard[i].second.first)
				{
					if (kCount > statisticHard[i].second.second)
					{
						newPosition = i;
						break;
					}
					else if (kCount == statisticHard[i].second.second)
					{
						if (i + 1 < statisticHard.size())
						{
							newPosition = i + 1;
						}
						break;
					}
				}
			}
			if (newPosition != -1)
			{
				for (int i = statisticHard.size() - 1; i >= 0; i--)
				{
					if (newPosition < i)
					{
						statisticHard[i] = statisticHard[i - 1];
					}
					else if (newPosition == i)
					{
						statisticHard[i] = { name, {lCount, kCount} };
						break;
					}
				}
			}
		}
	}

	std::vector<std::pair<std::string, std::pair<short int, short int>>> getStat(short int hardness)
	{
		if (hardness == gameSettings::fieldSetting.hardnessEnum::easy)
		{
			return statisticEasy;
		}
		else if (hardness == gameSettings::fieldSetting.hardnessEnum::normal)
		{
			return statisticNormal;
		}
		else
		{
			return statisticHard;
		}
	}

	void loadStatFromFile()
	{
		std::ifstream file(path);
		if (file.is_open())
		{
			short int count;
			file >> count;
			for (int i = 0; i < count; i++)
			{
				std::string playerName;
				file >> playerName;
				short int levelCount, botsKillCount;
				file >> levelCount >> botsKillCount;
				statisticEasy.push_back({ playerName, { levelCount, botsKillCount } });
			}
			file >> count;
			for (int i = 0; i < count; i++)
			{
				std::string playerName;
				file >> playerName;
				short int levelCount, botsKillCount;
				file >> levelCount >> botsKillCount;
				statisticNormal.push_back({ playerName, { levelCount, botsKillCount } });
			}
			file >> count;
			for (int i = 0; i < count; i++)
			{
				std::string playerName;
				file >> playerName;
				short int levelCount, botsKillCount;
				file >> levelCount >> botsKillCount;
				statisticHard.push_back({ playerName, { levelCount, botsKillCount } });
			}
			file.close();
		}
	}

	void setStatToFile()
	{
		std::ofstream file(path, std::ios::out);
		file << statisticEasy.size();
		for (int i = 0; i < statisticEasy.size(); i++)
		{
			file << statisticEasy[i].first << " " << statisticEasy[i].second.first << " " << statisticEasy[i].second.second << std::endl;
		}
		file << statisticNormal.size();
		for (int i = 0; i < statisticNormal.size(); i++)
		{
			file << statisticNormal[i].first << " " << statisticNormal[i].second.first << " " << statisticNormal[i].second.second << std::endl;
		}
		file << statisticHard.size();
		for (int i = 0; i < statisticHard.size(); i++)
		{
			file << statisticHard[i].first << " " << statisticHard[i].second.first << " " << statisticHard[i].second.second << std::endl;
		}
		file.close();
	}
};

