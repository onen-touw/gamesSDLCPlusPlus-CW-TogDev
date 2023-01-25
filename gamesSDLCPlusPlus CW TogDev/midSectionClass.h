#pragma once

#include"interfaceObjects.h"
#include"imageClass.h"

class midSectionClass : public interfaceObjects, public imageClass
{

private:

    std::string text1 = "Выберите объект для сравнения";
    std::vector<SDL_Rect>imgRects = {};
    int containerTextH = 100;
    int imageH = 100;

public:
    midSectionClass(SDL_Surface* bgImg, TTF_Font* font, SDL_Rect rect) :interfaceObjects(bgImg, font, rect) {
        this->loadImages(gameSettings::objectsFC.objParam);
        for (int i = 0; i < ObjectID::TOTAL; i++)
        {
            this->imgRects.push_back({ rect.x, rect.y + this->containerTextH + this->imageH*i , rect.w, this->imageH });
        }


    }
    ~midSectionClass()
    {
        this->text1.clear();
    }
    void blit()
    {
        this->blitBg();
        SDL_Rect containerRect = this->objRect;
        containerRect.y = gameSettings::winSetting.header;
        containerRect.h = containerTextH;
        this->blitOnlyTextCenter(this->text1.c_str(), containerRect);

        for (int i = 0; i < imgRects.size(); i++)
        {
            this->blitBg(this->imageVector[i], this->imgRects[i]);
        }
    }

    SDL_Surface* choseImgByClick(int x, int y) {
        for (int i = 0; i < imgRects.size(); i++)
        {
            if (x >= imgRects[i].x && x <= imgRects[i].x + imgRects[i].w 
                && y >= imgRects[i].y && y <= imgRects[i].y + imgRects[i].h)
            {
                return imageVector[i];
            }
        }
        return nullptr;
    }


};

