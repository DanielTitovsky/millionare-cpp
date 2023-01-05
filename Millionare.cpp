#include <iostream>
#include <fstream>
#include "GameManager.h"
#include "LanguageHelper.h"

int main()
{
    GameManager game;
    game.Bootstrap();

    using namespace ftxui;
    using namespace std;

    /*  auto container = Container::Horizontal({});

      auto renderer = Renderer(container, [&] {
          return
              vbox({
                  filler(),
                  text("TEST") | color(Color::Green) | border | center | bold,
                  filler()
                  }) | border;
          });

      auto screen = ScreenInteractive::Fullscreen();
      screen.Loop(renderer);*/

      /* auto buttons = Container::Horizontal({
            Button("Menu", [&] {}, ButtonOption::Animated(Color::Red)) ,
            Button("Next", [&] {}, ButtonOption::Animated(Color::Green)),
               });
           auto component = Renderer(buttons, [&] {

               return vbox({ buttons->Render(), }) | border ;

               });
           auto screen = ScreenInteractive::FitComponent();
           screen.Loop(component);
           return 0;*/
//
//   auto button1 = Button("Menu", [&] {}, ButtonOption::Animated(Color::Red));
//    auto button2 = Button("Next", [&] {}, ButtonOption::Animated(Color::Green));
//
//    auto buttons = Container::Horizontal({ button1 , button2 });
//
//    auto component = Renderer(buttons, [&] {
//        return vbox({
//            hbox({
//                button1->Render(),
//                filler(),
//            }),  
//            filler(),
//            hbox({
//                text("fsdfsdfsdfgsdgasdgasdgasdgasdgasd") | center | borderDouble,
//            }) | center,
//            filler(),
//            hbox({
//             filler(),
//             button2->Render(),
//            }),
//        });
//    });
//    auto screen = ScreenInteractive::Fullscreen();
//    screen.Loop(component);
//    return 0;
}

    






