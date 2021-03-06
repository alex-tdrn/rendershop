#pragma once

#include "clk/util/color_rgb.hpp"

#include <cassert>

namespace clk
{
class color_rgba
{
public:
	color_rgba() = default;
	explicit color_rgba(glm::vec4 v);
	explicit color_rgba(color_rgb v);
	explicit color_rgba(color_rgb v, float a);
	explicit color_rgba(color_rgb v, int a);
	explicit color_rgba(float v);
	explicit color_rgba(int v);
	explicit color_rgba(float r, float g, float b, float a);
	explicit color_rgba(int r, int g, int b, int a);
	color_rgba(color_rgba const&) = default;
	color_rgba(color_rgba&&) = default;
	auto operator=(color_rgba const& that) -> color_rgba& = default;
	auto operator=(color_rgba&& that) -> color_rgba& = default;
	~color_rgba() = default;
	auto operator==(color_rgba const& that) const -> bool;
	auto operator!=(color_rgba const& that) const -> bool;
	static auto compare_equal_low_precision(color_rgba const& lhs, color_rgba const& rhs) -> bool;

	static auto create_random(std::uint64_t seed) -> color_rgba;
	static auto create_random() -> color_rgba;
	static auto pack(color_rgba color) -> std::uint32_t;
	static auto unpack(std::uint32_t packedColor) -> color_rgba;
	auto valid() const -> bool;
	template <typename T>
	auto operator+=(T const& that) -> color_rgba&;
	auto operator+=(color_rgba const& that) -> color_rgba&;
	template <typename T>
	auto operator-=(T const& that) -> color_rgba&;
	auto operator-=(color_rgba const& that) -> color_rgba&;
	template <typename T>
	auto operator*=(T const& that) -> color_rgba&;
	auto operator*=(color_rgba const& that) -> color_rgba&;
	template <typename T>
	auto operator/=(T const& that) -> color_rgba&;
	auto operator/=(color_rgba const& that) -> color_rgba&;
	auto data() -> float*;
	auto r() const -> float;
	auto g() const -> float;
	auto b() const -> float;
	auto a() const -> float;
	auto ru8() const -> std::uint8_t;
	auto gu8() const -> std::uint8_t;
	auto bu8() const -> std::uint8_t;
	auto au8() const -> std::uint8_t;
	auto operator[](std::size_t i) const -> float;
	auto rgb() const -> color_rgb;
	auto vector() const -> glm::vec4;
	auto packed() const -> std::uint32_t;

private:
	color_rgb _rgb_value;
	float _alpha_value = 1.0f;
};

inline color_rgba::color_rgba(glm::vec4 v) : _rgb_value(v.r, v.g, v.b), _alpha_value(v.a)
{
}

inline color_rgba::color_rgba(color_rgb v) : _rgb_value(v)
{
}

inline color_rgba::color_rgba(color_rgb v, float a) : _rgb_value(v), _alpha_value(a)
{
}

inline color_rgba::color_rgba(color_rgb v, int a) : _rgb_value(v), _alpha_value(static_cast<float>(a) / 255.0f)
{
}
inline color_rgba::color_rgba(float v) : _rgb_value(v), _alpha_value(v)
{
}

inline color_rgba::color_rgba(int v)
	: _rgb_value(static_cast<float>(v) / 255.0f), _alpha_value(static_cast<float>(v) / 255.0f)
{
}

inline color_rgba::color_rgba(float r, float g, float b, float a) : _rgb_value(r, g, b), _alpha_value(a)
{
}
inline color_rgba::color_rgba(int r, int g, int b, int a)
	: _rgb_value(static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f, static_cast<float>(b) / 255.0f)
	, _alpha_value(static_cast<float>(a) / 255.0f)
{
}

inline auto color_rgba::operator==(color_rgba const& that) const -> bool
{
	return _rgb_value == that._rgb_value && _alpha_value == that._alpha_value;
}

inline auto color_rgba::operator!=(color_rgba const& that) const -> bool
{
	return _rgb_value != that._rgb_value && _alpha_value != that._alpha_value;
}

inline auto color_rgba::compare_equal_low_precision(color_rgba const& lhs, color_rgba const& rhs) -> bool
{
	return color_rgb::compare_equal_low_precision(lhs._rgb_value, rhs._rgb_value) && lhs.au8() == rhs.au8();
}

inline auto color_rgba::create_random(std::uint64_t seed) -> color_rgba
{
	static std::unordered_map<std::uint64_t, glm::vec4> cache;
	if(cache.find(seed) == cache.end())
	{
		std::mt19937_64 generator(seed);
		std::uniform_real_distribution<float> dis(0, 1);

		cache[seed] = {dis(generator), dis(generator), dis(generator), dis(generator)};
	}
	return color_rgba{cache[seed]};
}

inline auto color_rgba::create_random() -> color_rgba
{
	return color_rgba::create_random(std::chrono::system_clock::now().time_since_epoch().count());
}

inline auto color_rgba::pack(color_rgba color) -> std::uint32_t
{
	std::uint32_t ret = color_rgb::pack(color._rgb_value);
	ret |= color.au8() << 24;
	return ret;
}

inline auto color_rgba::unpack(std::uint32_t packedColor) -> color_rgba
{
	color_rgb rgb = color_rgb::unpack(packedColor);
	int a = static_cast<int>(packedColor >> 24 & 0b1111'1111);
	return color_rgba{rgb, a};
}

inline auto color_rgba::valid() const -> bool
{
	if(!_rgb_value.valid())
		return false;
	if(_alpha_value < 0.0f || _alpha_value > 1.0f)
		return false;
	return true;
}

template <typename T>
auto color_rgba::operator+=(T const& that) -> color_rgba&
{
	_rgb_value += that;
	_alpha_value += that;
	return *this;
}

inline auto color_rgba::operator+=(color_rgba const& that) -> color_rgba&
{
	_rgb_value += that._rgb_value;
	_alpha_value += that._alpha_value;
	return *this;
}

template <typename T>
auto color_rgba::operator-=(T const& that) -> color_rgba&
{
	_rgb_value -= that;
	_alpha_value -= that;
	return *this;
}

inline auto color_rgba::operator-=(color_rgba const& that) -> color_rgba&
{
	_rgb_value -= that._rgb_value;
	_alpha_value -= that._alpha_value;
	return *this;
}

template <typename T>
auto color_rgba::operator*=(T const& that) -> color_rgba&
{
	_rgb_value *= that;
	_alpha_value *= that;
	return *this;
}

inline auto color_rgba::operator*=(color_rgba const& that) -> color_rgba&
{
	_rgb_value *= that._rgb_value;
	_alpha_value *= that._alpha_value;
	return *this;
}

template <typename T>
auto color_rgba::operator/=(T const& that) -> color_rgba&
{
	_rgb_value /= that;
	_alpha_value /= that;
	return *this;
}

inline auto color_rgba::operator/=(color_rgba const& that) -> color_rgba&
{
	_rgb_value /= that._rgb_value;
	_alpha_value /= that._alpha_value;
	return *this;
}

inline auto color_rgba::data() -> float*
{
	return _rgb_value.data();
}

inline auto color_rgba::r() const -> float
{
	return _rgb_value.r();
}

inline auto color_rgba::g() const -> float
{
	return _rgb_value.g();
}

inline auto color_rgba::b() const -> float
{
	return _rgb_value.b();
}

inline auto color_rgba::a() const -> float
{
	return _alpha_value;
}

inline auto color_rgba::ru8() const -> std::uint8_t
{
	return _rgb_value.ru8();
}

inline auto color_rgba::gu8() const -> std::uint8_t
{
	return _rgb_value.gu8();
}

inline auto color_rgba::bu8() const -> std::uint8_t
{
	return _rgb_value.bu8();
}

inline auto color_rgba::au8() const -> std::uint8_t
{
	return static_cast<std::uint8_t>(_alpha_value * 255);
}

inline auto color_rgba::operator[](std::size_t i) const -> float
{
	assert(i <= 3);
	if(i <= 2)
		return _rgb_value[i];
	return _alpha_value;
}

inline auto color_rgba::rgb() const -> color_rgb
{
	return _rgb_value;
}

inline auto color_rgba::vector() const -> glm::vec4
{
	return {_rgb_value.r(), _rgb_value.g(), _rgb_value.b(), _alpha_value};
}

inline auto color_rgba::packed() const -> std::uint32_t
{
	return color_rgba::pack(*this);
}

auto inline operator+(color_rgba const& lhs, color_rgba const& rhs) -> color_rgba
{
	color_rgba result{lhs};
	result += rhs;
	return result;
}

template <typename T>
auto operator+(color_rgba const& lhs, T const& rhs) -> color_rgba
{
	color_rgba result{lhs};
	result += rhs;
	return result;
}

template <typename T>
auto operator+(T const& lhs, color_rgba const& rhs) -> color_rgba
{
	color_rgba result{rhs};
	result += lhs;
	return result;
}

auto inline operator-(color_rgba const& lhs, color_rgba const& rhs) -> color_rgba
{
	color_rgba result{lhs};
	result -= rhs;
	return result;
}

template <typename T>
auto operator-(color_rgba const& lhs, T const& rhs) -> color_rgba
{
	color_rgba result{lhs};
	result -= rhs;
	return result;
}

auto inline operator*(color_rgba const& lhs, color_rgba const& rhs) -> color_rgba
{
	color_rgba result{lhs};
	result *= rhs;
	return result;
}

template <typename T>
auto operator*(color_rgba const& lhs, T const& rhs) -> color_rgba
{
	color_rgba result{lhs};
	result *= rhs;
	return result;
}

template <typename T>
auto operator*(T const& lhs, color_rgba const& rhs) -> color_rgba
{
	color_rgba result{rhs};
	result *= lhs;
	return result;
}

auto inline operator/(color_rgba const& lhs, color_rgba const& rhs) -> color_rgba
{
	color_rgba result{lhs};
	result /= rhs;
	return result;
}

template <typename T>
auto operator/(color_rgba const& lhs, T const& rhs) -> color_rgba
{
	color_rgba result{lhs};
	result /= rhs;
	return result;
}

template <>
inline auto data_type_name<color_rgba>::get() -> std::string
{
	return "Color with transparency";
}

} // namespace clk