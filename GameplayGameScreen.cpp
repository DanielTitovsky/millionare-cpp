#include "GameplayGameScreen.h"
#include "MainMenuGameScreen.h"

Component gameScreens::GameplayGameScreen::Render()
{
    auto backButton = Button("Back", [&]() {
        this->gameManager->SetGameScreen(new MainMenuGameScreen(this->gameManager));
    });

    auto container = Container::Vertical({ backButton });
    auto renderer = Renderer(container, [&] {
        this->Update();

        return WrapMainUI(
            vbox({
                text("GAMEPLAY") | center,
                text("") | flex_grow,
                backButton->Render() | center
             }) | flex
        );
    });

    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(renderer);

    return renderer;
}


void gameScreens::GameplayGameScreen::Update()
{

}