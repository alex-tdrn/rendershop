#pragma once

#include "clk/base/graph.hpp"
#include "clk/gui/widgets/viewer.hpp"

#include <imnodes.h>

namespace clk::gui::impl
{
template <typename data, typename widget>
class widget_cache;
class node_viewer;
class port_viewer;
template <bool const_data>
class selection_manager;
class layout_solver;
} // namespace clk::gui::impl

namespace clk::gui
{
class graph_viewer final : public viewer_of<clk::graph>
{
public:
	graph_viewer() = delete;
	graph_viewer(clk::graph const* data, std::string_view data_name);
	graph_viewer(graph_viewer const&) = delete;
	graph_viewer(graph_viewer&&) = delete;
	auto operator=(graph_viewer const&) -> graph_viewer& = delete;
	auto operator=(graph_viewer&&) -> graph_viewer& = delete;
	~graph_viewer() final;

	auto clone() const -> std::unique_ptr<clk::gui::widget> final;
	void draw_contents() const final;

private:
	mutable bool _first_draw = true;
	imnodes::EditorContext* _context;
	std::unique_ptr<impl::widget_cache<clk::node const, impl::node_viewer>> _node_cache;
	std::unique_ptr<impl::widget_cache<clk::port const, impl::port_viewer>> _port_cache;
	mutable std::vector<std::pair<clk::input const*, clk::output const*>> _connections;
	std::unique_ptr<impl::selection_manager<true>> _selection_manager;
	std::unique_ptr<impl::layout_solver> _layout_solver;

	void draw_graph() const;
	void run_layout_solver() const;
};

} // namespace clk::gui