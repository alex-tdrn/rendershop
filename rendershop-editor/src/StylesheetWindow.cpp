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
		ImGui::SliderFloat("Anchor Offset", &sheet->anchorOffset, 0.0f, 100.0f);
		ImGui::SliderFloat("Link Thickness", &sheet->linkThickness, 1.0f, 10.0f);

	}
	ImGui::End();
}
