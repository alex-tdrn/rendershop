#pragma once

#include "clk/gui/panel.hpp"

#include <vector>

namespace clk::gui
{
class main_window
{
public:
	main_window() = default;
	main_window(main_window const&) = delete;
	main_window(main_window&&) = default;
	auto operator=(main_window const&) -> main_window& = delete;
	auto operator=(main_window&&) -> main_window& = default;
	~main_window() = default;

	void add_panel(clk::gui::panel&& panel);
	void draw();

private:
	std::vector<clk::gui::panel> _panels;
};
} // namespace clk::gui