#pragma once
#include "interfaceObjects.h"
class rulerWinClass :
    public interfaceObjects
{
public: const short openMenu = 0;
private:
    SDL_Rect RectRight = { 0, gameSettings::winSetting.header , gameSettings::winSetting.winW/3, gameSettings::winSetting.winH };
    SDL_Rect RectLeft = { gameSettings::winSetting.winW - gameSettings::winSetting.winW / 3, gameSettings::winSetting.header , gameSettings::winSetting.winW, gameSettings::winSetting.winH };
public:
    rulerWinClass(SDL_Surface* bgImg) :interfaceObjects(bgImg) {}
    ~rulerWinClass()
    {

    }
    void blit()
    {
        this->blitBg();
    }
};

