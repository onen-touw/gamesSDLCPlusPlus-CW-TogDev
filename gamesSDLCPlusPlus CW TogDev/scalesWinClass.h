#pragma once
#include "interfaceObjects.h"
class scalesWinClass :
    public interfaceObjects
{
public: const short openMenu = 0;
private:

    std::string text1 = "Перетащите объект сюда";
    SDL_Rect rectForChosenPict = {};
    int containerTextH = 100;
    int imageH = 100;
    std::vector<SDL_Surface*> picts;
    SDL_Surface* CH = nullptr;
    int objWeight = 0;

public:
    scalesWinClass(SDL_Surface* bgImg, TTF_Font* font, SDL_Rect rect) :interfaceObjects(bgImg, font, rect) {
        this->rectForChosenPict = { rect.x + rect.w / 2 - this->imageH / 2, (gameSettings::winSetting.winH - containerTextH - gameSettings::winSetting.header) / 2,
            this->imageH,this->imageH };
    }
    ~scalesWinClass()
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

    void setPictureToCompaire(SDL_Surface* img, int objWeight) {
        this->picts.push_back(img);
        this->objWeight += objWeight;
    }
    void blitCH(int n, int posY, SDL_Surface* img)
    {
        CH = img;
        if (n == 1)
        {
            this->rectForChosenPict = this->rectForChosenPict = { 10, posY + this->imageH / 2,
                        380,20 };
        }
        else
        {
            this->rectForChosenPict = this->rectForChosenPict = { 610, posY + this->imageH / 2,
                       380,20 };
        }
        this->blitBg(this->CH, this->rectForChosenPict);
    }
    void blitPicts(int n, int posY) {
        
        int posX = (gameSettings::winSetting.block - this->imageH) / picts.size();
        if (n == 1)
        {
            for (int i = 0; i < picts.size(); i++)
            {
                this->rectForChosenPict = this->rectForChosenPict = { posX * i + posX / 2, posY - this->imageH / 2,
                    this->imageH,this->imageH };
                this->blitBg(this->picts[i], this->rectForChosenPict);
            }
        }
        else
        {
            for (int i = 0; i < picts.size(); i++)
            {
                this->rectForChosenPict = this->rectForChosenPict = { 600 + posX * i + posX / 2, posY - this->imageH / 2,
                    this->imageH,this->imageH };
                this->blitBg(this->picts[i], this->rectForChosenPict);
            }
        }
    }
    void resetWin()
    {
        this->picts.clear();
        this->objWeight = 0;
    }
    int tempGetL() { return this->objWeight; }
};

