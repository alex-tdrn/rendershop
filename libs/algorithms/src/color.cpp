#include "clk/algorithms/color.hpp"

namespace clk::algorithms
{
add_colors::add_colors()
{
	register_port(_color_a);
	register_port(_color_b);
	register_port(_result);
}

void add_colors::update()
{
	*_result = *_color_a + *_color_b;
}

subtract_colors::subtract_colors()
{
	register_port(_color_a);
	register_port(_color_b);
	register_port(_result);
}

void subtract_colors::update()
{
	*_result = *_color_a - *_color_b;
}

multiply_colors::multiply_colors()
{
	register_port(_color_a);
	register_port(_color_b);
	register_port(_result);
}

void multiply_colors::update()
{
	*_result = *_color_a * *_color_b;
}

divide_colors::divide_colors()
{
	register_port(_color_a);
	register_port(_color_b);
	register_port(_result);
}

void divide_colors::update()
{
	if(_color_b->r() != 0 && _color_b->g() != 0 && _color_b->b() != 0)
		*_result = *_color_a / *_color_b;
}

decompose_color::decompose_color()
{
	register_port(_color);
	register_port(_red_component);
	register_port(_green_component);
	register_port(_blue_component);
}

void decompose_color::update()
{
	*_red_component = _color->r() * 100;
	*_green_component = _color->g() * 100;
	*_blue_component = _color->b() * 100;
}

grayscale::grayscale()
{
	register_port(_input_color);
	register_port(_output_color);
}

void grayscale::update()
{
	const glm::vec3 linear_grayscale = glm::vec3(0.2126, 0.7152, 0.0722);
	*_output_color = clk::color_rgb(glm::dot(linear_grayscale, _input_color->vector()));
}

mix_colors::mix_colors()
{
	register_port(_factor);
	register_port(_color_a);
	register_port(_color_b);
	register_port(_mixed_color);
}

void mix_colors::update()
{
	float f = _factor.data() / 100.0f;
	*_mixed_color = f * _color_a.data() + (1 - f) * _color_b.data();
}

random_color::random_color()
{
	register_port(_color);
}

void random_color::update()
{
	std::mt19937 generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
	std::uniform_real_distribution<float> dis(0, 1);

	*_color = clk::color_rgb{dis(generator), dis(generator), dis(generator)};
}

value_to_color::value_to_color()
{
	register_port(_value);
	register_port(_color);
}

void value_to_color::update()
{
	*_color = clk::color_rgb{*_value / 100.0f};
}

apply_gamma::apply_gamma()
{
	register_port(_linear);
	register_port(_gamma_corrected);
}

void apply_gamma::update()
{
	*_gamma_corrected = clk::color_rgb(glm::pow(_linear->vector(), glm::vec3(1 / 2.2f)));
}

remove_gamma::remove_gamma()
{
	register_port(_gamma_corrected);
	register_port(_linear);
}

void remove_gamma::update()
{
	*_linear = clk::color_rgb(glm::pow(_gamma_corrected->vector(), glm::vec3(2.2f)));
}

tonemap_reinhard::tonemap_reinhard()
{
	register_port(_input_color);
	register_port(_tonemapped_color);
}

void tonemap_reinhard::update()
{
	auto divisor = clk::color_rgb(*_input_color + glm::vec3(1.0f));
	if(divisor.r() != 0 && divisor.g() != 0 && divisor.b() != 0)
		*_tonemapped_color = *_input_color / divisor;
}

tonemap_filmic_aces::tonemap_filmic_aces()
{
	register_port(_input_color);
	register_port(_tonemapped_color);
}

void tonemap_filmic_aces::update()
{
	auto a = 2.51f;
	auto b = 0.03f;
	auto c = 2.43f;
	auto d = 0.59f;
	auto e = 0.14f;
	auto divisor = *_input_color * (c * *_input_color + d) + e;
	if(divisor.r() != 0 && divisor.g() != 0 && divisor.b() != 0)
		*_tonemapped_color = (*_input_color * (a * *_input_color + b)) / divisor;
}

} // namespace clk::algorithms
