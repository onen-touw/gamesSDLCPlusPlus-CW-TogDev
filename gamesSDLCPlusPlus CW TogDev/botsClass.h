#pragma once
#include"botClass.h"

class botsClass:public botClass
{
private:
	std::vector<botClass> bots;
	std::vector<std::pair<point, short int>> way;
public:
	std::vector<point> checkCell(std::vector<std::vector<cell>> field, point characterPosition)
	{
		std::vector<point> temp;
		if (characterPosition.p1 > 0)
		{
			if (field[characterPosition.p1 - 1][characterPosition.p2].objType == Object::Empty || field[characterPosition.p1 - 1][characterPosition.p2].objType == Object::BrockenWall)
			{ 
				point pos = { characterPosition.p1 - 1, characterPosition.p2 };
				temp.push_back(pos);
			}
		}
		if (characterPosition.p1 < field.size() - 1)
		{
			if (field[characterPosition.p1 + 1][characterPosition.p2].objType == Object::Empty || field[characterPosition.p1 + 1][characterPosition.p2].objType == Object::BrockenWall)
			{ 
				point pos = { characterPosition.p1 + 1, characterPosition.p2 };
				temp.push_back(pos);
			}
		}
		if (characterPosition.p2 > 0) {
			if (field[characterPosition.p1][characterPosition.p2 - 1].objType == Object::Empty || field[characterPosition.p1][characterPosition.p2 - 1].objType == Object::BrockenWall)
			{
				point pos = { characterPosition.p1, characterPosition.p2 - 1 };
				temp.push_back(pos);
			}
		}
		if (characterPosition.p2 < field[0].size() - 1) {
			if (field[characterPosition.p1][characterPosition.p2 + 1].objType == Object::Empty || field[characterPosition.p1][characterPosition.p2 + 1].objType == Object::BrockenWall)
			{
				point pos = { characterPosition.p1, characterPosition.p2 + 1 };
				temp.push_back(pos);
			}
		}
		return temp;
	}
	void findWay(std::vector<std::vector<cell>> field, point characterPosition)
	{
		way.clear();
		std::vector<point> nextCheck;
		std::vector<point> nowCheck;
		std::vector<point> temp = checkCell(field, characterPosition);
		for (int i = 0; i < temp.size(); i++)
		{
			nowCheck.push_back(temp[i]);
		}
		while (nowCheck.size() != 0)
		{
			for(int i = 0; i  nowCheck.size())
		}
	}
};

