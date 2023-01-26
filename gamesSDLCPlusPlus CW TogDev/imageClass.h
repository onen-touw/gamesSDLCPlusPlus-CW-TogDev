#pragma once
#include"settings.h"
class imageClass
{
protected:

	std::vector<SDL_Surface*> imageVector;


private:
	void createImageVector(size_t size) {
		imageVector.resize(size);
	}

	void load(std::string path, unsigned enumName) {
		bool success = true;
		SDL_Surface* flower = IMG_Load(path.c_str());
		if (flower == nullptr) {
			std::cout << "Can't load: " << IMG_GetError() << std::endl;
			success = false;
			return;
		}

		/// optimization imgSurface for target surface
		flower = SDL_ConvertSurface(flower, gameSettings::winSetting.surface->format, NULL);
		if (flower == nullptr) {
			std::cout << "Can't convert: " << SDL_GetError() << std::endl;
			success = false;
			return;
		}
		if (!success)
		{
			system("pause");
			exit(-2);
		}
		imageVector[enumName] = flower;
		return;
	}

public:

	imageClass(){}

	~imageClass()
	{
		if (this->imageVector.size() > 0)
		{
			for (int i = 0; i < this->imageVector.size(); i++)
			{
				SDL_FreeSurface(this->imageVector[i]);
			}
			this->imageVector.clear();
		}
	}

	SDL_Surface* getImage(unsigned enumName) {
		return imageVector[enumName];
	}

	void loadImages(std::vector<imagePath>vPaths) {

		this->createImageVector(vPaths.size());
		
		for (int i = 0; i < this->imageVector.size(); i++)
		{
			std::cout << vPaths[i].path << "<< loading #" << i << "\n";
			this->load(vPaths[i].path, vPaths[i].position);
		}
	}

	SDL_Surface* loadOneImg(std::string path) {
		SDL_Surface* flower = IMG_Load(path.c_str());
		if (flower == nullptr) {
			std::cout << "Can't load: " << IMG_GetError() << std::endl;
			system("pause");
			exit(-2);
		}
		return flower;
	}


	void logOut() {
		for (int i = 0; i < imageVector.size(); i++)
		{
			if (imageVector[i] != nullptr)
			{
				std::cout << "picture uploaded:: #" << i << "\n";
			}
		}
	}

};

