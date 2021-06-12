#pragma once
#include "clk/base/input.hpp"
#include "clk/base/output.hpp"
#include "clk/gui/widgets/viewer.hpp"
#include "clk/util/color_rgba.hpp"

#include <imnodes.h>
#include <memory>

namespace clk::gui::impl
{
class port_viewer
{
public:
	port_viewer() = delete;
	port_viewer(clk::port const* port, int id);
	port_viewer(port_viewer const&) = delete;
	port_viewer(port_viewer&&) noexcept = delete;
	auto operator=(port_viewer const&) -> port_viewer& = delete;
	auto operator=(port_viewer&&) noexcept -> port_viewer& = delete;
	virtual ~port_viewer() = default;

	auto id() const -> int;
	virtual auto port() const -> clk::port const* = 0;
	virtual void draw() = 0;
	auto position() const -> glm::vec2;

protected:
	int _id = -1; // NOLINT
	std::uint32_t _color; // NOLINT
	std::unique_ptr<clk::gui::viewer> _data_viewer; // NOLINT
	glm::vec2 _position; // NOLINT
};

class input_viewer final : public port_viewer
{
public:
	input_viewer() = delete;
	input_viewer(clk::input const* port, int id);
	input_viewer(input_viewer const&) = delete;
	input_viewer(input_viewer&&) noexcept = delete;
	auto operator=(input_viewer const&) -> input_viewer& = delete;
	auto operator=(input_viewer&&) noexcept -> input_viewer& = delete;
	~input_viewer() final = default;

	auto port() const -> clk::input const* final;
	void draw() final;

private:
	clk::input const* _port = nullptr;
};

class output_viewer final : public port_viewer
{
public:
	output_viewer() = delete;
	output_viewer(clk::output const* port, int id);
	output_viewer(output_viewer const&) = delete;
	output_viewer(output_viewer&&) noexcept = delete;
	auto operator=(output_viewer const&) -> output_viewer& = delete;
	auto operator=(output_viewer&&) noexcept -> output_viewer& = delete;
	~output_viewer() final = default;

	auto port() const -> clk::output const* final;
	void draw() final;

private:
	clk::output const* _port = nullptr;
};

inline port_viewer::port_viewer(clk::port const* port, int id)
	: _id(id)
	, _color(color_rgba(color_rgb::create_random(port->data_type_hash()), 1.0f).packed())
	, _data_viewer(clk::gui::viewer::create(port->data_type_hash(), port->data_pointer(), port->name()))
{
	_data_viewer->set_maximum_width(200);
}

inline auto port_viewer::id() const -> int
{
	return _id;
}

inline auto port_viewer::position() const -> glm::vec2
{
	return _position;
}

inline input_viewer::input_viewer(clk::input const* port, int id) : port_viewer(port, id), _port(port)
{
}

inline auto input_viewer::port() const -> clk::input const*
{
	return _port;
}

inline void input_viewer::draw()
{
	imnodes::PushColorStyle(imnodes::ColorStyle_Pin, _color);
	imnodes::PushColorStyle(imnodes::ColorStyle_PinHovered, _color);

	if(_port->is_connected())
		imnodes::BeginInputAttribute(_id, imnodes::PinShape_QuadFilled);
	else
		imnodes::BeginInputAttribute(_id, imnodes::PinShape_Quad);

	_data_viewer->update_data_pointer(_port->data_pointer());
	_data_viewer->draw();

	imnodes::EndInputAttribute();
	auto rect_min = glm::vec2(ImGui::GetItemRectMin());
	auto rect_max = glm::vec2(ImGui::GetItemRectMax());
	_position.y = (rect_min.y + rect_max.y) / 2;
	_position.x = rect_min.x;
	imnodes::PopColorStyle();
	imnodes::PopColorStyle();
}

inline output_viewer::output_viewer(clk::output const* port, int id) : port_viewer(port, id), _port(port)
{
}

inline auto output_viewer::port() const -> output const*
{
	return _port;
}

inline void output_viewer::draw()
{
	imnodes::PushColorStyle(imnodes::ColorStyle_Pin, _color);
	imnodes::PushColorStyle(imnodes::ColorStyle_PinHovered, _color);

	if(_port->is_connected())
		imnodes::BeginOutputAttribute(_id, imnodes::PinShape_TriangleFilled);
	else
		imnodes::BeginOutputAttribute(_id, imnodes::PinShape_Triangle);

	_data_viewer->draw();

	imnodes::EndOutputAttribute();

	auto rect_min = glm::vec2(ImGui::GetItemRectMin());
	auto rect_max = glm::vec2(ImGui::GetItemRectMax());
	_position.y = (rect_min.y + rect_max.y) / 2;
	_position.x = rect_max.x;

	imnodes::PopColorStyle();
	imnodes::PopColorStyle();
}

inline auto create_port_viewer(clk::port const* port, int id) -> std::unique_ptr<port_viewer>
{
	if(auto const* inputPort = dynamic_cast<clk::input const*>(port); inputPort != nullptr)
		return std::make_unique<input_viewer>(inputPort, id);
	else if(auto const* outputPort = dynamic_cast<clk::output const*>(port); outputPort != nullptr)
		return std::make_unique<output_viewer>(outputPort, id);
	return nullptr;
}

} // namespace clk::gui::impl