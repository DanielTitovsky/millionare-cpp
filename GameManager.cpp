#include "GameManager.h"
#include "json/json.h"
#include <iostream>
#include <fstream>

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref
#include "QuestionsManager.h"
#include "LoadingGameScreen.h"
#include "MainMenuGameScreen.h"

using namespace Json;
using namespace ftxui;
using namespace gameScreens;
using namespace std;

void GameManager::Bootstrap()
{
    SetGameScreen(new LoadingGameScreen(this));
}

void GameManager::RenderQuestions() {
    auto questions = questionsManager.GetQuestions();

    for (ArrayIndex i = 0; i < questions.size(); i++)
    {
        Value question = questions[i];
        Value text = question["text"];
        Value options = question["options"];
        Value answer = question["answer"];

        cout << "Text: " << text << endl;
        cout << "Answers:";

        for (ArrayIndex i2 = 0; i2 < options.size(); i2++)
        {
            cout << options[i2] << "|";
        }

        cout << endl << "Answer: " << answer << endl << endl;
    }
}

void GameManager::GoToMainMenu()
{
    SetGameScreen(new MainMenuGameScreen(this));
}
