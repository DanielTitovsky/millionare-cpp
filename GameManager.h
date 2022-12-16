#pragma once
#include <iostream>
#include <fstream>

#include "QuestionsManager.h"
#include "GameState.h"
#include "IGameScreen.h"

class GameManager
{
private:
	IGameScreen* currentGameScreen;

public:
	QuestionsManager questionsManager;
	GameState gameState;

public:
	GameManager() {
		currentGameScreen = nullptr;
	}

	void SetGameScreen(IGameScreen* screen) {
		if (currentGameScreen != nullptr) {
			delete currentGameScreen;
		}

		currentGameScreen = screen;
		currentGameScreen->Render();
	}
	
	void Bootstrap();
	void GoToMainMenu();

    void RenderQuestions();
};

