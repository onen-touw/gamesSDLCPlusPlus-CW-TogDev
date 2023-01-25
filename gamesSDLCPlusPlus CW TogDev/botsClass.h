#pragma once
#include"botClass.h"
#include"imageClass.h"

class botsClass/*:public botClass*/: public imageClass
{
private:
	std::vector<botClass> bots;
	std::vector<std::pair<point, short int>> way;

	SDL_Surface* botImg = nullptr;
	short cellSize = 0;
	short headerH = 0;

public:
	botsClass() {
		this->botImg = this->loadOneImg("./image/bot/ghost.png");
		this->cellSize = gameSettings::winSetting.cellSize;
		this->headerH = gameSettings::winSetting.headerHeight;
	}
	~botsClass()
	{
		this->bots.clear();
		this->way.clear();
	}

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
	bool killCharacter(point charpos)
	{
		for (int i = 0; i < bots.size(); i++)
		{
			if (bots[i].getPosition().p1 == charpos.p1 && bots[i].getPosition().p2 == charpos.p2)
			{
				bots.erase(bots.begin() + i);
				return true;
			}
			else if (bots[i].getPosition().p1 == charpos.p1 + 1 && bots[i].getPosition().p2 == charpos.p2)
			{
				bots.erase(bots.begin() + i);
				return true;
			}
			else if (bots[i].getPosition().p1 == charpos.p1 - 1 && bots[i].getPosition().p2 == charpos.p2)
			{
				bots.erase(bots.begin() + i);
				return true;
			}
			else if (bots[i].getPosition().p1 == charpos.p1 && bots[i].getPosition().p2 == charpos.p2 + 1)
			{
				bots.erase(bots.begin() + i);
				return true;
			}
			else if (bots[i].getPosition().p1 == charpos.p1 && bots[i].getPosition().p2 == charpos.p2 - 1)
			{
				bots.erase(bots.begin() + i);
				return true;
			}
		}
		return false;
	}
	void spawnBot(point botPosition)
	{
		botClass bot = botClass(botPosition);
		bots.push_back(bot);
	}

