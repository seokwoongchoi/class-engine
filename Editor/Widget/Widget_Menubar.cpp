#include "stdafx.h"
#include "Widget_Menubar.h"
#include "../Tool/Tool_Script.h"
#include "../Tool/Tool_Sprite.h"

Widget_Menubar::Widget_Menubar(Context * context)
	:IWidget(context)
	
{
	bShowMetricsWindow = false;
	bShowStyleEditor = false;
	bShowDemoWindow = false;
}

void Widget_Menubar::Render()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Load")) OpenFileDialog();
			ImGui::Separator();
			if (ImGui::MenuItem("Save")) {}
			if (ImGui::MenuItem("Save as")) {}
			
			
			ImGui::EndMenu();
		}


		if (ImGui::BeginMenu("Tools"))
		{
			ImGui::MenuItem("Metrics", nullptr, &bShowMetricsWindow);
			ImGui::MenuItem("Style", nullptr, &bShowStyleEditor);
			ImGui::MenuItem("Demo", nullptr, &bShowDemoWindow);
			ImGui::MenuItem("Script", nullptr, &Tool_Script::Get().IsVisible());
			ImGui::MenuItem("Sprite", nullptr, &Tool_Sprite::Get().IsVisible());
			ImGui::EndMenu();
		}



		ImGui::EndMainMenuBar();
	}


	if (bShowMetricsWindow) ImGui:: ShowMetricsWindow();
	if (bShowStyleEditor)   ImGui:: ShowStyleEditor();
	if (bShowDemoWindow)    ImGui:: ShowDemoWindow();
	if (Tool_Script::Get().IsVisible())Tool_Script::Get().Render();
	if (Tool_Sprite::Get().IsVisible())Tool_Sprite::Get().Render();
}

void Widget_Menubar::OpenFileDialog(string filePath)
{
	if (filePath.length() < 1)
	{
		FileSystem::OpenFileDialog(bind(&Widget_Menubar::OpenFileDialog, this, placeholders::_1));
		FileSystem::TextureFilter;
	}
	else
	{
		
		//TODO: 해당되는 경로를 연결해준다.
	}
}

void Widget_Menubar::SaveFileDialog(string filePath)
{
}
