#pragma once
#include "IGameScreen.h"
#include "GameManager.h"

namespace gameScreens {
    class SettingsGameScreen :
        public GameScreenBase
    {
    public:
        SettingsGameScreen(GameManager* gameManagerPointer)
        {
            gameManager = gameManagerPointer;
        }

        virtual void Update();
        virtual Component Render();

    private:
        GameManager* gameManager;

    };
}