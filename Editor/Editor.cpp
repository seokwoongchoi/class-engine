#include "stdafx.h"
#include "Editor.h"
#include "ImGui/Source/imgui.h"
#include "ImGui//Source/imgui_internal.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

#include "Widget/Widget_Menubar.h"
#include "Widget/Widget_ToolBar.h"
#include "Widget/Widget_Hierachy.h"
#include "Widget/Widget_Inspector.h"
#include "Widget/Widget_Assets.h"
#include "Widget/Widget_Scene.h"
#include "Widget/Widget_Log.h"
#include "Widget/Widget_Project.h"
#include "Widget/Widget_ProgressBar.h"
#include "Utillity/IconProvider.h"
#include "./Utillity/EditorHelper.h"
#include "./Tool/Tool_Script.h"
#include "./Tool/Tool_Sprite.h"

#define DOCKING_ENABLED ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable //현재 도킹이 가능한지 아닌지 체크


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
function<LRESULT(HWND, uint, WPARAM, LPARAM)>Editor::EditorProc = nullptr;
Editor::Editor()
	:context(nullptr)
	,bInitialized(false)
	,bUsingDockSpace(true)
{

	
}

Editor::~Editor()
{
	if (!bInitialized)return;
	for (auto widget : widgets)
		SAFE_DELETE(widget);

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

}

LRESULT Editor::MessageProc(HWND handle, uint message, WPARAM wParam, LPARAM lParam)
{
	return ImGui_ImplWin32_WndProcHandler(handle,message,wParam,lParam);
}

void Editor::Resize()
{
}

void Editor::Initialize(Context * context)
{
	if (bInitialized)return;
	this->context = context;
	auto graphics = context->GetSubsystem<Graphics>();

	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcon;
	io.ConfigResizeWindowsFromEdges = true; //imgui가 빠져나오게 할수있다.

	ImGui_ImplWin32_Init(Settings::Get()->GetWindowHandle());
	
	ImGui_ImplDX11_Init(graphics->GetDevice(), graphics->GetDeviceContext());
	ApplyStyle();
	
	IconProvider::Get().Initialize(context);
	Tool_Script::Get().Initialize(context);
	Tool_Sprite::Get().Initialize(context);
	widgets.emplace_back(new Widget_Menubar(context));
	widgets.emplace_back(new Widget_ToolBar(context));
	widgets.emplace_back(new Widget_Hierachy(context));
	widgets.emplace_back(new Widget_Inspector(context));
	widgets.emplace_back(new Widget_Assets(context));
	widgets.emplace_back(new Widget_Scene(context));
	widgets.emplace_back(new Widget_Log(context));
	widgets.emplace_back(new Widget_Project(context));
	widgets.emplace_back(new Widget_ProgressBar(context));
	//widgets.emplace_back(new Widget_ToolBar(context));
	/*for (auto widget : widgets)
		widget->Initialize(context);*/


	EditorProc = bind(
		&Editor::MessageProc,this,
		placeholders::_1,
		placeholders::_2,
		placeholders::_3,
		placeholders::_4
	);
	bInitialized = true;
}

void Editor::Render()
{
	if (!bInitialized)return;
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	if(DOCKING_ENABLED)
		BeginDockSpace();

	for (auto widget : widgets)
	{
 		if(widget->IsVisible())
	    {
		widget->Begin();
		widget->Render();
		widget->End();
	
	    }
	}
	
	if (DOCKING_ENABLED)
	EndDockSpace();
	//Tool_Script::Get().Render();

	ImGui::Render();//그리는게 아니라 데이터만 만든다.
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	//imgui의 데이터가 dx11로 넘어가서 dx11이 그린다.

	
	if (DOCKING_ENABLED)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault(); //추가적인 플랫폼 저장하는함수
	}
}

void Editor::BeginDockSpace()
{
	ImGuiWindowFlags windowFlags =
		//ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos + ImVec2(0.0f, ImGui::GetFrameHeight()+ Widget_ToolBar::ToolBarHeight));
	ImGui::SetNextWindowSize(viewport->Size - ImVec2(0.0f, Widget_ToolBar::ToolBarHeight+ ImGui::GetFrameHeight()));

	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowBgAlpha(0.0f);//백그라운드 알파값안주는거
	ImGui::Begin("DockSpace", &bUsingDockSpace, windowFlags);
	ImGui::PopStyleVar(3);

	//ImGuiIO& io = ImGui::GetIO();
	//if (io.ConfigFlags&ImGuiConfigFlags_DockingEnable)
	//{
	//	ImGuiID id = ImGui::GetID("MyDockSpace");
	//	ImGui::DockSpace(id, ImVec2(0.0f, 0.0f), ImGuiWindowFlags_AlwaysAutoResize);
	//}
	//ImGui::End();
	ImGuiID id = ImGui::GetID("MyDockSpace");//MyDockSpace
	if (!ImGui::DockBuilderGetNode(id))
	{
		ImGui::DockBuilderRemoveNode(id);
		ImGui::DockBuilderAddNode(id, ImGui::GetMainViewport()->Size);

		ImGuiID mainDock = id;
		ImGuiID rightDock = ImGui::DockBuilderSplitNode(mainDock,ImGuiDir_Right,0.2f,nullptr,&mainDock);
		ImGuiID rightDownDock = ImGui::DockBuilderSplitNode(rightDock, ImGuiDir_Down, 0.6f, nullptr, &rightDock);
		ImGuiID downDock = ImGui::DockBuilderSplitNode(mainDock, ImGuiDir_Down, 0.3f, nullptr, &mainDock);
		ImGuiID downRightDock = ImGui::DockBuilderSplitNode(downDock, ImGuiDir_Right, 0.6f, nullptr, &downDock);

		ImGui::DockBuilderDockWindow("Scene",mainDock);
		ImGui::DockBuilderDockWindow("Hierarchy",rightDock);
		ImGui::DockBuilderDockWindow("Inspector",rightDownDock);
		ImGui::DockBuilderDockWindow("Assets",downDock);
		ImGui::DockBuilderDockWindow("Log", downRightDock);
		ImGui::DockBuilderFinish(mainDock);


	}
	ImGui::DockSpace(id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruDockspace);

}

