#pragma once
#include <iostream>
#include <fstream>

#include "QuestionsManager.h"
#include "IGameScreen.h"

struct GameState
{
public:
	GameState() {
		score = 0;
		userName = "Piter Pan";
		activeLanguageId = 0;
	}

public:
	int score;
	int activeLanguageId; // 0 - RU; 1 - EN
	std::string userName;
};

