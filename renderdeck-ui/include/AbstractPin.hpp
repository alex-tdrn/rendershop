#pragma once
#include <imgui_node_editor.h>
#include <map>

class AbstractPin
{
private:
	static inline std::map<unsigned long long, AbstractPin*> pinMap;

protected:
	ax::NodeEditor::PinId id = -1;

public:
	AbstractPin() = default;
	AbstractPin(ax::NodeEditor::PinId id)
		: id(id)
	{
		pinMap[id.Get()] = this;
	}
	AbstractPin(AbstractPin&&) = default;
	AbstractPin(AbstractPin const&) = delete;
	AbstractPin& operator=(AbstractPin&&) = default;
	AbstractPin& operator=(AbstractPin const&) = delete;
	~AbstractPin()
	{
		pinMap.erase(id.Get());
	}

public:
	static  AbstractPin const* getPinForID(ax::NodeEditor::PinId id)
	{
		if(pinMap.find(id.Get()) != pinMap.end())
			return pinMap[id.Get()];
		return nullptr;
	}
	ax::NodeEditor::PinId getID() const
	{
		return id;
	}
	virtual bool connect(AbstractPin const* otherPin) const = 0;
	virtual void draw() = 0;
	virtual ImVec2 calculateSize() const = 0;
};