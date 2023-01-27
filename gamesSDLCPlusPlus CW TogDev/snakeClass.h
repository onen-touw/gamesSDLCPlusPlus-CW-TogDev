#pragma once

#include"imageClass.h"

class snakeClass : public imageClass
{
private:
	std::vector<snakePaaram> snake;
	int headDirection = _directions::DOWN;
	int cellSize = 0;


public:
	snakeClass(point pos){
		snake.push_back({pos, pos });		///head
		this->loadImages(gameSettings::fieldSetting.snakeImagesPathVector);
		this->cellSize =  gameSettings::fieldSetting.cellSize;
	}
	~snakeClass() {
		snake.clear();
	}

	void snakeEat() {
		this->snake.push_back(this->snake[this->snake.size() - 1]);
	}

	point snakeGetHeadPos() { return this->snake[0].pos; }
	int getHeadDirection() { return this->headDirection; }

	bool snakeChangeDirection(int direction, std::vector<std::vector<cellV>>&V) {
		switch (direction)
		{
		case _directions::UP:
			if (this->headDirection != _directions::DOWN)
			{
				if (this->snake[0].pos.p1 - 1 > 0)
				{
					this->headDirection = _directions::UP;
				}
			}
			else return false;
			break;
		case _directions::LEFT:
			if (this->headDirection != _directions::RIGHT)
			{
				if (this->snake[0].pos.p2 - 1 > 0) {
					this->headDirection = _directions::LEFT;
				}
			}
			else return false;
			break;
		case _directions::DOWN:
			if (this->headDirection != _directions::UP)
			{
				if (this->snake[0].pos.p1 + 1ull < V.size()) {
					this->headDirection = _directions::DOWN;
				}
			}
			else return false;
			break;
		case _directions::RIGHT:
			if (this->headDirection != _directions::LEFT)
			{
				if (this->snake[0].pos.p2 + 1ull < V[0].size())
				{
					this->headDirection = _directions::RIGHT;
				}
			}
			else return false;
			break;

		default:
			break;
		}

		return true;
	}

	bool checkSnakeÑollision() {
		if (this->snake.size()>3)
		{
			for (int i = 1; i < this->snake.size(); i++)
			{
				if (this->snake[0].pos.p1 == this->snake[i].pos.p1 && this->snake[0].pos.p2 == this->snake[i].pos.p2)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool transmitSnake(std::vector<std::vector<cellV>>&V) {
		switch (this->headDirection)
		{
		case _directions::UP:
			if (this->snake[0].pos.p1 - 1 > 0)
			{
				if (!this->checkSnakeÑollision())
				{
					this->snake[0].lastPos = this->snake[0].pos;
					this->snake[0].pos.p1--;
					
				}
				else return false;
			}
			else return false;

			break;
		case _directions::LEFT:
			if (this->snake[0].pos.p2 - 1ll > 0) {
				if (!this->checkSnakeÑollision())
				{
					this->snake[0].lastPos = this->snake[0].pos;
					this->snake[0].pos.p2--;
				}
				else return false;
			}
			else return false;
			break;
		case _directions::DOWN:
			if (this->snake[0].pos.p1 + 1ull < V.size()) {
				if (!this->checkSnakeÑollision())
				{
					this->snake[0].lastPos = this->snake[0].pos;
					this->snake[0].pos.p1++;
				}
				else return false;
			}
			else return false;
			break;
		case _directions::RIGHT:
			if (this->snake[0].pos.p2 + 1ull < V[0].size())
			{
				if (!this->checkSnakeÑollision())
				{
					this->snake[0].lastPos = this->snake[0].pos;
					this->snake[0].pos.p2++;
				}
				else return false;
			}
			else return false;
			break;

		default:
			break;
		}

		SDL_Rect mr = { this->snake[0].pos.p2 * this->cellSize,this->snake[0].pos.p1 * this->cellSize + gameSettings::winSetting.header , this->cellSize, this->cellSize, };
		SDL_BlitScaled(imageVector[gameSettings::fieldSetting.head], NULL, gameSettings::winSetting.surface, &mr);
		if (this->snake.size() <= 1)
		{
			mr.x = this->snake[this->snake.size() - 1].lastPos.p2 * this->cellSize;
			mr.y = this->snake[this->snake.size() - 1].lastPos.p1 * this->cellSize + gameSettings::winSetting.header;

		}
		else
		{
			mr.x = this->snake[this->snake.size() - 1].pos.p2 * this->cellSize;
			mr.y = this->snake[this->snake.size() - 1].pos.p1 * this->cellSize + gameSettings::winSetting.header;
		}
			SDL_BlitScaled(imageVector[gameSettings::fieldSetting.emptyCell], NULL, gameSettings::winSetting.surface, &mr);
		std::cout << mr.x << " " << mr.y << " " << mr.w << " " << mr.h << " \n";

		for (int i = 1; i < this->snake.size(); i++)
		{
			this->snake[i].lastPos = this->snake[i].pos;

			this->snake[i].pos = this->snake[i - 1ll].lastPos;

		}
		return true;
	}
	

	void blitFullSnake() {
		if (this->snake.size() > 0)
		{
			for (int i = 0; i < this->snake.size(); i++)
			{
				SDL_Rect mr = { this->snake[i].pos.p2 * this->cellSize,this->snake[i].pos.p1 * this->cellSize + gameSettings::winSetting.header , this->cellSize, this->cellSize };
				SDL_BlitScaled(this->imageVector[gameSettings::fieldSetting.head], NULL, gameSettings::winSetting.surface, &mr);
			}
		}
	}

};



