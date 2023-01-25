#pragma once

#include"interfaceObjects.h"
#include"imageClass.h"

class botClass
{
private:
	point botPosition = { 0, 0 };
	point nextPosition = { 0, 0 };
public:
	botClass() {

	}

	~botClass()
	{

	}

	bool checkCell(std::vector<std::vector<cell>> field, point position)
	{
		//if(field[position.p1][position.p2].objType == )
	}

	void calculateNewBotPosition(std::vector<std::vector<cell>> field, point characterPosition)
	{
		std::vector<std::pair<point, point>> reviewQueue;
		reviewQueue;
	}

};

