#include"stdafx.h"
#include "Widget_Assets.h"
#include "../Utillity/EditorHelper.h"
#include "../Utillity/DragDrop.h"


Widget_Assets::Widget_Assets(Context * context)
	:IWidget(context)
{
	
	title = "Assets";
	itemSize = 100.0f;
	itemSizeMin = 50.0f;
	itemSizeMax = 200.0f;

	currentPath = "../_Assets/Texture/";
	resourceManager = context->GetSubsystem<ResourceManager>();

	UpdateItems(currentPath);
}

Widget_Assets::~Widget_Assets()
{
}



void Widget_Assets::Render()
{
	if (ImGui::Button("Directory"))
	{
		//TODO:
    }
	ImGui::SameLine();
	ImGui::Text(currentPath.c_str());
	ImGui::SameLine(ImGui::GetWindowContentRegionWidth()*0.8f);
	ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth()*0.207f);
	ImGui::SliderFloat("##ItemSize", &itemSize, itemSizeMin, itemSizeMax);
	ImGui::PopItemWidth();

	ImGui::Separator();

	ShowItems();
}

void Widget_Assets::ShowItems()
{
	auto PushStyle = []()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1.0f, 18.0f));
	};

	auto PopStyle = []() {ImGui::PopStyleVar(2); };

	ImVec2 contextSize = ImGui::GetWindowContentRegionMax() - ImGui::GetWindowContentRegionMin();
	

	PushStyle();

	ImGui::BeginChild("##Child",contextSize,true);
	{
		int columns = static_cast<int>(ImGui::GetWindowContentRegionWidth()/itemSize);
		columns = columns < 1 ? 1 : columns; //없다면 아이템이 없으니까 없으면 아에 생성이 안되니까 하나라도 잡아지게한다.
		ImGui::Columns(columns, nullptr, false);
		for (auto& item : items)
		{
			//ImageButton
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

			if (ImGui::ImageButton(item.thumbnail.texture->GetShaderResourceView(), ImVec2(itemSize, itemSize-23.0f)))
			{
				//TODO:
			}
			ImGui::PopStyleColor(2);

			//Dragdrop
			DragDrop::SetDragDropPayload(DragDropPayloadType::Texture, item.label);

			//Label
			ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX()-itemSize);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSize - 13.0f);
			ImGui::PushItemWidth(itemSize+8.5f);
			{
				ImGui::TextWrapped(item.label.c_str());
			}
			ImGui::PopItemWidth();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + itemSize);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - itemSize + 13.0f);

			ImGui::NextColumn();
		}
	}
	ImGui::EndChild();

	PopStyle();
}

void Widget_Assets::UpdateItems(const string & path)
{
	//item vector에 아이템들을 집어넣는다.
	if (!FileSystem::IsDirectory(path))
		return;

	items.clear();
	items.shrink_to_fit();

	vector<string>files;
	files = FileSystem::GetFilesInDirectory(path);
	for (const auto& file : files)
	{
		items.emplace_back(file, IconProvider::Get().Load(file, IconType::Custom));
	}
}
