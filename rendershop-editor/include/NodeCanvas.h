#pragma once

#include "Widget.h"
#include "Node.h"

#include <vector>
#include <memory>

class AbstractPipe;

class NodeCanvas final : public Widget
{
private:
	ax::NodeEditor::EditorContext* context;
	std::vector<std::unique_ptr<AbstractPipe>>* store = nullptr;
	std::vector<Node> nodes;
	
public:
	NodeCanvas();
	NodeCanvas(NodeCanvas const&) = delete;
	NodeCanvas(NodeCanvas&&) = default;
	NodeCanvas& operator=(NodeCanvas const&) = delete;
	NodeCanvas& operator=(NodeCanvas&&) = default;
	~NodeCanvas();

public:
	void draw() override;
	void setStore(std::vector<std::unique_ptr<AbstractPipe>>* store);

};