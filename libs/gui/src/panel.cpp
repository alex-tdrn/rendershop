#include "clk/gui/panel.hpp"

#include <imgui_stdlib.h>
#include <range/v3/algorithm.hpp>

namespace clk::gui
{
panel::panel() : _title("Unnamed panel")
{
	update_title_with_id();
	register_self();
}

panel::panel(std::unique_ptr<clk::gui::widget>&& widget) : _widget(std::move(widget)), _title(_widget->data_name())
{
	update_title_with_id();
	register_self();
}

panel::panel(std::unique_ptr<clk::gui::widget>&& widget, std::string_view title)
	: _widget(std::move(widget)), _title(std::string(title))
{
	update_title_with_id();
	register_self();
}

panel::panel(panel const& other)
{
	*this = other;
	update_title_with_id();
	register_self();
}

panel::panel(panel&& other) noexcept
{
	*this = std::move(other);
	update_title_with_id();
	register_self();
}

auto panel::operator=(panel const& other) -> panel&
{
	if(this != &other)
	{
		_title = "Copy of " + other._title;
		_visible = other._visible;
		_flags = other._flags;
		_widget = other._widget->clone();
		update_title_with_id();
	}
	return *this;
}

auto panel::operator=(panel&& other) noexcept -> panel&
{
	std::swap(_id, other._id);
	std::swap(_widget, other._widget);
	std::swap(_title_with_id, other._title_with_id);
	std::swap(_title, other._title);
	std::swap(_visible, other._visible);
	std::swap(_flags, other._flags);
	std::swap(_opacity, other._opacity);

	return *this;
}

panel::~panel()
{
	deregister_self();
}

auto panel::operator==(panel const& other) const -> bool
{
	return this->_id == other._id;
}

void panel::queue(action_type action_type) const
{
	_queued_actions.emplace_back(_id, action_type);
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
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, _opacity);
	if(ImGui::Begin(_title_with_id.c_str(), &_visible, _flags))
	{
		handle_context_menu();
		handle_key_presses();
		_widget->draw();
	}
	ImGui::End();
	ImGui::PopStyleVar();
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

void panel::toggle_title_bar()
{
	if(title_bar_visible())
		hide_title_bar();
	else
		show_title_bar();
}

void panel::show_title_bar()
{
	_flags &= ~ImGuiWindowFlags_NoTitleBar;
}

void panel::hide_title_bar()
{
	_flags |= ImGuiWindowFlags_NoTitleBar;
}

auto panel::title_bar_visible() const -> bool
{
	return (_flags & ImGuiWindowFlags_NoTitleBar) == 0;
}

auto panel::generate_id() -> int
{
	static int next_available_id = 0;
	return next_available_id++;
}

void panel::register_self()
{
	_all_panels.push_back(this);
}

void panel::deregister_self()
{
	_all_panels.erase(ranges::remove(_all_panels, this), _all_panels.end());
}

void panel::update_title_with_id()
{
	_title_with_id = _title + "###" + std::to_string(_id);
}

void panel::handle_context_menu()
{
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.0f);
	if(ImGui::BeginPopupContextItem("Context menu"))
	{
		ImGui::InputText(
			"Rename", &_title, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CallbackAlways,
			[](ImGuiInputTextCallbackData* data) -> int {
				auto* panel = static_cast<clk::gui::panel*>(data->UserData);
				panel->update_title_with_id();
				return 0;
			},
			this);

		ImGui::SliderFloat("Opacity", &_opacity, 0.05f, 1.0f, "%.2f");
		if(title_bar_visible())
		{
			if(ImGui::MenuItem("Hide Title Bar"))
			{
				hide_title_bar();
			}
		}
		else
		{
			if(ImGui::MenuItem("Show Title Bar"))
			{
				show_title_bar();
			}
		}
		if(ImGui::MenuItem("Duplicate"))
			queue(action_type::duplicate);

		if(ImGui::MenuItem("Delete"))
			queue(action_type::remove);

		ImGui::EndPopup();
	}

	ImGui::PopStyleVar();
}

void panel::handle_key_presses()
{
	if(ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows))
	{
		if(ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Tab)))
		{
			toggle_title_bar();
		}
	}
}

} // namespace clk::gui