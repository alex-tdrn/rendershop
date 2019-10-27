#include "NodeCanvas.h"
#include "AbstractPin.hpp"
#include "rendershop/base/AbstractPipe.hpp"
#include "Stylesheet.hpp"

NodeCanvas::NodeCanvas()
{
	context = ax::NodeEditor::CreateEditor();
	title = "Pipeline Canvas " + std::to_string(id);
	windowFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
}

NodeCanvas::~NodeCanvas()
{
	ax::NodeEditor::DestroyEditor(context);
}

void NodeCanvas::drawContents()
{
	if(ImGui::Begin(title.c_str(), &visible, windowFlags))
	{
		ax::NodeEditor::SetCurrentEditor(context);
		ax::NodeEditor::Begin(title.c_str());
		ax::NodeEditor::GetStyle().LinkStrength = Stylesheet::getCurrentSheet().linkStrength;

		for(auto& node : nodes)
			node.draw();
		for(auto& node : nodes)
			node.drawInputLinks();
		if(ax::NodeEditor::BeginCreate())
		{
			ax::NodeEditor::PinId idPin1 = 0, idPin2 = 0;
			if(ax::NodeEditor::QueryNewLink(&idPin1, &idPin2) && idPin1 != idPin2)
			{
				auto pin1 = AbstractPin::getPinForID(idPin1);
				auto pin2 = AbstractPin::getPinForID(idPin2);
				if(pin1->canConnect(pin2))
				{
					if(ax::NodeEditor::AcceptNewItem({0, 1, 0, 1, }, 2))
					{
						pin1->connect(pin2);
					}
				}
				else
				{
					ax::NodeEditor::RejectNewItem({1, 0, 0, 1}, 2);
				}
			}

			ax::NodeEditor::PinId pinId = 0;
			if(ax::NodeEditor::QueryNewNode(&pinId))
			{
				if(ax::NodeEditor::AcceptNewItem())
				{
					ax::NodeEditor::Suspend();
					ImGui::OpenPopup("Create New Node");
					ax::NodeEditor::Resume();
				}
			}
		}
		ax::NodeEditor::EndCreate();

		ax::NodeEditor::Suspend();
		if(ImGui::BeginPopup("<<Create New Link>>"))
		{
			ImGui::Text("<<< TEST >>>");
			ImGui::Text("Create New Link");

			ImGui::EndPopup();
		}

		if(ImGui::BeginPopup("Create New Node"))
		{
			for(auto [name, constructor] : AbstractPipe::getPipeMap())
			{
				if(ImGui::MenuItem(name.c_str()))
				{
					auto source = constructor();
					nodes.emplace_back(source.get());
					store->push_back(std::move(source));
				}
			}
			ImGui::EndPopup();
		}
		ax::NodeEditor::Resume();


		ax::NodeEditor::End();
	}
	ImGui::End();
}

void NodeCanvas::setStore(std::vector<std::unique_ptr<AbstractPipe>>* store)
{
	this->store = store;
	for(auto& pipe : *store)
		nodes.emplace_back(pipe.get());
}
