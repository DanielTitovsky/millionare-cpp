#pragma once
#include <iostream>
#include <fstream>
#include "json/json.h"

using namespace Json;

class QuestionsManager
{
private:
    std::string QuestionsFilePath = "./questions.json";
    Value ReadFile();

public:
    Value GetQuestions();
};

