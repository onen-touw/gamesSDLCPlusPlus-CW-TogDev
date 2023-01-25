#pragma once
#include"botClass.h"

class botsClass:public botClass
{
private:
	std::vector<botClass> bots;
	std::vector<std::pair<point, short int>> way;
public:
	void killBots(point boomPosition)
	{
		for (int i = 0; i < bots.size(); i++)
		{
			if (bots[i].getPosition().p1 == boomPosition.p1 && bots[i].getPosition().p2 == boomPosition.p2)
			{
				bots.erase(bots.begin() + i);
				return;
			}
			else if (bots[i].getPosition().p1 == boomPosition.p1 + 1 && bots[i].getPosition().p2 == boomPosition.p2)
			{
				bots.erase(bots.begin() + i);
				return;
			}
			else if (bots[i].getPosition().p1 == boomPosition.p1 + 2 && bots[i].getPosition().p2 == boomPosition.p2)
			{
				bots.erase(bots.begin() + i);
				return;
			}
			else if (bots[i].getPosition().p1 == boomPosition.p1 - 1 && bots[i].getPosition().p2 == boomPosition.p2)
			{
				bots.erase(bots.begin() + i);
				return;
			}
			else if (bots[i].getPosition().p1 == boomPosition.p1 - 2 && bots[i].getPosition().p2 == boomPosition.p2)
			{
				bots.erase(bots.begin() + i);
				return;
			}
			else if (bots[i].getPosition().p1 == boomPosition.p1 && bots[i].getPosition().p2 == boomPosition.p2 + 1)
			{
				bots.erase(bots.begin() + i);
				return;
			}
			else if (bots[i].getPosition().p1 == boomPosition.p1 && bots[i].getPosition().p2 == boomPosition.p2 + 2)
			{
				bots.erase(bots.begin() + i);
				return;
			}
			else if (bots[i].getPosition().p1 == boomPosition.p1 && bots[i].getPosition().p2 == boomPosition.p2 - 1)
			{
				bots.erase(bots.begin() + i);
				return;
			}
			else if (bots[i].getPosition().p1 == boomPosition.p1 && bots[i].getPosition().p2 == boomPosition.p2 - 2)
			{
				bots.erase(bots.begin() + i);
				return;
			}
		}
	}
	void spawnBot(point botPosition)
	{
		botClass bot = botClass(botPosition);
		bots.push_back(bot);
	}
	void blitBots()
	{
		for (int i = 0; i < bots.size(); i++)
		{
			bots[i].blit();
		}
	}
	std::vector<point> checkCell(std::vector<std::vector<std::pair<cell, bool>>> field, point characterPosition)
	{
		std::vector<point> temp;
		if (characterPosition.p1 > 0)
		{
			if (field[characterPosition.p1 - 1][characterPosition.p2].second == false)
			{
				if (field[characterPosition.p1 - 1][characterPosition.p2].first.objType == Object::Empty || field[characterPosition.p1 - 1][characterPosition.p2].first.objType == Object::BrockenWall)
				{
					point pos = { characterPosition.p1 - 1, characterPosition.p2 };
					temp.push_back(pos);
				}
			}
		}
		if (characterPosition.p1 < field.size() - 1)
		{
			if (field[characterPosition.p1 + 1][characterPosition.p2].second == false)
			{
				if (field[characterPosition.p1 + 1][characterPosition.p2].first.objType == Object::Empty || field[characterPosition.p1 + 1][characterPosition.p2].first.objType == Object::BrockenWall)
				{
					point pos = { characterPosition.p1 + 1, characterPosition.p2 };
					temp.push_back(pos);
				}
			}
		}
		if (characterPosition.p2 > 0) 
		{
			if (field[characterPosition.p1][characterPosition.p2 - 1].second == false)
			{
				if (field[characterPosition.p1][characterPosition.p2 - 1].first.objType == Object::Empty || field[characterPosition.p1][characterPosition.p2 - 1].first.objType == Object::BrockenWall)
				{
					point pos = { characterPosition.p1, characterPosition.p2 - 1 };
					temp.push_back(pos);
				}
			}
		}
		if (characterPosition.p2 < field[0].size() - 1) 
		{
			if (field[characterPosition.p1][characterPosition.p2 + 1].second == false)
			{
				if (field[characterPosition.p1][characterPosition.p2 + 1].first.objType == Object::Empty || field[characterPosition.p1][characterPosition.p2 + 1].first.objType == Object::BrockenWall)
				{
					point pos = { characterPosition.p1, characterPosition.p2 + 1 };
					temp.push_back(pos);
				}
			}
		}
		return temp;
	}
	void findWay(std::vector<std::vector<cell>> fieldV, point characterPosition)
	{
		std::vector<std::vector<std::pair<cell, bool>>> field;
		for (int i = 0; i < fieldV.size(); i++)
		{
			std::vector<std::pair<cell, bool>> tempField;
			for (int j = 0; j < fieldV[i].size(); j++)
			{
				cell cell;
				point pos = { i, j };
				cell.pxPosition = pos;
				cell.objLive = fieldV[i][j].objLive;
				cell.objType = fieldV[i][j].objType;
				tempField.push_back({ cell, false });
			}
			field.push_back(tempField);
			tempField.clear();
		}
		way.clear();
		std::vector<std::pair<point, short int>> nextCheck;
		std::vector<std::pair<point, short int>> nowCheck;
		field[characterPosition.p1][characterPosition.p2].second = true;
		std::vector<point> temp = checkCell(field, characterPosition);
		for (int i = 0; i < temp.size(); i++)
		{
			nowCheck.push_back({ temp[i], this->way.size() });
			field[temp[i].p1][temp[i].p2].second = true;
			this->way.push_back({ temp[i], 0 });
		}
		temp.clear();
		while (nowCheck.size() != 0)
		{
			for (int i = 0; i < nowCheck.size(); i++)
			{
				std::vector<point> temp = checkCell(field, nowCheck[i].first);
				for (int j = 0; j < temp.size(); j++)
				{
					nextCheck.push_back({ temp[j], this->way.size() });
					field[temp[i].p1][temp[i].p2].second = true;
					this->way.push_back({ temp[j], nowCheck[i].second });
				}
				temp.clear();
			}
			nowCheck.clear();
			for (int i = 0; i < nextCheck.size(); i++)
			{
				nowCheck.push_back(nextCheck[i]);
			}
			nextCheck.clear();
		}
	}
	void setBotPosition(botClass bot, std::vector<std::vector<cell>> field)
	{
		bool find = false;
		bot.setOldPosition(bot.getPosition());
		for (int i = 0; i < this->way.size(); i++)
		{
			if (bot.getPosition().p1 == this->way[i].first.p1 && bot.getPosition().p2 == this->way[i].first.p2)
			{
				find = true;
				bot.setPosition(this->way[this->way[i].second].first);
			}
		}
		if (find == false)
		{
			if(bot.getPosition().p1 > 0)
			{
					if (field[bot.getPosition().p1 - 1][bot.getPosition().p2].objType == Object::Empty || field[bot.getPosition().p1 - 1][bot.getPosition().p2].objType == Object::BrockenWall)
					{
						point pos = { bot.getPosition().p1 - 1, bot.getPosition().p2 };
						bot.setPosition(pos);
						return;
					}
			}
			if (bot.getPosition().p1 < field.size() - 1)
			{
					if (field[bot.getPosition().p1 + 1][bot.getPosition().p2].objType == Object::Empty || field[bot.getPosition().p1 + 1][bot.getPosition().p2].objType == Object::BrockenWall)
					{
						point pos = { bot.getPosition().p1 + 1, bot.getPosition().p2 };
						bot.setPosition(pos);
						return;
					}
			}
			if (bot.getPosition().p2 > 0)
			{
					if (field[bot.getPosition().p1][bot.getPosition().p2 - 1].objType == Object::Empty || field[bot.getPosition().p1][bot.getPosition().p2 - 1].objType == Object::BrockenWall)
					{
						point pos = { bot.getPosition().p1, bot.getPosition().p2 - 1 };
						bot.setPosition(pos);
						return;
					}
			}
			if (bot.getPosition().p2 < field[0].size() - 1)
			{
					if (field[bot.getPosition().p1][bot.getPosition().p2 + 1].objType == Object::Empty || field[bot.getPosition().p1][bot.getPosition().p2 + 1].objType == Object::BrockenWall)
					{
						point pos = { bot.getPosition().p1, bot.getPosition().p2 + 1 };
						bot.setPosition(pos);
						return;
					}
			}
		}
	}
	void updateBots(botClass bot, std::vector<std::vector<cell>> field)
	{
		for (int i = 0; i < bots.size(); i++)
		{
			setBotPosition(bots[i], field);
		}
	}
};

