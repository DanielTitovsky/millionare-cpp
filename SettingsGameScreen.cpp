#include "SettingsGameScreen.h"
#include "MainMenuGameScreen.h"

using namespace std;

Component gameScreens::SettingsGameScreen::Render()
{
    string userName = gameManager->gameState.userName;
    int selectedLanguage = gameManager->gameState.activeLanguageId;

    Component userNameInput = Input(&userName, "Username (for leaderboards)");

    auto backButton = Button("Back", [&]() {
        this->gameManager->GoToMainMenu();
    });
    auto saveButton = Button("Save", [&]() {
        gameManager->gameState.userName = userName;
        gameManager->gameState.activeLanguageId = selectedLanguage;

        this->gameManager->GoToMainMenu();
    });

    vector<string> languagesList = {
     "RU",
     "EN"
    };
    auto languageRadioBox = Radiobox(&languagesList, &selectedLanguage);

    auto container = Container::Vertical({ backButton, saveButton, userNameInput, languageRadioBox });
    auto renderer = Renderer(container, [&] {
        this->Update();

        return WrapMainUI(
            vbox({
                text("SETTINGS") | center | focus,
                text("") | flex_grow,
                hbox({
                    text("Username:") | flex_shrink,
                    userNameInput->Render(),
                }) | center | border | color(Color::DarkSeaGreen1),
                filler(),
                hbox({
                    text("Language:") | flex_shrink,
                    languageRadioBox->Render(),
                }) | center | border | color(Color::DarkGoldenrod),
                text("") | flex_grow,
                hbox({
                    backButton->Render() | color(Color::BlueLight),
                    saveButton->Render() | color(Color::GreenLight)
                }) | center
            }) | flex
        );
    });

    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(renderer);

    return renderer;
}


void gameScreens::SettingsGameScreen::Update()
{

}