#pragma once
#include "clk/base/input.hpp"
#include "clk/base/output.hpp"
#include "clk/gui/widgets/editor.hpp"
#include "clk/gui/widgets/viewer.hpp"
#include "clk/util/color_rgba.hpp"

#include <imnodes.h>
#include <memory>

namespace clk::gui::impl
{
class port_editor
{
public:
	port_editor() = delete;
	port_editor(clk::port* port, int id);
	port_editor(port_editor const&) = delete;
	port_editor(port_editor&&) noexcept = delete;
	auto operator=(port_editor const&) -> port_editor& = delete;
	auto operator=(port_editor&&) noexcept -> port_editor& = delete;
	virtual ~port_editor() = default;

	auto id() const -> int;
	auto color() const -> std::uint32_t;
	void set_enabled(bool enabled);
	void set_stable_height(bool stable_height);
	virtual auto port() const -> port* = 0;
	virtual void draw(clk::gui::widget* override_widget = nullptr) = 0;

protected:
	int _id = -1; // NOLINT
	std::uint32_t _color; // NOLINT
	std::unique_ptr<clk::gui::viewer> _data_viewer; // NOLINT
	bool _enabled = true; // NOLINT
	bool _stable_height = false; // NOLINT
};

class input_editor final : public port_editor
{
public:
	input_editor() = delete;
	input_editor(clk::input* port, int id);
	input_editor(input_editor const&) = delete;
	input_editor(input_editor&&) noexcept = delete;
	auto operator=(input_editor const&) -> input_editor& = delete;
	auto operator=(input_editor&&) noexcept -> input_editor& = delete;
	~input_editor() final = default;

	auto port() const -> input* final;
	void draw(clk::gui::widget* override_widget = nullptr) final;

private:
	clk::input* _port = nullptr;
	std::unique_ptr<clk::gui::editor> _default_data_editor;
};

class output_editor final : public port_editor
{
public:
	output_editor() = delete;
	output_editor(clk::output* port, int id);
	output_editor(output_editor const&) = delete;
	output_editor(output_editor&&) noexcept = delete;
	auto operator=(output_editor const&) -> output_editor& = delete;
	auto operator=(output_editor&&) noexcept -> output_editor& = delete;
	~output_editor() final = default;

	auto port() const -> output* final;
	void draw(clk::gui::widget* override_widget = nullptr) final;

private:
	clk::output* _port = nullptr;
};

inline port_editor::port_editor(clk::port* port, int id)
	: _id(id)
	, _color(color_rgba(color_rgb::create_random(port->data_type_hash()), 1.0f).packed())
	, _data_viewer(clk::gui::viewer::create(port->data_type_hash(), port->data_pointer(), port->name()))
{
	_data_viewer->set_maximum_width(200);
}

inline auto port_editor::id() const -> int
{
	return _id;
}

inline auto port_editor::color() const -> std::uint32_t
{
	return _color;
}

inline void port_editor::set_enabled(bool enabled)
{
	_enabled = enabled;
}

inline void port_editor::set_stable_height(bool stable_height)
{
	_stable_height = stable_height;
}

inline input_editor::input_editor(clk::input* port, int id) : port_editor(port, id), _port(port)
{
	auto* default_port = &port->default_port();

	_default_data_editor =
		clk::gui::editor::create(default_port->data_type_hash(), default_port->data_pointer(), port->name(), [=]() {
			default_port->update_timestamp();
			default_port->push();
		});
	_default_data_editor->set_maximum_width(200);
}

inline auto input_editor::port() const -> input*
{
	return _port;
}

inline void input_editor::draw(clk::gui::widget* override_widget)
{
	ImNodes::PushColorStyle(ImNodesCol_Pin, _color);

	float const begin_y = ImGui::GetCursorPosY();

	if(!_enabled)
		ImNodes::BeginStaticAttribute(_id);
	else
		ImNodes::BeginInputAttribute(_id, ImNodesPinShape_QuadFilled);

	if(override_widget != nullptr)
	{
		override_widget->draw();
	}
	else
	{
		if(!_port->is_connected())
		{
			_default_data_editor->draw();
		}
		else
		{
			_data_viewer->update_data_pointer(_port->data_pointer());
			_data_viewer->draw();
		}

		if(_stable_height)
		{
			float current_height = ImGui::GetCursorPosY() - begin_y;
			float max_height = std::max(_data_viewer->last_size().y, _default_data_editor->last_size().y);
			if(current_height < max_height)
				ImGui::Dummy(ImVec2(10, max_height - current_height));
		}
	}

	if(!_enabled)
		ImNodes::EndStaticAttribute();
	else
		ImNodes::EndInputAttribute();

	ImNodes::PopColorStyle();
}

inline output_editor::output_editor(clk::output* port, int id) : port_editor(port, id), _port(port)
{
}

inline auto output_editor::port() const -> output*
{
	return _port;
}

inline void output_editor::draw(clk::gui::widget* override_widget)
{
	ImNodes::PushColorStyle(ImNodesCol_Pin, _color);

	if(!_enabled)
		ImNodes::BeginStaticAttribute(_id);
	else
		ImNodes::BeginOutputAttribute(_id, ImNodesPinShape_TriangleFilled);

	if(override_widget != nullptr)
		override_widget->draw();
	else
		_data_viewer->draw();

	if(!_enabled)
		ImNodes::EndStaticAttribute();
	else
		ImNodes::EndOutputAttribute();

	ImNodes::PopColorStyle();
}

inline auto create_port_editor(clk::port* port, int id) -> std::unique_ptr<port_editor>
{
	if(auto* input = dynamic_cast<clk::input*>(port); input != nullptr)
		return std::make_unique<input_editor>(input, id);
	else if(auto* output = dynamic_cast<clk::output*>(port); output != nullptr)
		return std::make_unique<output_editor>(output, id);
	return nullptr;
}

} // namespace clk::gui::impl