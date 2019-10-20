#pragma once
#include "Widget.h"

#include <vector>
#include <memory>

class MainWidget final : public Widget
{
private:
	std::vector<std::unique_ptr<Widget>> children;
	std::string dockspaceName;

public:
	MainWidget();
	MainWidget(MainWidget const&) = delete;
	MainWidget(MainWidget&&) = default;
	MainWidget& operator=(MainWidget const&) = delete;
	MainWidget& operator=(MainWidget&&) = default;
	virtual ~MainWidget() = default;

private:
	Widget* addChildImpl(std::unique_ptr<Widget>&& widget);
	void drawContents() override;

public:
	template<typename W>
	W* addChild(std::unique_ptr<W>&& widget)
	{
		static_assert(std::is_base_of_v<Widget, W>);
		auto ret = widget.get();
		addChildImpl(std::move(widget));
		return ret;
	}
};