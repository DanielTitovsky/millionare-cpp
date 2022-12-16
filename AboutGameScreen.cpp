#include "AboutGameScreen.h"
#include "MainMenuGameScreen.h"

using namespace std;

Component gameScreens::AboutGameScreen::Render()
{
    string aboutText = "Football, also called association football or soccer, is a game involving two teams of 11 players who try to maneuver the ball into the other team's goal without using their hands or arms. The team that scores more goals wins. Football is the world's most popular ball game in numbers of participants and spectators.";
    
    auto backButton = Button("Back", [&]() {
        this->gameManager->SetGameScreen(new MainMenuGameScreen(this->gameManager));
    });

    auto container = Container::Vertical({ backButton });
    auto renderer = Renderer(container, [&] {
        this->Update();

        return WrapMainUI(
            vbox({
                window(text("ABOUT") | center | color(Color::Gold1),
                    vbox({
                        paragraphAlignCenter(aboutText)
                    }) | size(WIDTH, EQUAL, 30) | center
                ) | size(WIDTH, EQUAL, 50) | center,
                text("") | flex_grow,
                separator(),
                backButton->Render() | center
            }) | flex
        );
    });
    
    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(renderer);

    return renderer;
}


void gameScreens::AboutGameScreen::Update()
{

}