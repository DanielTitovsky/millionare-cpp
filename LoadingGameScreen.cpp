#include "LoadingGameScreen.h"
#include "LanguageHelper.h"
using namespace gameScreens;

void gameScreens::LoadingGameScreen::Update()
{
    loadingProgress += 0.02f;

    if (loadingProgress >= 1)
    {
        gameManager->GoToMainMenu();
    }
}

Component gameScreens::LoadingGameScreen::Render()
{
    auto container = Container::Vertical({ });
    auto renderer = Renderer(container, [&] {
        this->Update();

        return WrapMainUI(
            vbox({
                filler(),
                paragraphAlignCenter(LanguageHelper::Translit("Загрузка...")) | color(Color::Cyan),
                paragraphAlignCenter(LanguageHelper::Translit("Двигайте мышью чтобы ускорить загрузку")) | color(Color::Pink1),
                text(""),
                hbox({
                    filler(),
                    gauge(loadingProgress) | color(Color::Green3) | border,
                    filler()
                }),
                filler()
            })
        );
    });

    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(renderer);

    return renderer;
;}
