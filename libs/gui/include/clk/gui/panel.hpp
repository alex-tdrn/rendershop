#pragma once

#include <imgui.h>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "clk/gui/widgets/widget.hpp"

namespace clk::gui
{
class panel final
{
public:
	panel() = default;
	explicit panel(std::unique_ptr<clk::gui::widget>&& widget);
	panel(std::unique_ptr<clk::gui::widget>&& widget, std::string_view title);
	panel(panel const& other);
	panel(panel&&) noexcept = default;
	auto operator=(panel const& other) -> panel&;
	auto operator=(panel&&) noexcept -> panel& = default;
	~panel() = default;

	void set_widget(std::unique_ptr<clk::gui::widget>&& widget);
	void draw();
	void set_title(std::string_view title);
	auto title() const -> std::string_view;
	auto visible() const -> bool;
	void toggle_visibility();
	void show();
	void hide();

private:
	std::unique_ptr<clk::gui::widget> _widget;
	std::string _title;
	bool _visible = true;
	ImGuiWindowFlags _flags = ImGuiWindowFlags_None;
};

} // namespace clk::gui