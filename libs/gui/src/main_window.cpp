#include "clk/gui/main_window.hpp"

namespace clk::gui
{
void main_window::add_panel(clk::gui::panel&& panel)
{
	_panels.push_back(std::move(panel));
}

void main_window::draw()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
	window_flags |= ImGuiWindowFlags_NoDocking;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	window_flags |= ImGuiWindowFlags_NoNavFocus;
	ImGui::Begin("Main Window", nullptr, window_flags);
	ImGui::PopStyleVar(3);

	ImGuiID dockspace_id = ImGui::GetID("Main Window Dockspace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

	if(ImGui::BeginMenuBar())
	{
		if(ImGui::BeginMenu("View"))
		{
			for(auto& panel : _panels)
				if(ImGui::MenuItem(panel.title().data(), "", panel.visible()))
					panel.toggle_visibility();
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::End();
	for(auto& panel : _panels)
		panel.draw();
}
} // namespace clk::gui