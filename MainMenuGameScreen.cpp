#include "MainMenuGameScreen.h"
#include "AboutGameScreen.h"
#include "SettingsGameScreen.h"
#include "GameplayGameScreen.h"
#include "LanguageHelper.h"

using namespace gameScreens;

void gameScreens::MainMenuGameScreen::Update()
{
}

Component gameScreens::MainMenuGameScreen::Render()
{
    auto startButton = Button(LanguageHelper::Translit("Èãðàòü!"), [&]() {
        this->gameManager->SetGameScreen(new GameplayGameScreen(this->gameManager));
    });

    auto aboutButton = Button(LanguageHelper::Translit("Î íàñ"), [&]() {
        this->gameManager->SetGameScreen(new AboutGameScreen(this->gameManager));
    });

    auto settingsButton = Button(LanguageHelper::Translit("Íàñòðîéêè"), [&]() {
        this->gameManager->SetGameScreen(new SettingsGameScreen(this->gameManager));
    });

    auto exitButton = Button(LanguageHelper::Translit("Âûéòè"), [&]() {
        exit(0);
    });

    auto buttons = Container::Horizontal({
        startButton,
        aboutButton,
        settingsButton,
        exitButton
    });

    auto renderer = Renderer(buttons, [&] {
        this->Update();

        return WrapMainUI(
            vbox({
                filler(),
                paragraphAlignCenter(LanguageHelper::Translit("ÃËÀÂÍÎÅ ÌÅÍÞ")),
                text(""),
                startButton->Render() | center | color(Color::Green),
                aboutButton->Render() | center | color(Color::Yellow),
                settingsButton->Render() | center | color(Color::Aquamarine1),
                exitButton->Render() | center | color(Color::Red),
                filler()
            })
        );
    });

    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(renderer);

    return renderer;
}
