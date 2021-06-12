#pragma once
#include "clk/base/graph.hpp"

#include <algorithm>
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
	struct node_representation
	{
		int id = -1;
		glm::vec2 position = {0.0f, 0.0f};
		float bounding_radius = 1.0f;
		float mass = 1.0f;
		glm::vec2 velocity = {0.0f, 0.0f};
	};
	struct port_representation
	{
		glm::vec2 position = {0.0f, 0.0f};
		std::size_t parent_node_index = 0;
		// does not contain all indices, only indices less than the index of the current port
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
	void step();
	auto get_results() -> const std::vector<node_representation>&;

private:
	using chrono = std::chrono::high_resolution_clock;
	chrono::time_point _last_step_execution = chrono::time_point::min();
	std::vector<node_representation> _nodes;
	std::vector<port_representation> _ports;

	constexpr static auto what_lerp_is_this(float ideal_distance, float distance) -> float;
	void apply_black_hole_forces();
	void apply_repulsion_forces();
	void apply_attraction_forces();
	void integrate();
};

template <typename T, typename U>
void layout_solver::update_cache(clk::graph const& graph, T& node_cache, U& port_cache)
{
	_nodes.clear();
	_ports.clear();
	std::unordered_map<int, std::size_t> port_id_to_index;
	for(auto const& node : graph)
	{
		auto id = node_cache.widget_for(node.get()).id();
		glm::vec2 dim = imnodes::GetNodeDimensions(id);
		glm::vec2 pos = imnodes::GetNodeGridSpacePos(id);
		pos += dim / 2.0f;

		node_representation n;
		n.id = id;
		n.position = pos;
		n.mass = dim.x * dim.y;
		n.bounding_radius = glm::length(dim) / 2.0f;
		_nodes.push_back(n);

		for(auto const& port : node->all_ports() | ranges::views::filter(&clk::port::is_connected))
		{
			port_representation p;
			auto const& widget = port_cache.widget_for(port);
			port_id_to_index[widget.id()] = _ports.size();
			p.position = widget.position();
			p.parent_node_index = _nodes.size() - 1;
			for(auto const& connected_port : port->connected_ports())
			{
				int connected_id = port_cache.widget_for(connected_port).id();
				// only add the connection if the index comes before the current port
				if(auto it = port_id_to_index.find(connected_id); it != port_id_to_index.end())
					p.connected_port_indices.push_back(it->second);
			}

			_ports.push_back(p);
		}
	}
}

inline void layout_solver::restart()
{
	_last_step_execution = chrono::time_point::min();
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

inline auto layout_solver::get_results() -> const std::vector<node_representation>&
{
	return _nodes;
}

inline constexpr auto layout_solver::what_lerp_is_this(float ideal_distance, float distance) -> float
{
	float force = ideal_distance - distance;
	return (force < 0 ? -1.0f : 1.0f) * force * force;
}

inline void layout_solver::apply_black_hole_forces()
{
	for(auto& node : _nodes)
	{
		auto direction = node.position;
		float distance = glm::length(direction);
		const float ideal_distance = 1000; // TODO, bounding radius for whole graph
		if(distance > ideal_distance)
		{
			direction /= distance;
			float force = what_lerp_is_this(ideal_distance, distance) * 100;

			node.velocity = force * direction;
		}
		else
		{
			node.velocity = glm::vec2{0.0f};
		}
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
			const float ideal_distance = node1->bounding_radius * 1.5f + node2->bounding_radius * 1.5f;
			if(distance < ideal_distance)
			{
				node1_to_node2 /= distance;
				float force = what_lerp_is_this(ideal_distance, distance) * 1000;

				node1->velocity -= force * node1_to_node2;
				node2->velocity += force * node1_to_node2;
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
			const float ideal_distance = 0;
			if(distance > 1)
			{
				port1_to_port2 /= distance;
				float force = what_lerp_is_this(ideal_distance, distance) * 100;

				node1.velocity -= force * port1_to_port2;
				node2.velocity += force * port1_to_port2;
			}
		}
	}
}

inline void layout_solver::integrate()
{
	auto current_time = chrono::now();

	float seconds_elapsed =
		std::chrono::duration_cast<std::chrono::duration<float>>(current_time - _last_step_execution).count();

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