#pragma once

#include <chrono>
#include <imgui.h>

namespace clk::gui
{
using namespace std::chrono_literals;

class performance_overlay
{
public:
	performance_overlay();
	performance_overlay(performance_overlay const&) = default;
	performance_overlay(performance_overlay&&) = default;
	auto operator=(performance_overlay const&) -> performance_overlay& = default;
	auto operator=(performance_overlay&&) -> performance_overlay& = default;
	~performance_overlay() = default;

	void set_frame_samples(int count);
	void set_plot_height(float height);
	void record_frame();
	void draw();

private:
	int _frame_samples = 0;
	unsigned int _current_frame_index = 0;
	std::chrono::high_resolution_clock::time_point _last_frame = std::chrono::high_resolution_clock::now();
	std::vector<std::chrono::nanoseconds> _frametimes;
	std::chrono::nanoseconds _average_frametime = 0ns;
	std::chrono::nanoseconds _longest_frametime = 100ms;

	float _plot_height = 100;

	template <typename T, typename Ratio>
	static auto print_duration(std::chrono::duration<T, Ratio> duration) -> std::string;
};

inline performance_overlay::performance_overlay()
{
	set_frame_samples(200);
}

inline void performance_overlay::set_frame_samples(int count)
{
	_frame_samples = count;
	_frametimes.resize(_frame_samples);
}

inline void performance_overlay::set_plot_height(float height)
{
	_plot_height = height;
}

inline void performance_overlay::record_frame()
{
	auto currentFrame = std::chrono::steady_clock::now();

	_current_frame_index = (_current_frame_index + 1) % _frame_samples;

	std::chrono::nanoseconds currentFrametime = currentFrame - _last_frame;

	_average_frametime -= _frametimes[_current_frame_index] / _frame_samples;
	if(_longest_frametime == _frametimes[_current_frame_index])
		_longest_frametime = 100ms;
	_frametimes[_current_frame_index] = currentFrametime;
	_average_frametime += _frametimes[_current_frame_index] / _frame_samples;
	if(currentFrametime > _longest_frametime)
		_longest_frametime = currentFrametime;

	_last_frame = currentFrame;
}

inline void performance_overlay::draw()
{
	ImGui::Text("Total Frametime: %s", print_duration(_frametimes[_current_frame_index]).data());
	ImGui::Text("Average: %s", print_duration(_average_frametime).data());
	ImGui::Text("Longest: %s", print_duration(_longest_frametime).data());
	ImGui::PlotLines("###Frametimes",
		[](void* data, int idx) -> float {
			return static_cast<float>(static_cast<std::chrono::nanoseconds*>(data)[idx].count()); // NOLINT
		},
		_frametimes.data(), _frame_samples, static_cast<int>(_current_frame_index), nullptr, 0.0f,
		static_cast<float>(_longest_frametime.count()), {ImGui::GetContentRegionAvailWidth(), _plot_height});
}

template <typename T, typename Ratio>
auto performance_overlay::print_duration(std::chrono::duration<T, Ratio> duration) -> std::string
{
	static int const threshold = 1'000;
	if constexpr(std::is_same_v<Ratio, std::nano>)
	{
		if(duration.count() < threshold)
			return std::to_string(duration.count()) + "ns";
		else
			return print_duration(std::chrono::duration_cast<std::chrono::microseconds>(duration));
	}
	else if constexpr(std::is_same_v<Ratio, std::micro>)
	{
		if(duration.count() < threshold)
			return std::to_string(duration.count()) + "us";
		else
			return print_duration(std::chrono::duration_cast<std::chrono::milliseconds>(duration));
	}
	else if constexpr(std::is_same_v<Ratio, std::milli>)
	{
		if(duration.count() < threshold)
			return std::to_string(duration.count()) + "ms";
		else
			return print_duration(std::chrono::duration_cast<std::chrono::seconds>(duration));
	}
	else if constexpr(std::is_same_v<Ratio, std::ratio<1, 1>>)
	{
		return std::to_string(duration.count()) + "s";
	}
}
} // namespace clk::gui