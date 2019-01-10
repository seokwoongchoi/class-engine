#include "stdafx.h"
#include "Widget_ToolBar.h"
#include "../ImGui/Source/imgui_internal.h"
#include "../Utillity/IconProvider.h"
#include "../Utillity/EditorHelper.h"

float Widget_ToolBar::ToolBarHeight = 0.0f;


Widget_ToolBar::Widget_ToolBar(Context * context)
	:IWidget(context)
{
	title = "ToolBar";
	windowFlags |= ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoTitleBar;
}

void Widget_ToolBar::Begin()
{
	ImGuiContext& ctx = *GImGui;
	float width = ctx.IO.DisplaySize.x;
	float height = ctx.FontBaseSize + ctx.Style.FramePadding.y*2.0f - 1.0f;
	//메뉴바의 폰트사이즈랑 패딩사이즈를 가지고와서 메뉴바바로밑에 툴바가 붙을수있게한다.
	ToolBarHeight = height + 14.0f;
	ImGui::SetNextWindowPos(ImGui::GetWindowViewport()->Pos+ImVec2(0.0f,ImGui::GetFrameHeight()));
	ImGui::SetNextWindowSize(ImVec2(width, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 4.0f));
	ImGui::Begin(title.c_str(), &bVisible, windowFlags);
}

void Widget_ToolBar::Render()
{
	ImGui::SameLine();
	ImGui::PushStyleColor //버튼눌렀을대 active형태 유지
	(
		ImGuiCol_Button,
		ImGui::GetStyle().Colors[Engine::IsOnEngineFlags(EngineFlags_Game)?ImGuiCol_ButtonActive : ImGuiCol_Button]
	);
	if (IconProvider::Get().ImageButton(IconType::Play, 20.0f))
	{
		Engine::ToggleEngineFlags(EngineFlags_Game);
	}
	ImGui::PopStyleColor();
}

void Widget_ToolBar::End()
{
	ImGui::PopStyleVar();
	ImGui::End();   
}
