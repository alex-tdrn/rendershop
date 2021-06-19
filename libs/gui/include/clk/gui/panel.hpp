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
	friend void draw();

public:
	enum class action_type
	{
		duplicate,
		remove
	};

	panel();
	explicit panel(std::unique_ptr<clk::gui::widget>&& widget);
	panel(std::unique_ptr<clk::gui::widget>&& widget, std::string_view title);
	panel(panel const& other);
	panel(panel&&) noexcept;
	auto operator=(panel const& other) -> panel&;
	auto operator=(panel&&) noexcept -> panel&;
	~panel();

	auto operator==(panel const& other) const -> bool;

	void queue(action_type action_type) const;
	void remove();
	void set_widget(std::unique_ptr<clk::gui::widget>&& widget);
	void draw();
	void set_title(std::string_view title);
	auto title() const -> std::string_view;
	auto visible() const -> bool;
	void toggle_visibility();
	void show();
	void hide();
	void toggle_title_bar();
	void show_title_bar();
	void hide_title_bar();
	auto title_bar_visible() const -> bool;

private:
	inline static std::vector<panel*> _all_panels; // NOLINT
	inline static std::vector<panel> _orphaned_panels; // NOLINT
	inline static std::vector<std::pair<int, action_type>> _queued_actions; // NOLINT

	int _id = generate_id();
	std::unique_ptr<clk::gui::widget> _widget;
	std::string _title_with_id;
	std::string _title;
	bool _visible = true;
	ImGuiWindowFlags _flags = ImGuiWindowFlags_None;
	float _opacity = 1.0f;

	static auto generate_id() -> int;

	void register_self();
	void deregister_self();
	void update_title_with_id();
	void handle_context_menu();
	void handle_key_presses();
};

} // namespace clk::gui