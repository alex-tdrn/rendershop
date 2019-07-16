#pragma once
#include <imgui.h>

static inline void drawItemRect(ImDrawList* drawList)
{
	auto min = ImGui::GetItemRectMin();
	auto max = ImGui::GetItemRectMax();
	
	const float minSize = 4;
	if(max.x - min.x < minSize)
		max.x = min.x + minSize;
	if(max.y - min.y < minSize)
		max.y = min.y + minSize;

	drawList->AddRect(min, max, ImGui::GetColorU32(ImVec4{ 1, 0, 1, 1 }));
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
		}, ImGui::GetColorU32(ImVec4{ 1, 1, 0, 1 }))
	;
}

static inline void drawRect(ImDrawList* drawList, ImVec2 start, float w)
{
	drawList->AddRect(start, {
			start.x + w,
			start.y + ImGui::GetTextLineHeight() + ImGui::GetStyle().ItemSpacing.y
		}, ImGui::GetColorU32(ImVec4{0, 1, 1, 1 }));
}

static inline void drawRect(ImDrawList* drawList, ImVec2 start, float w, float h)
{
	drawList->AddRect(start, {
		start.x + w,
		start.y + h
		}, ImGui::GetColorU32(ImVec4{ 0, 1, 1, 1 }));
}
