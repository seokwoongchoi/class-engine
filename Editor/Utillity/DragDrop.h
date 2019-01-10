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
		//� Ư�������� payload�� �ִ� �巡���ϸ� �̰��� �����Ѵ�. ���¼��� payload���ִ� �����͸� �����´�.(�����̸�����)
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
		{
			ImGui::SetDragDropPayload
			(
				reinterpret_cast<const char*>(&type),
				data.c_str(),
				data.length()+1//data�� length�� �������� null�� �����־ +1������Ѵ�.
			);
			ImGui::Text(data.c_str());
			ImGui::EndDragDropSource();
		}

	}
	static const string GetDragDropPayload(const DragDropPayloadType& type)
	{//�������� ��ϵǾ������� ���´�.
		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload
			(
				//payload�� �����´�. ���� ���ϴ°͸� �޾ƿ��� üũ�Ѵ�. type���� ���ϴ°��� ã���Ѵ�.
				reinterpret_cast<const char*>(&type)
			);
			if (payload)
				return reinterpret_cast<const char*>(payload->Data);//payload�� ����Ǿ��ִ� �ڷ� void*���� char*�� ���������ؼ� �����Ѵ�.
			ImGui::EndDragDropTarget();
		}
		return "";
	}
};