void Editor::EndDockSpace()
{
	ImGui::End();
}

void Editor::ApplyStyle()
{
	ImGui::GetIO().ConfigResizeWindowsFromEdges = true;
	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();

	float fontSize = 15.0f;
	float roundness = 2.0f;
	ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 text = ImVec4(0.76f, 0.77f, 0.8f, 1.0f);
	ImVec4 black = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 backgroundVeryDark = ImVec4(0.08f, 0.086f, 0.094f, 1.00f);
	ImVec4 backgroundDark = ImVec4(0.117f, 0.121f, 0.145f, 1.00f);
	ImVec4 backgroundMedium = ImVec4(0.26f, 0.26f, 0.27f, 1.0f);
	ImVec4 backgroundLight = ImVec4(0.37f, 0.38f, 0.39f, 1.0f);
	ImVec4 highlightBlue = ImVec4(0.172f, 0.239f, 0.341f, 1.0f);
	ImVec4 highlightBlueHovered = ImVec4(0.202f, 0.269f, 0.391f, 1.0f);
	ImVec4 highlightBlueActive = ImVec4(0.382f, 0.449f, 0.561f, 1.0f);
	ImVec4 barBackground = ImVec4(0.078f, 0.082f, 0.09f, 1.0f);
	ImVec4 bar = ImVec4(0.164f, 0.180f, 0.231f, 1.0f);
	ImVec4 barHovered = ImVec4(0.411f, 0.411f, 0.411f, 1.0f);
	ImVec4 barActive = ImVec4(0.337f, 0.337f, 0.368f, 1.0f);

	// Spatial
	style.WindowBorderSize = 1.0f;
	style.FrameBorderSize = 1.0f;
	style.FramePadding = ImVec2(5, 5);
	style.ItemSpacing = ImVec2(6, 5);
	style.Alpha = 1.0f;
	style.WindowRounding = roundness;
	style.FrameRounding = roundness;
	style.PopupRounding = roundness;
	style.GrabRounding = roundness;
	style.ScrollbarSize = 20.0f;
	style.ScrollbarRounding = roundness;

	// Colors
	style.Colors[ImGuiCol_Text] = text;
	style.Colors[ImGuiCol_WindowBg] = backgroundDark;
	style.Colors[ImGuiCol_Border] = black;
	style.Colors[ImGuiCol_FrameBg] = bar;
	style.Colors[ImGuiCol_FrameBgHovered] = highlightBlue;
	style.Colors[ImGuiCol_FrameBgActive] = highlightBlueHovered;
	style.Colors[ImGuiCol_TitleBg] = backgroundVeryDark;
	style.Colors[ImGuiCol_TitleBgActive] = bar;
	style.Colors[ImGuiCol_MenuBarBg] = backgroundVeryDark;
	style.Colors[ImGuiCol_ScrollbarBg] = barBackground;
	style.Colors[ImGuiCol_ScrollbarGrab] = bar;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = barHovered;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = barActive;
	style.Colors[ImGuiCol_CheckMark] = white;
	style.Colors[ImGuiCol_SliderGrab] = bar;
	style.Colors[ImGuiCol_SliderGrabActive] = barActive;
	style.Colors[ImGuiCol_Button] = barActive;
	style.Colors[ImGuiCol_ButtonHovered] = highlightBlue;
	style.Colors[ImGuiCol_ButtonActive] = highlightBlueActive;
	style.Colors[ImGuiCol_Header] = highlightBlue; // selected items (tree, menu bar etc.)
	style.Colors[ImGuiCol_HeaderHovered] = highlightBlueHovered; // hovered items (tree, menu bar etc.)
	style.Colors[ImGuiCol_HeaderActive] = highlightBlueActive;
	style.Colors[ImGuiCol_Separator] = backgroundLight;
	style.Colors[ImGuiCol_ResizeGrip] = backgroundMedium;
	style.Colors[ImGuiCol_ResizeGripHovered] = highlightBlue;
	style.Colors[ImGuiCol_ResizeGripActive] = highlightBlueHovered;
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.7f, 0.77f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = highlightBlue; // Also used for progress bar
	style.Colors[ImGuiCol_PlotHistogramHovered] = highlightBlueHovered;
	style.Colors[ImGuiCol_TextSelectedBg] = highlightBlue;
	style.Colors[ImGuiCol_PopupBg] = backgroundVeryDark;
	style.Colors[ImGuiCol_DragDropTarget] = backgroundLight;
}
