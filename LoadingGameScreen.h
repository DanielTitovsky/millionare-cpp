#pragma once
#include "IGameScreen.h"
#include "GameManager.h"

namespace gameScreens {
    class LoadingGameScreen :
        public GameScreenBase
    {
        
        public:
            LoadingGameScreen(GameManager* gameManagerPointer)
            {
                gameManager = gameManagerPointer;
                loadingProgress = 0;
            }

        private:
            float loadingProgress;
            GameManager* gameManager;

        public:
            virtual void Update();
            virtual Component Render();
    };
};