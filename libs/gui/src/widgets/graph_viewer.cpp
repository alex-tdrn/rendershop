#include "clk/gui/widgets/graph_viewer.hpp"

#include "clk/base/node.hpp"
#include "clk/base/port.hpp"
#include "layout_solver.hpp"
#include "node_viewers.hpp"
#include "port_viewers.hpp"
#include "selection_manager.hpp"
#include "widget_cache.hpp"

namespace clk::gui
{
graph_viewer::graph_viewer(clk::graph const* data, std::string_view data_name)
	: viewer_of<clk::graph>(data, data_name)
	, _node_cache(
		  std::make_unique<impl::widget_cache<clk::node const, impl::node_viewer>>([&](node const* node, int id) {
			  return impl::create_node_viewer(node, id, _port_cache.get());
		  }))
	, _port_cache(std::make_unique<impl::widget_cache<clk::port const, impl::port_viewer>>(&impl::create_port_viewer))
	, _selection_manager(std::make_unique<impl::selection_manager<true>>(_node_cache.get(), _port_cache.get()))
	, _layout_solver(std::make_unique<impl::layout_solver>())

{
	disable_title();
	_context = imnodes::EditorContextCreate();
	imnodes::EditorContextSet(_context);

	imnodes::EditorContextSet(nullptr);
}

graph_viewer::~graph_viewer()
{
	imnodes::EditorContextFree(_context);
}

auto graph_viewer::clone() const -> std::unique_ptr<widget>
{
	return std::make_unique<graph_viewer>(data(), data_name());
}

void graph_viewer::draw_contents() const
{
	imnodes::EditorContextSet(_context);

	draw_graph();
	_selection_manager->update();

	imnodes::EditorContextSet(nullptr);
}

void graph_viewer::draw_graph() const
{
	_connections.clear();

	imnodes::BeginNodeEditor();

	for(auto const& node : *data())
	{
		_node_cache->widget_for(node.get()).draw();
		for(auto* output : node->outputs())
			for(auto* input : output->connected_inputs())
				if(_port_cache->has_widget_for(input))
					_connections.emplace_back(std::make_pair(input, output));
	}

	{
		int linkID = 0;
		for(auto& connection : _connections)
		{
			auto color = color_rgba(color_rgb::create_random(connection.first->data_type_hash()), 1.0f).packed();
			imnodes::PushColorStyle(imnodes::ColorStyle_Link, color);
			imnodes::Link(linkID++, _port_cache->widget_for(connection.first).id(),
				_port_cache->widget_for(connection.second).id());
			imnodes::PopColorStyle();
		}
	}

	run_layout_solver();

	imnodes::EndNodeEditor();
}

void graph_viewer::run_layout_solver() const
{
	// TODO don't run this every frame

	_layout_solver->clear_nodes();
	for(auto const& node : *data())
	{
		auto id = _node_cache->widget_for(node.get()).id();
		_layout_solver->add_node(id, imnodes::GetNodeGridSpacePos(id), imnodes::GetNodeDimensions(id));
	}

	_layout_solver->step();

	for(auto const& result : _layout_solver->get_results())
		imnodes::SetNodeGridSpacePos(result.id, result.position);
}

} // namespace clk::gui