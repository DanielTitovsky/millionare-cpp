#include "GameplayGameScreen.h"
#include "MainMenuGameScreen.h"
#include "LanguageHelper.h"

Component gameScreens::GameplayGameScreen::Render()
{
    auto passButton = Button("PASS", [&]() {
        this->gameManager->GoToMainMenu();
    });
    auto backButton = Button("MENU", [&]() {
        this->gameManager->GoToMainMenu();
    });

    auto optionsButton1 = Button("1) Tom", [&]() { });
    auto optionsButton2 = Button("2) Jerry", [&]() {});
    auto optionsButton3 = Button("3) Mickey", [&]() {});
    auto optionsButton4 = Button("4) Mouse", [&]() {});

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

        return WrapMainUI(
            vbox({
                hbox({
                    passButton->Render() | color(Color::GrayLight),
                    filler(),
                    vbox({
                        text(LanguageHelper::Translit("Внимание "+gameManager->gameState.userName+"!")) | bold | center | color(Color::Green3),
                        text(LanguageHelper::Translit("Вопрос номер 1")) | center
                    }),
                    filler(),
                    backButton->Render() | color(Color::Red)
                }),
                filler(),
                vbox({
                    paragraphAlignCenter(LanguageHelper::Translit("Кто у нас самый умный?")) | borderDouble,
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
                    text("Your score: 20")
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