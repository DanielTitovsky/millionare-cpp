#include "GameplayGameScreen.h"
#include "MainMenuGameScreen.h"
#include "LanguageHelper.h"

struct GameStats
{
    int questionsNumber = 0;
    int score = 0;
    bool helpCallUsed = false;
    bool help50Used = false;
    Value currentQuestion = NULL;
    QuestionsManager questionsManager;

    void Answer(int answerNumber) 
    {
        bool isRight = currentQuestion["answer"] == answerNumber;
        if (isRight) 
        {
            score += 125;
            NextQuestion();
        }
        else {
            score -= 125;
            NextQuestion();
        }
    }
    void NextQuestion()
    {
        auto questions = questionsManager.GetQuestions();
        currentQuestion = questions["Lite"][questionsNumber];
        questionsNumber++;
    }

};

Component gameScreens::GameplayGameScreen::Render()
{
    GameStats gameStats;
    gameStats.NextQuestion();
    std::string answer1 = "";
    std::string answer2 = "";
    std::string answer3 = "";
    std::string answer4 = "";

    auto passButton = Button("PASS", [&]() {
        this->gameManager->GoToMainMenu();
    });
    auto backButton = Button("MENU", [&]() {
        this->gameManager->GoToMainMenu();
    });

    auto optionsButton1 = Button(&answer1, [&]() 
     { 
            gameStats.Answer(0);
     });
    auto optionsButton2 = Button(&answer2, [&]() {
            gameStats.Answer(1);
        });
    auto optionsButton3 = Button(&answer3, [&]() {
            gameStats.Answer(2);
        });
    auto optionsButton4 = Button(&answer4, [&]() {
            gameStats.Answer(3);
        });

    auto helpCall = Button("Call a friend", [&]() {});
    auto help50 = Button("50/50", [&]() {});

    auto container = Container::Vertical({
        passButton,
        backButton, 
        optionsButton1, 
        optionsButton2, 
        optionsButton3, 
        optionsButton4,
        helpCall,
        help50
    });

    auto renderer = Renderer(container, [&] {
        this->Update();
        answer1 = "";
        answer2 = "";
        answer3 = "";
        answer4 = "";

        for (int i = 0; i < gameStats.currentQuestion["options"].size(); i++) 
        {
            std::string q = gameStats.currentQuestion["options"][i].toStyledString();
            switch (i) 
            {
             case 0:
                 answer1 = q ;
                 break;
             case 1:
                 answer2 = q;
                 break; 
             case 2:
                 answer3 = q;
                 break;
             case 3:
                 answer4 = q;
                 break;
            }
        }

        return WrapMainUI(
            vbox({
                hbox({
                    passButton->Render() | color(Color::GrayLight),
                    filler(),
                    vbox({
                        text(LanguageHelper::Translit("Внимание "+gameManager->gameState.userName+"!")) | bold | center | color(Color::Green3),
                        text(LanguageHelper::Translit("Вопрос номер "+ std::to_string(gameStats.questionsNumber))) | center
                    }),
                    filler(),
                    backButton->Render() | color(Color::Red)
                }),
                filler(),
                vbox({
                    paragraphAlignCenter(LanguageHelper::Translit(gameStats.currentQuestion["text"].toStyledString())) | borderDouble,
                    filler(),
                    hbox({
                      optionsButton1->Render(),
                      optionsButton2->Render(),
                      optionsButton3->Render(),
                      optionsButton4->Render(),
                    }) | center
                }),
                filler(),
                separator(),
                vbox({
                    text("Helpers:") | center,
                    hbox({
                        helpCall->Render() | color(Color::Green3Bis),
                        help50->Render() | color(Color::Yellow3Bis),
                    }) | center
                }) | center,
                separator(),
                hbox({
                    text("Your score: "+ std::to_string(gameStats.score))
                }) | center
            })
        );
    });

    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(renderer);

    return renderer;
}


void gameScreens::GameplayGameScreen::Update()
{

}