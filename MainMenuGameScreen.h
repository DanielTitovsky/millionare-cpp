#pragma once
#include "IGameScreen.h"
#include "LoadingGameScreen.h"

namespace gameScreens {
    class MainMenuGameScreen :
        public GameScreenBase
    {

        public:
            MainMenuGameScreen(GameManager* gameManagerPointer)
            {
                gameManager = gameManagerPointer;
            }

            virtual void Update();
            virtual Component Render();

        private:
            GameManager* gameManager;
    };
}