	std::vector<point> checkCell(std::vector<std::vector<std::pair<cell, bool>>> field, point pos)
	{
		std::vector<point> temp;
		if (pos.p1 > 0)
		{
			if (field[pos.p1 - 1][pos.p2].second == false)
			{
				if (field[pos.p1 - 1][pos.p2].first.objType == Object::Empty || field[pos.p1 - 1][pos.p2].first.objType == Object::BrockenWall || field[pos.p1 - 1][pos.p2].first.objType == Object::bot)
				{
					point tempPos = { pos.p1 - 1, pos.p2 };
					temp.push_back(tempPos);
				}
			}
		}
		if (pos.p1 < field.size() - 1)
		{
			if (field[pos.p1 + 1][pos.p2].second == false)
			{
				if (field[pos.p1 + 1][pos.p2].first.objType == Object::Empty || field[pos.p1 + 1][pos.p2].first.objType == Object::BrockenWall || field[pos.p1 + 1][pos.p2].first.objType == Object::bot)
				{
					point tempPos = { pos.p1 + 1, pos.p2 };
					temp.push_back(tempPos);
				}
			}
		}
		if (pos.p2 > 0)
		{
			if (field[pos.p1][pos.p2 - 1].second == false)
			{
				if (field[pos.p1][pos.p2 - 1].first.objType == Object::Empty || field[pos.p1][pos.p2 - 1].first.objType == Object::BrockenWall || field[pos.p1][pos.p2 - 1].first.objType == Object::bot)
				{
					point tempPos = { pos.p1, pos.p2 - 1 };
					temp.push_back(tempPos);
				}
			}
		}
		if (pos.p2 < field[0].size() - 1)
		{
			if (field[pos.p1][pos.p2 + 1].second == false)
			{
				if (field[pos.p1][pos.p2 + 1].first.objType == Object::Empty || field[pos.p1][pos.p2 + 1].first.objType == Object::BrockenWall || field[pos.p1][pos.p2 + 1].first.objType == Object::bot)
				{
					point tempPos = { pos.p1, pos.p2 + 1 };
					temp.push_back(tempPos);
				}
			}
		}
		return temp;
	}
	void findWay(std::vector<std::vector<cell>>& fieldV, point characterPosition)
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
		this->way.clear();
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
					field[temp[j].p1][temp[j].p2].second = true;
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
		field.clear();
	}
	void setBotPosition(botClass& bot, std::vector<std::vector<cell>>& field)
	{
		bool find = false;
		//std::cout << bot.getPosition().p1 << " " << bot.getPosition().p2 << " botPOs\n";
		field[bot.getPosition().p1][bot.getPosition().p2].objType = Object::Empty;
		bot.setOldPosition(bot.getPosition());
		for (int i = 0; i < this->way.size(); i++)
		{

			if (bot.getPosition().p1 == this->way[i].first.p1 && bot.getPosition().p2 == this->way[i].first.p2)
			{
				std::cout << bot.getPosition().p1 << " " << bot.getPosition().p2 << " botPOs\n";

				find = true;
				bot.setPosition(this->way[this->way[i].second].first);
				field[bot.getPosition().p1][bot.getPosition().p2].objType = Object::bot;
				return;
			}
		}
		if (find == false)
		{
			if(bot.getPosition().p1 > 0)
			{
					if (field[bot.getPosition().p1 - 1ll][bot.getPosition().p2].objType == Object::Empty || field[bot.getPosition().p1 - 1][bot.getPosition().p2].objType == Object::BrockenWall)
					{
						point pos = { bot.getPosition().p1 - 1, bot.getPosition().p2 };
						bot.setPosition(pos);
						field[bot.getPosition().p1][bot.getPosition().p2].objType = Object::bot;
						return;
					}
			}
			if (bot.getPosition().p1 < field.size() - 1)
			{
					if (field[bot.getPosition().p1 + 1][bot.getPosition().p2].objType == Object::Empty || field[bot.getPosition().p1 + 1][bot.getPosition().p2].objType == Object::BrockenWall)
					{
						point pos = { bot.getPosition().p1 + 1, bot.getPosition().p2 };
						bot.setPosition(pos);
						field[bot.getPosition().p1][bot.getPosition().p2].objType = Object::bot;
						return;
					}
			}
			if (bot.getPosition().p2 > 0)
			{
					if (field[bot.getPosition().p1][bot.getPosition().p2 - 1].objType == Object::Empty || field[bot.getPosition().p1][bot.getPosition().p2 - 1].objType == Object::BrockenWall)
					{
						point pos = { bot.getPosition().p1, bot.getPosition().p2 - 1 };
						bot.setPosition(pos);
						field[bot.getPosition().p1][bot.getPosition().p2].objType = Object::bot;
						return;
					}
			}
			if (bot.getPosition().p2 < field[0].size() - 1)
			{
					if (field[bot.getPosition().p1][bot.getPosition().p2 + 1].objType == Object::Empty || field[bot.getPosition().p1][bot.getPosition().p2 + 1].objType == Object::BrockenWall)
					{
						point pos = { bot.getPosition().p1, bot.getPosition().p2 + 1 };
						bot.setPosition(pos);
						field[bot.getPosition().p1][bot.getPosition().p2].objType = Object::bot;
						return;
					}
			}
		}
	}
	void updateBots(std::vector<std::vector<cell>>& field, point charPos)
	{
		std::cout << "hui" << std::endl;
		this->findWay(field, charPos);
		std::cout << this->way.size() << std::endl;
		for (int i = 0; i < bots.size(); i++)
		{
			setBotPosition(bots[i], field);
			//std::cout << bots[i].getPosition().p1 << " " << bots[i].getPosition().p2 << " botPOs\n";
		}
	}

	void blitBots(std::vector<std::vector<cell>>& V) {
		SDL_Rect mr = { 0,0, this->cellSize,this->cellSize };
		for (int i = 0; i < this->bots.size(); i++)
		{

			V[this->bots[i].getOldPosition().p1][this->bots[i].getOldPosition().p2].objType = Object::Empty;
			

			mr = { this->bots[i].getPosition().p2 * this->cellSize, this->bots[i].getPosition().p1*this->cellSize + headerH,this->cellSize,this->cellSize };
			SDL_BlitScaled(this->botImg, NULL, gameSettings::winSetting.surface, &mr);
		}


	}

};

