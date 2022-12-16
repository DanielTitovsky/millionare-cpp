#pragma once
#include "IGameScreen.h"
#include "GameManager.h"

namespace gameScreens {
    class AboutGameScreen :
        public GameScreenBase
    {
        public:
            AboutGameScreen(GameManager* gameManagerPointer)
            {
                gameManager = gameManagerPointer;
            }

            virtual void Update();
            virtual Component Render();

        private:
            GameManager* gameManager;

    };
}