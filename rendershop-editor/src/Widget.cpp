#include "Widget.h"

void Widget::draw()
{
	if(!visible)
		return;
	drawContents();
}

std::string const& Widget::getTitle() const
{
	return title;
}

bool Widget::isVisible() const
{
	return visible;
}

void Widget::toggleVisibility()
{
	visible = !visible;
}

void Widget::show()
{
	visible = true;
}

void Widget::hide()
{
	visible = false;
}
