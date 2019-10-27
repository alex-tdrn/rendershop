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

		}

		if(ImGui::CollapsingHeader("Links", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::SliderFloat("Link Strength", &sheet->linkStrength, 0.0f, 1000.0f);
			ImGui::SliderFloat("Link Thickness", &sheet->linkThickness, 1.0f, 10.0f);

		}


	}
	ImGui::End();
}
