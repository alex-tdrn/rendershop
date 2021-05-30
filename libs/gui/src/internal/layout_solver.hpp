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
		glm::vec2 position = {0.0f, 0.0f};
		float mass = 1.0f;
		glm::vec2 force = {0.0f, 0.0f};
		glm::vec2 acceleration = {0.0f, 0.0f};
		glm::vec2 velocity = {0.0f, 0.0f};
	};

	struct black_hole
	{
		glm::vec2 position = {0.0f, 0.0f};
		float mass = 10000000.0f;
	};

	layout_solver() = default;
	layout_solver(layout_solver const&) = delete;
	layout_solver(layout_solver&&) = delete;
	auto operator=(layout_solver const&) -> layout_solver& = delete;
	auto operator=(layout_solver&&) -> layout_solver& = delete;
	~layout_solver() = default;

	void restart();
	void add_black_hole(black_hole black_hole);
	void clear_nodes();
	void add_node(int id, glm::vec2 position, float mass);
	void step();
	auto get_results() -> std::vector<node>&;

private:
	using chrono = std::chrono::high_resolution_clock;
	chrono::time_point _last_step_execution = chrono::time_point::min();
	std::vector<black_hole> _black_holes = {black_hole{}};
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

inline void layout_solver::add_black_hole(black_hole black_hole)
{
	_black_holes.push_back(black_hole);
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

inline auto layout_solver::get_results() -> std::vector<node>&
{
	return _nodes;
}

inline void layout_solver::apply_black_hole_forces()
{
	for(auto const& black_hole : _black_holes)
	{
		for(auto& node : _nodes)
		{
			auto node_to_center = black_hole.position - node.position;
			float distance = glm::length(node_to_center);
			if(std::abs(distance) < 100.0f)
			{
				node.force = glm::vec2{0.0f};
			}
			else
			{
				node_to_center /= distance;
				node.force = node_to_center * (node.mass * black_hole.mass) / (distance * distance);
			}
		}
	}
}

inline void layout_solver::apply_repulsion_forces()
{
	// TODO
}

inline void layout_solver::apply_attraction_forces()
{
	// TODO
}

inline void layout_solver::integrate()
{
	// TODO
	auto current_time = chrono::now();

	float seconds_elapsed =
		std::chrono::duration_cast<std::chrono::duration<float>>(current_time - _last_step_execution).count();

	_last_step_execution = current_time;

	for(auto& node : _nodes)
	{
		node.acceleration = node.force / node.mass;
		node.velocity += node.acceleration * seconds_elapsed;
		node.position += node.velocity * seconds_elapsed;
	}
}

} // namespace clk::gui::impl