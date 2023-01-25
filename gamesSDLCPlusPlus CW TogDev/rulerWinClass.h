#pragma once
#include "interfaceObjects.h"
class rulerWinClass :
    public interfaceObjects
{
public: const short openMenu = 0;
private:
   
    std::string text1 = "Перетащите картинку сюда";
    SDL_Rect rectForChosenPict = {};
    int containerTextH = 100;
    int imageH = 200;
    SDL_Surface* pict = nullptr;
    short objLenth = 0;

public:
    rulerWinClass(SDL_Surface* bgImg, TTF_Font* font, SDL_Rect rect) :interfaceObjects(bgImg, font, rect) {
        this->rectForChosenPict = { rect.x + rect.w / 2 - this->imageH/2, (gameSettings::winSetting.winH - containerTextH - gameSettings::winSetting.header) / 2,
            this->imageH,this->imageH };
    }
    ~rulerWinClass()
    {
        this->text1.clear();
    }
    void blit()
    {
        this->blitBg();
        SDL_Rect containerTxtRect = this->objRect;
        containerTxtRect.y = gameSettings::winSetting.header;
        containerTxtRect.h = this->containerTextH;
        this->blitOnlyTextCenter(this->text1.c_str(), containerTxtRect);
    }

    void setPictureToCompaire(SDL_Surface* img) {
        this->pict = img;
    }

    void blitPict() {
        this->blitBg(this->pict, this->rectForChosenPict);
    }
}; 

