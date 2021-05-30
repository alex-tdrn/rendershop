#pragma once
#include <chrono>
#include <cmath>
#include <glm/glm.hpp>
#include <vector>

namespace clk::gui::impl
{
class layout_solver
{
public:
	struct node
	{
		int id = -1;
		std::vector<int> connected_nodes;
		glm::vec2 position = {0.0f, 0.0f};
		float mass = 1.0f;
		glm::vec2 velocity = {0.0f, 0.0f};
	};

	layout_solver() = default;
	layout_solver(layout_solver const&) = delete;
	layout_solver(layout_solver&&) = delete;
	auto operator=(layout_solver const&) -> layout_solver& = delete;
	auto operator=(layout_solver&&) -> layout_solver& = delete;
	~layout_solver() = default;

	void restart();
	void clear_nodes();
	void add_node(int id, glm::vec2 position, float mass, std::vector<int>&& connected_nodes);
	void step();
	auto get_results() -> std::vector<node>&;

private:
	using chrono = std::chrono::high_resolution_clock;
	chrono::time_point _last_step_execution = chrono::time_point::min();
	std::vector<node> _nodes;

	void apply_black_hole_forces();
	void apply_repulsion_forces();
	void apply_attraction_forces();
	void integrate();
};

inline void layout_solver::restart()
{
	_last_step_execution = chrono::time_point::min();
}

inline void layout_solver::clear_nodes()
{
	_nodes.clear();
}

inline void layout_solver::add_node(int id, glm::vec2 position, float mass, std::vector<int>&& connected_nodes)
{
	node _node;
	_node.id = id;
	_node.connected_nodes = std::move(connected_nodes);
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
	integrate();
}

inline auto layout_solver::get_results() -> std::vector<node>&
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

				bool connected = false;
				for(auto connected_id : node1->connected_nodes)
				{
					if(connected_id == node2->id)
					{
						connected = true;
						break;
					}
				}

				if(connected)
				{
					//	repulsion_force -= node1->mass * node2->mass * distance;
				}

				node1->velocity -= repulsion_force * node1_to_node2;
				node2->velocity += repulsion_force * node1_to_node2;
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