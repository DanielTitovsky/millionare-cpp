#pragma once

#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref

using namespace ftxui;

__interface IGameScreen
{
	virtual Component Render();
};

class GameScreenBase :
	public IGameScreen {

public:
	Element WrapMainUI(Element content) {
		return vbox({
			hbox({
				color(Color::Green3, paragraphAlignCenter("---------------------> MILLIONARE <---------------------"))
			}) | border,
			vbox({
				content | flex_grow,
			}) | border | flex
		});
	}

	virtual Component Render()
	{
		auto container = Container::Vertical({ });
		auto renderer = Renderer(container, [&] {
			return WrapMainUI(vbox({
					paragraphAlignCenter("Something wrong! Empty screen!")
			}));
		});

		auto screen = ScreenInteractive::Fullscreen();
		screen.Loop(renderer);

		return renderer;
	}

	void Sleep(int microseconds = 0) {
		std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
	}

};