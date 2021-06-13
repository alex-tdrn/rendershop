#include "clk/gui/panel.hpp"

#include <algorithm>
#include <iterator>

namespace clk::gui
{
panel::panel(std::unique_ptr<clk::gui::widget>&& widget) : _widget(std::move(widget)), _title(_widget->data_name())
{
}

panel::panel(std::unique_ptr<clk::gui::widget>&& widget, std::string_view title)
	: _widget(std::move(widget)), _title(std::string(title))
{
}

panel::panel(panel const& other)
{
	*this = other;
}

auto panel::operator=(panel const& other) -> panel&
{
	if(this != &other)
	{
		_title = "Copy of " + other._title;
		_visible = other._visible;
		_flags = other._flags;
		_widget = other._widget->clone();
	}
	return *this;
}

void panel::set_widget(std::unique_ptr<clk::gui::widget>&& widget)
{
	_widget = std::move(widget);
}

void panel::draw()
{
	if(!_visible)
		return;
	ImGui::PushID(this);
	if(ImGui::Begin(_title.c_str(), &_visible, _flags))
		_widget->draw();
	ImGui::End();
	ImGui::PopID();
}

void panel::set_title(std::string_view title)
{
	if(title.empty() && _widget != nullptr)
		_title = _widget->data_name();
	else
		_title = std::string(title);
}

auto panel::title() const -> std::string_view
{
	return _title;
}

auto panel::visible() const -> bool
{
	return _visible;
}

void panel::toggle_visibility()
{
	_visible = !_visible;
}

void panel::show()
{
	_visible = true;
}

void panel::hide()
{
	_visible = false;
}

} // namespace clk::gui