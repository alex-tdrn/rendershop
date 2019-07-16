#pragma once
#include <imgui.h>

static inline void drawItemRect(ImDrawList* drawList, float r, float g, float b)
{
	drawList->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(),
		ImGui::GetColorU32(ImVec4{ r, g, b, 1 }));
}

static inline void drawSpacingRect(ImDrawList* drawList)
{
	auto cursor = ImGui::GetCursorPos();
	drawList->AddRect(
		{
			cursor.x - ImGui::GetStyle().ItemSpacing.x,
			cursor.y,
		}, {
			cursor.x,
			cursor.y + ImGui::GetTextLineHeight() + ImGui::GetStyle().ItemSpacing.y
		},
		ImGui::GetColorU32(ImVec4{ 1, 1, 0, 1 }))
	;
}

//static void drawCursorRect(ImDrawList* drawList, float r, float g, float b, float w)
//{
//	ax::NodeEditor::GetNodeBackgroundDrawList(id)->AddRect(
//		{
//			ImGui::GetCursorPosX(),
//			ImGui::GetCursorPosY(),
//		}, {
//			ImGui::GetCursorPosX() + w,
//			ImGui::GetCursorPosY() + ImGui::GetTextLineHeight()
//		},
//		ImGui::GetColorU32(ImVec4{ r, g, b, 1 }))
//		;
//}
