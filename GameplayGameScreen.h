#pragma once
#include "IGameScreen.h"
#include "GameManager.h"

namespace gameScreens {
    class GameplayGameScreen :
        public GameScreenBase
    {
    public:
        GameplayGameScreen(GameManager* gameManagerPointer)
        {
            gameManager = gameManagerPointer;
        }

        virtual void Update();
        virtual Component Render();

    private:
        GameManager* gameManager;

    };
}