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
	struct node_representation
	{
		int id = -1;
		glm::vec2 position = {0.0f, 0.0f};
		glm::vec2 size = {1.0f, 1.0f};
		float mass = {1.0f};
		glm::vec2 force = {0.0f, 0.0f};
		glm::vec2 acceleration = {0.0f, 0.0f};
		glm::vec2 velocity = {0.0f, 0.0f};
	};

	layout_solver() = default;
	layout_solver(layout_solver const&) = delete;
	layout_solver(layout_solver&&) = delete;
	auto operator=(layout_solver const&) -> layout_solver& = delete;
	auto operator=(layout_solver&&) -> layout_solver& = delete;
	~layout_solver() = default;

	void restart();
	void set_center(glm::vec2 center);
	void clear_nodes();
	void add_node(int id, glm::vec2 position, glm::vec2 size);
	void step();
	auto get_results() -> std::vector<node_representation> const&;

private:
	using chrono = std::chrono::high_resolution_clock;
	chrono::time_point _last_step_execution = chrono::time_point::min();
	glm::vec2 _center = glm::vec2{0.0f, 0.0f};
	std::vector<node_representation> _nodes;

	void add_gravity_forces();
	void add_repulsion_forces();
	void add_attraction_forces();
	void integrate();
};

inline void layout_solver::restart()
{
	_last_step_execution = chrono::time_point::min();
}

inline void layout_solver::set_center(glm::vec2 center)
{
	_center = center;
}

inline void layout_solver::clear_nodes()
{
	_nodes.clear();
}

inline void layout_solver::add_node(int id, glm::vec2 position, glm::vec2 size)
{
	node_representation _node;
	_node.id = id;
	_node.position = position;
	_node.size = size;
	_node.mass = size.x * size.y;
	_nodes.push_back(_node);
}

inline void layout_solver::step()
{
	if(_last_step_execution == chrono::time_point::min())
	{
		_last_step_execution = chrono::now();
		return;
	}
	add_gravity_forces();
	add_repulsion_forces();
	add_attraction_forces();
	integrate();
}

inline auto layout_solver::get_results() -> std::vector<node_representation> const&
{
	return _nodes;
}

inline void layout_solver::add_gravity_forces()
{
	// TODO
}

inline void layout_solver::add_repulsion_forces()
{
	// TODO
}

inline void layout_solver::add_attraction_forces()
{
	// TODO
}

inline void layout_solver::integrate()
{
	// TODO
	float t = static_cast<float>(
		std::chrono::duration_cast<std::chrono::duration<float>>(chrono::now().time_since_epoch()).count());
	for(auto& node : _nodes)
	{
		node.position += 20000.0f / node.mass * glm::vec2{std::cos(t), std::sin(t)};
	}
}

} // namespace clk::gui::impl