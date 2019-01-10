#include"stdafx.h"
#include "Widget_Log.h"
#include "../Utillity/IconProvider.h"

Widget_Log::Widget_Log(Context * context)
	:IWidget(context)
{
	title = "Log";
	bShowInfo = true;
	bShowWarning = true;
	bShowError = true;
	bScroll = false;
	maxLogCount = 999;
    
	logger = new EngineLogger();
	logger->SetCallback([this](const LogPair& logPair) {AddLog(logPair); });

    Log::SetLogger(logger);
	
	//assert를 전부 log로 바꾼다.
	Log::Write("Error", LogType::Error);
	Log::Write("Info", LogType::Info);
	Log::Write("Info", LogType::Info);
}

Widget_Log::~Widget_Log()
{
	SAFE_DELETE(logger);
}



void Widget_Log::Render()
{
	static ImGuiTextFilter logFilter;
	static const vector<ImVec4> logColors=
	{
		ImVec4(0.76f,0.77f,0.8f,1.0f), //info red
		ImVec4(0.75f,0.75f,0.0f,1.0f), //warning yellow
		ImVec4(0.75f,0.0f,0.0f,1.0f), //error white
	};
	auto LogTypeButton = [this](const IconType& type, bool& toggle)
	{
		ImGui::PushStyleColor
		(
			ImGuiCol_Button,
			ImGui::GetStyle().Colors[toggle?ImGuiCol_ButtonActive:ImGuiCol_Button]
		);
		
		if (ImGui::ImageButton(IconProvider::Get().GetShaderResourceFromType(type), ImVec2(15.0f, 15.0f)))
		{
			    toggle = !toggle;
				bScroll =true;
		}
		ImGui::PopStyleColor();
		ImGui::SameLine();
	};
	
	if (ImGui::Button("Clear"))
		Clear();
	ImGui::SameLine();

	LogTypeButton(IconType::Log_Info, bShowInfo);
	LogTypeButton(IconType::Log_Warning, bShowWarning);
	LogTypeButton(IconType::Log_Error, bShowError);
	//filter
	logFilter.Draw("Filter",-100.0f);
	ImGui::Separator();

	ImGui::BeginChild("Log Board",ImVec2(0,0),false,ImGuiWindowFlags_HorizontalScrollbar);
	for (auto& log : logs)
	{
		if (!logFilter.PassFilter(log.text.c_str()))
			continue;

		bool bCheck = false;
		bCheck |= log.type == 0 && bShowInfo;
		bCheck |= log.type == 1 && bShowWarning;
		bCheck |= log.type == 2 && bShowError;

		if (bCheck)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, logColors[log.type]);
			ImGui::TextUnformatted(log.text.c_str());
			ImGui::PopStyleColor();
		}
	}
	if (bScroll)
	{
		ImGui::SetScrollHereY();
		bScroll = false;
	}
	ImGui::EndChild();
}

void Widget_Log::AddLog(const LogPair & logPair)
{
	logs.push_back(logPair);
	if (logs.size() > maxLogCount)
		logs.pop_front();//가장앞에꺼를 지워주기위해서

	bScroll = true;
}

void Widget_Log::Clear()
{
	logs.clear();
	logs.shrink_to_fit();
}
