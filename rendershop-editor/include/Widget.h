#pragma once
#include <glm/glm.hpp>

class Widget
{
public:
	Widget() = default;
	Widget(Widget const&) = delete;
	Widget(Widget&&) = default;
	Widget& operator=(Widget const&) = delete;
	Widget& operator=(Widget&&) = default;
	virtual ~Widget() = default;

public:
	virtual void draw() = 0;

};