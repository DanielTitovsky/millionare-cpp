#include "GameplayGameScreen.h"
#include "MainMenuGameScreen.h"
#include "LanguageHelper.h"

struct GameStats
{
    // Config
    const int questionsPerLevel = 3; // Сколько вопросов на одном уровне
    std::string levelName = "Lite";

    int questionsNumber = 0; // Порядковый номер текущего вопроса
    int score = 0; // Счет игрока
    
    bool helpCallUsed = false; // Использована ли подсказка позвонить другу
    bool helpCallActive = false; // Активна ли подсказка Звонок бичу

    bool help50Used = false; // Использована ли подсказка
    bool help50Active = false; // Активна ли подсказка 50/50

    Value currentQuestion = NULL;
    QuestionsManager questionsManager;

    /// <summary>
    /// Использовать подсказку звонок бичу
    /// </summary>
    void helpCall() {
        helpCallUsed = true;
        helpCallActive = true;
    }

    /// <summary>
    /// Использовать подсказку 50/50
    /// </summary>
    void Help50() {
        help50Used = true;
        help50Active = true;
    }

    /// <summary>
    /// Ответить на вопрос
    /// </summary>
    /// <param name="answerNumber"></param>
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

    /// <summary>
    /// Следующий ответ
    /// </summary>
    void NextQuestion()
    {
        help50Active = false;
        auto questions = questionsManager.GetQuestions();
        if (questionsNumber >= questionsPerLevel * 2) // 4
        {
            levelName = "Hard";
        }
        else if (questionsNumber >= questionsPerLevel) // 2
        {
            levelName = "Normal";
        }

        auto levelsQuestions = questions[levelName]; // Вопросы текущего уровня сложности
        currentQuestion = GetRandomQuestion(levelsQuestions); // Запрашиваем рандомный вопрос из списка
        questionsNumber++;
    }

    /// <summary>
    /// Получить рандомный вопрос из списка вопросов
    /// </summary>
    /// <param name="questionsList">Список вопросов</param>
    /// <returns>Рандомный ответ</returns>
    Value GetRandomQuestion(Value questionsList)
    {
        int randomArrayKey = rand() % questionsList.size(); // Сгенерировать рандомный ключ массива
        return questionsList[randomArrayKey]; // Вернуть рандомный элемент массива по сегенерированному ключу
    }
};

Component gameScreens::GameplayGameScreen::Render()
{
    GameStats gameStats;
    gameStats.NextQuestion(); // Отображаем следующий вопрос при старте игры

    std::string answer1 = "";
    std::string answer2 = "";
    std::string answer3 = "";
    std::string answer4 = "";

    auto passButton = Button("PASS", [&]() { gameStats.NextQuestion(); });
    auto backButton = Button("MENU", [&]() { this->gameManager->GoToMainMenu(); });

    auto optionsButton1 = Button(&answer1, [&]() { gameStats.Answer(0); });
    auto optionsButton2 = Button(&answer2, [&]() { gameStats.Answer(1); });
    auto optionsButton3 = Button(&answer3, [&]() { gameStats.Answer(2); });
    auto optionsButton4 = Button(&answer4, [&]() { gameStats.Answer(3); });

    auto hideCallToFriendButton = Button("THANKS!", [&]() {
        gameStats.helpCallActive = false;
    });

    auto helpCall = Button("Call a friend", [&]() {
        gameStats.helpCall();
    }) | color(Color::Yellow3Bis);

    auto help50 = Button("50/50", [&]() {
        gameStats.Help50();
    }) | color(Color::Green3Bis);

    auto answerButtons = Container::Horizontal({ });
    auto helpButtons = Container::Horizontal({});

    auto container = Container::Vertical({
        answerButtons,
        helpButtons,
        hideCallToFriendButton,
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

        int answer = gameStats.currentQuestion["answer"].asInt(); // Номер правильного ответа в массиве

        // Добавить кнопки вариантов ответов
        answerButtons->DetachAllChildren();
        for (int i = 0; i < gameStats.currentQuestion["options"].size(); i++) 
        {
            std::string q = gameStats.currentQuestion["options"][i].toStyledString();
            switch (i) 
            {
                case 0:
                    if (gameStats.help50Active && answer != i) {
                        break;
                    }
                    answerButtons->Add(optionsButton1);
                    answer1 = std::to_string(i + 1) + ")" + q;
                    break;
                case 1:
                    if (gameStats.help50Active && answer != i) {
                        break;
                    }
                    answerButtons->Add(optionsButton2);
                    answer2 = std::to_string(i + 1) + ")" + q;
                    break; 
                case 2:
                    answerButtons->Add(optionsButton3);
                    answer3 = std::to_string(i + 1) + ")" + q;
                    break;
                case 3:
                    answerButtons->Add(optionsButton4);
                    answer4 = std::to_string(i + 1) + ")" + q;
                    break;
            }
        }

        // Добавить кнопки подсказок
        helpButtons->DetachAllChildren();
        if (!gameStats.help50Used) {
            helpButtons->Add(help50);
        }
        if (!gameStats.helpCallUsed) {
            helpButtons->Add(helpCall);
        }

        // окно помощь друга
        if (gameStats.helpCallActive) {
            return WrapMainUI(
                vbox({
                    vbox({
                        text("YOUR FRIEND RECOMENDS ANSWER №"+ std::to_string(answer + 1)) | center,
                    }) | center | flex_grow ,
                    separator(),
                    hbox({
                        hideCallToFriendButton->Render()
                    }) | center
                }) | flex
            );
        }
        // Проигрыш
        else if (gameStats.score < 0) {
            return WrapMainUI(
                vbox({
                    vbox({
                        text("YOU LOSE...") | center,
                    }) | center | flex_grow ,
                    separator(),
                    hbox({
                        backButton->Render()
                    }) | center
                }) | flex
            );
        }
        // Выигрыш
        else if (gameStats.questionsNumber > gameStats.questionsPerLevel * 3) {
            return WrapMainUI(
                vbox({
                    vbox({
                        text("YOU WIN!") | center,
                        text("YOUR SCORE: " + std::to_string(gameStats.score))
                    }) | center | flex_grow ,
                    separator(),
                    hbox({
                        backButton->Render() | color(Color::Gold3)
                    }) | center
                }) | flex
            );
        }
        // Игровой процесс
        else {
            return WrapMainUI(
                vbox({
                    hbox({
                        passButton->Render() | color(Color::GrayLight),
                        filler(),
                        vbox({
                            text(LanguageHelper::Translit("Внимание " + gameManager->gameState.userName + "!")) | bold | center | color(Color::Green3),
                            text(LanguageHelper::Translit("Вопрос номер " + std::to_string(gameStats.questionsNumber))) | center,
                            text("Level: "+ gameStats.levelName) | center | color(Color::Gold1)
                        }),
                        filler(),
                        backButton->Render() | color(Color::Red)
                    }),
                    filler(),
                    vbox({

                        paragraphAlignCenter(LanguageHelper::Translit(gameStats.currentQuestion["text"].toStyledString())) | borderDouble,
                        filler(),
                        answerButtons->Render() | center
                    }),
                    filler(),
                    separator(),
                    vbox({
                        text("Helpers:") | center,
                        hbox({
                           helpButtons->Render()
                        }) | center
                    }) | center,
                    separator(),
                    hbox({
                        text("Your score: "+ std::to_string(gameStats.score))
                    }) | center
                })
            );
        }

    });

    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(renderer);

    return renderer;
}

void gameScreens::GameplayGameScreen::Update()
{

}