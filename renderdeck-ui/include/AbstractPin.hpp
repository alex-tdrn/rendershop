#pragma once
#include "UniqueID.hpp"
#include "renderdeck/ResourcePort.hpp"

#include <imgui_node_editor.h>
#include <map>

class AbstractPin
{
private:
	static inline std::map<unsigned long long, AbstractPin*> pinMap;
	static inline std::map<AbstractResourcePort const*, ax::NodeEditor::PinId> portMap;
	
protected:
	ax::NodeEditor::PinId id = -1;
	AbstractResourcePort* port = nullptr;

public:
	AbstractPin() = default;
	AbstractPin(AbstractResourcePort* port)
		: id(uniqueID()), port(port)
	{
		pinMap[id.Get()] = this;
		portMap[port] = id;
	}
	AbstractPin(AbstractPin&&) = default;
	AbstractPin(AbstractPin const&) = delete;
	AbstractPin& operator=(AbstractPin&&) = default;
	AbstractPin& operator=(AbstractPin const&) = delete;
	virtual ~AbstractPin()
	{
		pinMap.erase(id.Get());
		portMap.erase(port);
	}

public:
	static  AbstractPin* getPinForID(ax::NodeEditor::PinId id)
	{
		if(pinMap.find(id.Get()) != pinMap.end())
			return pinMap[id.Get()];
		return nullptr;
	}
	static ax::NodeEditor::PinId getIDForPort(AbstractResourcePort const* port)
	{
		if(portMap.find(port) != portMap.end())
			return portMap[port];
		return -1;
	}

	ax::NodeEditor::PinId getID() const
	{
		return id;
	}

	AbstractResourcePort* getPort() const
	{
		return port;
	}

	bool connect(AbstractPin* otherPin)
	{
		auto otherPort = otherPin->getPort();

		if(!otherPort->canConnect(port))
			return false;

		otherPort->connect(port);
		return true;
	}

	virtual void draw() = 0;
	virtual ImVec2 calculateSize() const = 0;
};