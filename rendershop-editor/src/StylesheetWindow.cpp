#include "StylesheetWindow.h"

StylesheetWindow::StylesheetWindow()
{
	setStylesheet(Stylesheet::getCurrentSheet());
}

void StylesheetWindow::setStylesheet(Stylesheet& sheet)
{
	this->sheet = &sheet;
	title = "Stylesheet " + sheet.getName();
}

void StylesheetWindow::drawContents()
{
	if(ImGui::Begin(title.c_str(), &visible, windowFlags))
	{
		if(ImGui::CollapsingHeader("Global", ImGuiTreeNodeFlags_DefaultOpen))
		{

		}

		if(ImGui::CollapsingHeader("Nodes", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::SliderFloat("Node Border Width", &sheet->nodeBorderWidth, 1.0f, 10.0f);
			ImGui::SliderFloat("Hovered Border Width", &sheet->hoveredNodeBorderWidth, 1.0f, 10.0f);
			ImGui::SliderFloat("Selected Border Width", &sheet->selectedNodeBorderWidth, 1.0f, 10.0f);
			ImGui::SliderFloat("Node Rounding", &sheet->nodeRounding, 0.0f, 100.0f);
			ImGui::SliderFloat4("Node Padding", &sheet->nodePadding.x, 0.0f, 100.0f);
		}

		if(ImGui::CollapsingHeader("Pins", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::ColorEdit4("Event Color", &sheet->eventColor.x);
			ImGui::ColorEdit4("Event Text Color", &sheet->eventTextColor.x);
			ImGui::SliderFloat("Anchor Offset", &sheet->anchorOffset, 0.0f, 100.0f);
			ImGui::SliderFloat("Animated Anchor Offset", &sheet->animatedAnchorOffset, 0.0f, 100.0f);
			int duration = sheet->animatedAnchorOffsetDuration.count();
			ImGui::InputInt("Duration Anchor Offset Animation", &duration, 10, 100);
			if(duration < 0)
				duration = 0;
			sheet->animatedAnchorOffsetDuration = std::chrono::milliseconds(duration);
			ImGui::SliderFloat("Pin Border Width", &sheet->pinBorderWidth, 0.0f, 100.0f);
			ImGui::SliderFloat("Pin Rounding", &sheet->pinRounding, 0.0f, 100.0f);
			ImGui::SliderFloat("Pin Radius", &sheet->pinRadius, 0.0f, 100.0f);
			ImGui::SliderFloat("Pin Arrow Size", &sheet->pinArrowSize, 0.0f, 100.0f);
			ImGui::SliderFloat("Pin Arrow Width", &sheet->pinArrowWidth, 0.0f, 100.0f);
		}

		if(ImGui::CollapsingHeader("Links", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::SliderFloat("Link Strength", &sheet->linkStrength, 0.0f, 1000.0f);
			ImGui::SliderFloat("Link Thickness", &sheet->linkThickness, 1.0f, 10.0f);
			ImGui::SliderFloat2("Target Direction", &sheet->targetDirection.x, -1.0f, 1.0f);
			ImGui::SliderFloat2("Source Direction", &sheet->sourceDirection.x, -1.0f, 1.0f);
			ImGui::SliderFloat("Flow Marker Distance", &sheet->flowMarkerDistance, 0.0f, 100.0f);
			ImGui::SliderFloat("Flow Speed", &sheet->flowSpeed, 0.0f, 1000.0f);
			ImGui::SliderFloat("Flow Duration", &sheet->flowDuration, 0.0f, 10.0f);
		}


	}
	ImGui::End();
}
