#pragma once
#include <glm/glm.hpp>
#include <string>
#include <imgui.h>

class Widget
{
private:
	static inline int idCounter = 0;

protected:
	const int id = idCounter++;
	std::string title; 
	bool visible = true;
	ImGuiWindowFlags windowFlags;

public:
	Widget() = default;
	Widget(Widget const&) = delete;
	Widget(Widget&&) = default;
	Widget& operator=(Widget const&) = delete;
	Widget& operator=(Widget&&) = default;
	virtual ~Widget() = default;

protected:
	virtual void drawContents() = 0;

public:
	void draw();
	std::string const& getTitle() const;
	bool isVisible() const;
	void toggleVisibility();
	void show();
	void hide();

};