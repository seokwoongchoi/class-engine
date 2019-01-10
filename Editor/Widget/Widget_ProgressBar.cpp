#include "stdafx.h"
#include "Widget_ProgressBar.h"

Widget_ProgressBar::Widget_ProgressBar(Context * context)
	:IWidget(context)
	
{ 
	title = "Hold On...";
	progress = 0.0f;
	xMin = 500.0f;
	yMin = 83.0f;
	windowFlags |= ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoScrollbar;
	bVisible = false;
}

Widget_ProgressBar::~Widget_ProgressBar()
{
}

void Widget_ProgressBar::Begin()
{
	IWidget::Begin();
}

void Widget_ProgressBar::Render()
{
	if (!bVisible)
		return;

	ImGui::SetWindowFocus();
	ImGui::PushItemWidth(500.0f-ImGui::GetStyle().WindowPadding.x*2.0f);
	ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
	ImGui::Text(status.c_str());
	ImGui::PopItemWidth();
}
