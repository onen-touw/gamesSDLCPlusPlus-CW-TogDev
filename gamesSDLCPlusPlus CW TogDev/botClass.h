#pragma once

#include"interfaceObjects.h"
#include"imageClass.h"

class botClass
{
protected:
	point botPosition = { 0, 0 };
	point botOldPosition = { 0, 0 };
public:
	botClass() {

	}

	~botClass()
	{

	}

	point getPosition()
	{
		return botPosition;
	}
	point getOldPosition()
	{
		return botOldPosition;
	}
	void setPosition(point pos)
	{
		botPosition = pos;
	}
	void setOldPosition(point pos)
	{
		botOldPosition = pos;
	}

};

