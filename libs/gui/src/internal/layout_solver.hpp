#pragma once
#include "clk/base/graph.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <glm/glm.hpp>
#include <imgui.h>
#include <imnodes.h>
#include <vector>

namespace clk::gui::impl
{
class layout_solver
{
public:
	layout_solver() = default;
	layout_solver(layout_solver const&) = delete;
	layout_solver(layout_solver&&) = delete;
	auto operator=(layout_solver const&) -> layout_solver& = delete;
	auto operator=(layout_solver&&) -> layout_solver& = delete;
	~layout_solver() = default;

	template <typename T, typename U>
	void update_cache(clk::graph const& graph, T& node_cache, U& port_cache);
	void step();
	void set_time_multiplier(float multiplier);
	void set_gravity_distance_multiplier(float multiplier);
	void set_gravity_intensity_multiplier(float multiplier);
	void set_repulsion_distance_multiplier(float multiplier);
	void set_repulsion_intensity_multiplier(float multiplier);
	void set_attraction_distance_multiplier(float multiplier);
	void set_attraction_intensity_multiplier(float multiplier);

private:
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

	using chrono = std::chrono::high_resolution_clock;
	chrono::time_point _last_step_execution = chrono::time_point::min();
	std::vector<node_representation> _nodes;
	std::vector<port_representation> _ports;
	float _bounding_radius_graph = 1.0f;
	float _time_multiplier = 1.0f;
	float _gravity_distance_multiplier = 1.0f;
	float _gravity_intensity_multiplier = 1.0f;
	float _repulsion_distance_multiplier = 2.0f;
	float _repulsion_intensity_multiplier = 1.0f;
	float _attraction_distance_multiplier = 1.0f;
	float _attraction_intensity_multiplier = 1.0f;

	constexpr static auto calculate_force(float ideal_distance, float distance) -> float;
	void calculate_gravity();
	void calculate_repulsion();
	void calculate_attraction();
	void integrate();
	void write_out_results() const;
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
		n.mass = dim.x * dim.y / 100.0f;
		n.bounding_radius = glm::length(dim) / 2.0f;
		_nodes.push_back(n);
		_bounding_radius_graph += n.bounding_radius * n.bounding_radius;
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

	_bounding_radius_graph = std::sqrt(_bounding_radius_graph);
}

inline void layout_solver::step()
{
	if(_last_step_execution == chrono::time_point::min())
	{
		_last_step_execution = chrono::now();
		return;
	}

	calculate_gravity();
	calculate_repulsion();
	calculate_attraction();
	integrate();
	write_out_results();
}

inline void layout_solver::set_time_multiplier(float multiplier)
{
	_time_multiplier = multiplier;
}

inline void layout_solver::set_gravity_distance_multiplier(float multiplier)
{
	_gravity_distance_multiplier = multiplier;
}

inline void layout_solver::set_gravity_intensity_multiplier(float multiplier)
{
	_gravity_intensity_multiplier = multiplier;
}

inline void layout_solver::set_repulsion_distance_multiplier(float multiplier)
{
	_repulsion_distance_multiplier = multiplier;
}

inline void layout_solver::set_repulsion_intensity_multiplier(float multiplier)
{
	_repulsion_intensity_multiplier = multiplier;
}

inline void layout_solver::set_attraction_distance_multiplier(float multiplier)
{
	_attraction_distance_multiplier = multiplier;
}

inline void layout_solver::set_attraction_intensity_multiplier(float multiplier)
{
	_attraction_intensity_multiplier = multiplier;
}

inline constexpr auto layout_solver::calculate_force(float ideal_distance, float distance) -> float
{
	float force = ideal_distance - distance;
	return (force < 0 ? -1.0f : 1.0f) * force * force;
}

inline void layout_solver::calculate_gravity()
{
	for(auto& node : _nodes)
	{
		auto direction = node.position;
		float distance = glm::length(direction);
		const float ideal_distance = _bounding_radius_graph * _gravity_distance_multiplier;
		if(distance > ideal_distance)
		{
			direction /= distance;
			float force = calculate_force(ideal_distance, distance) * _gravity_intensity_multiplier;

			node.velocity = force * direction / node.mass;
		}
		else
		{
			node.velocity = glm::vec2{0.0f};
		}
	}
}

inline void layout_solver::calculate_repulsion()
{
	for(auto node1 = _nodes.begin(); node1 != _nodes.end(); ++node1)
	{
		for(auto node2 = node1 + 1; node2 != _nodes.end(); ++node2)
		{
			auto node1_to_node2 = node2->position - node1->position;
			float distance = glm::length(node1_to_node2);
			const float ideal_distance =
				(node1->bounding_radius + node2->bounding_radius) * _repulsion_distance_multiplier;
			if(distance < ideal_distance)
			{
				node1_to_node2 /= distance;
				float force = calculate_force(ideal_distance, distance) * _repulsion_intensity_multiplier;

				node1->velocity -= force * node1_to_node2 / node1->mass;
				node2->velocity += force * node1_to_node2 / node2->mass;
			}
		}
	}
}

inline void layout_solver::calculate_attraction()
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
			const float ideal_distance = _attraction_distance_multiplier;
			port1_to_port2 /= distance;
			float force = calculate_force(ideal_distance, distance) * _attraction_intensity_multiplier;

			node1.velocity -= force * port1_to_port2 / node1.mass;
			node2.velocity += force * port1_to_port2 / node2.mass;
		}
	}
}

inline void layout_solver::integrate()
{
	auto current_time = chrono::now();

	float seconds_elapsed =
		std::chrono::duration_cast<std::chrono::duration<float>>(current_time - _last_step_execution).count() *
		_time_multiplier;

	_last_step_execution = current_time;

	for(auto& node : _nodes)
	{
		auto position_difference = node.velocity * seconds_elapsed;
		if(glm::length(position_difference) > 0.1f)
			node.position += position_difference;
	}
}

inline void layout_solver::write_out_results() const
{
	for(auto const& node : _nodes)
	{
		glm::vec2 dim = imnodes::GetNodeDimensions(node.id);
		imnodes::SetNodeGridSpacePos(node.id, node.position - dim / 2.0f);
	}
}

} // namespace clk::gui::impl