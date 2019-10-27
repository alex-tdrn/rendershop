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
		ImGui::ColorEdit4("Event Color", &sheet->eventColor.x);
		ImGui::ColorEdit4("Event Text Color", &sheet->eventTextColor.x);
		ImGui::SliderFloat("Anchor Offset", &sheet->anchorOffset, 0.0f, 100.0f);
		ImGui::SliderFloat("Link Thickness", &sheet->linkThickness, 1.0f, 10.0f);
		ImGui::SliderFloat("Node Border Width", &sheet->nodeBorderWidth, 1.0f, 10.0f);

		if(ImGui::CollapsingHeader("Animations", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Text("Anchor Offset");
			ImGui::Separator();
			ImGui::PushID("Anchor Offset Animation");
			ImGui::SliderFloat("Animated", &sheet->animatedAnchorOffset, 0.0f, 100.0f);
			int duration = sheet->animatedAnchorOffsetDuration.count();
			ImGui::InputInt("Duration", &duration, 10, 100);
			if(duration < 0)
				duration = 0;
			sheet->animatedAnchorOffsetDuration = std::chrono::milliseconds(duration);
			ImGui::PopID();
		}
	}
	ImGui::End();
}
