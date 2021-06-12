#pragma once
#include "clk/base/graph.hpp"

#include <chrono>
#include <cmath>
#include <glm/glm.hpp>
#include <imnodes.h>
#include <vector>

namespace clk::gui::impl
{
class layout_solver
{
public:
	struct node
	{
		int id = -1;
		glm::vec2 position = {0.0f, 0.0f};
		float mass = 1.0f;
		glm::vec2 velocity = {0.0f, 0.0f};
	};
	struct port
	{
		int id = -1;
		glm::vec2 position = {0.0f, 0.0f};
		std::size_t parent_node_index = 0;
		std::vector<std::size_t> connected_port_indices;
	};

	layout_solver() = default;
	layout_solver(layout_solver const&) = delete;
	layout_solver(layout_solver&&) = delete;
	auto operator=(layout_solver const&) -> layout_solver& = delete;
	auto operator=(layout_solver&&) -> layout_solver& = delete;
	~layout_solver() = default;

	template <typename T, typename U>
	void update_cache(clk::graph const& graph, T& node_cache, U& port_cache);
	void restart();
	void clear_nodes();
	void add_node(int id, glm::vec2 position, float mass);
	void step();
	auto get_results() -> const std::vector<node>&;

private:
	using chrono = std::chrono::high_resolution_clock;
	chrono::time_point _last_step_execution = chrono::time_point::min();
	std::vector<node> _nodes;
	std::vector<port> _ports;

	void apply_black_hole_forces();
	void apply_repulsion_forces();
	void apply_attraction_forces();
	void integrate();
};

template <typename T, typename U>
void layout_solver::update_cache(clk::graph const& graph, T& node_cache, U& port_cache)
{
	clear_nodes();
	for(auto const& node : graph)
	{
		auto id = node_cache.widget_for(node.get()).id();
		glm::vec2 dim = imnodes::GetNodeDimensions(id);
		glm::vec2 pos = imnodes::GetNodeGridSpacePos(id);
		pos += dim / 2.0f;

		add_node(id, pos, dim.x * dim.y);
	}
}

inline void layout_solver::restart()
{
	_last_step_execution = chrono::time_point::min();
}

inline void layout_solver::clear_nodes()
{
	_nodes.clear();
}

inline void layout_solver::add_node(int id, glm::vec2 position, float mass)
{
	node _node;
	_node.id = id;
	_node.position = position;
	_node.mass = mass;
	_nodes.push_back(_node);
}

inline void layout_solver::step()
{
	if(_last_step_execution == chrono::time_point::min())
	{
		_last_step_execution = chrono::now();
		return;
	}
	apply_black_hole_forces();
	apply_repulsion_forces();
	apply_attraction_forces();
	integrate();
}

inline auto layout_solver::get_results() -> const std::vector<node>&
{
	return _nodes;
}

inline void layout_solver::apply_black_hole_forces()
{
	for(auto& node : _nodes)
	{
		if(glm::length(node.position) > 1)
			node.velocity = -node.position * 100.0f;
		else
			node.velocity = glm::vec2{0.0f};
	}
}

inline void layout_solver::apply_repulsion_forces()
{
	for(auto node1 = _nodes.begin(); node1 != _nodes.end(); ++node1)
	{
		for(auto node2 = node1 + 1; node2 != _nodes.end(); ++node2)
		{
			auto node1_to_node2 = node2->position - node1->position;
			float distance = glm::length(node1_to_node2);
			if(distance > 1)
			{
				node1_to_node2 /= distance;
				float repulsion_force = node1->mass * node2->mass / (distance * distance);

				node1->velocity -= repulsion_force * node1_to_node2;
				node2->velocity += repulsion_force * node1_to_node2;
			}
		}
	}
}

inline void layout_solver::apply_attraction_forces()
{
	for(auto const& port1 : _ports)
	{
		auto& node1 = _nodes[port1.parent_node_index];
		for(std::size_t port2_index : port1.connected_port_indices)
		{
			auto const& port2 = _ports[port2_index];
			auto& node2 = _nodes[port2.parent_node_index];

			auto port1_to_port2 = port2.position - port1.position;
			float distance = glm::length(port1_to_port2);
			if(distance > 1)
			{
				port1_to_port2 /= distance;
				float attraction_force = node1.mass * node2.mass / (distance * distance);

				node1.velocity -= attraction_force * port1_to_port2;
				node2.velocity += attraction_force * port1_to_port2;
			}
		}
	}
}

inline void layout_solver::integrate()
{
	// TODO
	auto current_time = chrono::now();

	float seconds_elapsed =
		std::chrono::duration_cast<std::chrono::duration<float>>(current_time - _last_step_execution).count();

	seconds_elapsed *= 1000;
	_last_step_execution = current_time;

	for(auto& node : _nodes)
	{
		node.velocity /= node.mass;
		auto position_difference = node.velocity * seconds_elapsed;
		if(glm::length(position_difference) > 0.1f)
			node.position += position_difference;
	}
}

} // namespace clk::gui::impl