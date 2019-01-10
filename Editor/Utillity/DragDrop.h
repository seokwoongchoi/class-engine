#pragma once
#include "stdafx.h"
#include "../ImGui/Source/imgui.h"

enum class DragDropPayloadType :uint
{
	Unknown,
	Texture,
	Object,
	Model,
	Audio,
	Script
};

class DragDrop
{
public:
	static void SetDragDropPayload(const DragDropPayloadType& type, const string& data)
	{
		//어떤 특정공간에 payload가 있다 드래그하면 이곳에 저장한다. 놓는순간 payload에있는 데이터를 꺼내온다.(조건이맞으면)
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
		{
			ImGui::SetDragDropPayload
			(
				reinterpret_cast<const char*>(&type),
				data.c_str(),
				data.length()+1//data의 length는 마지막에 null이 숨어있어서 +1해줘야한다.
			);
			ImGui::Text(data.c_str());
			ImGui::EndDragDropSource();
		}

	}
	static const string GetDragDropPayload(const DragDropPayloadType& type)
	{//놓았을때 등록되었던것을 빼온다.
		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload
			(
				//payload를 꺼내온다. 내가 원하는것만 받아오게 체크한다. type으로 원하는것을 찾게한다.
				reinterpret_cast<const char*>(&type)
			);
			if (payload)
				return reinterpret_cast<const char*>(payload->Data);//payload에 저장되어있는 자료 void*에서 char*로 강제변형해서 리턴한다.
			ImGui::EndDragDropTarget();
		}
		return "";
	}
};