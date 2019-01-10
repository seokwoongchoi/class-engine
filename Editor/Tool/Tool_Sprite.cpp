#include "stdafx.h"
#include "Tool_Sprite.h"
#include "../ImGui/Source/imgui.h"
#include "../Utillity/DragDrop.h"
#include "../Utillity/EditorHelper.h"

void Tool_Sprite::Initialize(Context * context)
{
	this->context = context;
	this->resourceManager = context->GetSubsystem<ResourceManager>();
	this->texture = nullptr;
	this->gridSpacing = 10.0f;
	this->gridColor = D3DXCOLOR(0, 1, 0, 1);
	this->bVisible = false;
	this->bRender = false;
	this->bCheckSize = false;
	this->bCheckOff = false;

}
void Tool_Sprite::Render()
{
	if (!bVisible) return;

	ImGui::Begin("SpriteTool", &bVisible);
	{
		ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
		ImVec2 size = ImGui::GetWindowSize();
		ShowSpriteFrame(size);
		DragDrop();
		
		ShowSpriteInfo(size);
		ShowSpriteEdit(size);
	}
	ImGui::End();
}

void Tool_Sprite::ShowSpriteFrame(const ImVec2 & size)
{
	ImGui::BeginChild("##SpriteFrame", ImVec2(size.x*0.5f, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
	{
		if (texture)
		{
			Mouse();
			ImVec2 firstMousePos = ImGui::GetIO().MouseClickedPos[0];
			ImVec2 lastMousePos = ImGui::GetMousePos();
			ImVec2 windowPos = ImGui::GetCursorPos() + ImGui::GetWindowPos();
			ImDrawList* drawList = ImGui::GetWindowDrawList();

			//Vertical
			for (float x = 0; x <= texture->GetSize().x; x += gridSpacing)
			{
				drawList->AddLine
				(
					ImVec2(x+ windowPos.x,windowPos.y),
					ImVec2(x+windowPos.x,windowPos.y+texture->GetSize().y),
					gridColor
				);
			}
			//Horizontal
			for (float y = 0; y <= texture->GetSize().y; y += gridSpacing)
			{
				drawList->AddLine
				(

					ImVec2( windowPos.x, y+windowPos.y),
					ImVec2( windowPos.x + texture->GetSize().x, y+windowPos.y ),
					gridColor
				);
				
			}
			ImGui::Image
			(
				texture->GetShaderResourceView(),EditorHelper::ToImVec2(texture->GetSize())
			);
			//Check Size
			if (texture&& ImGui::IsMouseDown(0)&&ImGui::IsWindowHovered())
			{

				width = Math::Abs(firstMousePos.x - lastMousePos.x);
				height = Math::Abs(firstMousePos.y - lastMousePos.y);
			
				widths.clear();
				heights.clear();
				bCheckSize = false;
			}
			if (ImGui::IsMouseReleased(0) && !ImGui::IsAnyItemActive()&&ImGui::IsWindowHovered() )
			{

				float width = Math::Abs(firstMousePos.x - lastMousePos.x);
				float height = Math::Abs(firstMousePos.y - lastMousePos.y);
				widths.emplace_back(width);
				heights.emplace_back(height);
				bCheckSize = true;

			}
			//Check Offset
			if (texture&& ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			{

				offsetx = firstMousePos.x - windowPos.x;
				offsety = firstMousePos.y - windowPos.y;

				offsetxs.clear();
				offsetys.clear();
				bCheckOff = false;
			}
			if (ImGui::IsMouseReleased(0) && !ImGui::IsAnyItemActive() && ImGui::IsWindowHovered())
			{

				offsetx = firstMousePos.x - windowPos.x;
				offsety = firstMousePos.y - windowPos.y;
				offsetxs.emplace_back(offsetx);
				offsetys.emplace_back(offsety);
				bCheckOff = true;

			}
		
		}
	}
	ImGui::EndChild();
}

void Tool_Sprite::ShowSpriteInfo(const ImVec2 & size)
{
	ImGui::SameLine();
	ImGui::BeginChild("##SpriteInfo", ImVec2(size.x*0.25f-70.0f, 0), true);
	{
		ImVec2 windowPos = ImGui::GetCursorPos() + ImGui::GetWindowPos();
			auto ShowFloat = [](const char* label, float* value)
			{
				float step = 1.0f;
				float step_fast = 1.0f;
				char* decimals = "%.3f";
				auto flags = ImGuiInputTextFlags_CharsDecimal;

				ImGui::PushItemWidth(100.0f);
				ImGui::InputFloat(label, value);//, step, step_fast, decimals, flags
				ImGui::PopItemWidth();
			};
			if (ImGui::CollapsingHeader("SpriteInfo", ImGuiTreeNodeFlags_DefaultOpen))
			{
				
				float zero = 0.0f;
				ImGui::Text("");
				ImGui::SameLine(0.0f); 
				ImGui::NewLine();      //!ImGui::IsWindowHovered() &&
					
				if (bCheckSize)
				{
					for (auto width1 : widths)
					{
						ImGui::NewLine();       ShowFloat("Width", &width1);
					}
					for (auto height1 : heights)
					{
						ImGui::NewLine();		ShowFloat("Height", &height1);
					}
				}
				else
				{
					ImGui::NewLine();       ShowFloat("Width", &width);
					ImGui::NewLine();		ShowFloat("Height", &height);
				}
			
				if (bCheckOff)
				{
					for (auto offsetx1 : offsetxs)
					{
						ImGui::NewLine();       ShowFloat("OffSet.X", &offsetx1);
					}
					for (auto offsety1 : offsetys)
					{
						ImGui::NewLine();		ShowFloat("OffSet.Y", &offsety1);
					}
				}
				else
				{
					ImGui::NewLine();       ShowFloat("OffSet.X", &offsetx);
					ImGui::NewLine();		ShowFloat("OffSet.Y", &offsety);
				}
				
			ImGui::NewLine();
			ImGui::Button("Save");

			}
	}
	ImGui::EndChild();
}

void Tool_Sprite::ShowSpriteEdit(const ImVec2 & size)
{
	ImGui::SameLine();
	ImGui::BeginChild("##SpriteEdit", ImVec2(size.x*0.25f - 10.0f, 0), true);
	{
		ImVec2 windowPos = ImGui::GetCursorPos() + ImGui::GetWindowPos();
		auto ShowFloat = [](const char* label, float* value)
		{
			float step = 1.0f;
			float step_fast = 1.0f;
			char* decimals = "%.3f";
			auto flags = ImGuiInputTextFlags_CharsDecimal;

			ImGui::PushItemWidth(100.0f);
			ImGui::InputFloat(label, value);//, step, step_fast, decimals, flags
			ImGui::PopItemWidth();
		};
		if (ImGui::CollapsingHeader("SpriteEditor", ImGuiTreeNodeFlags_DefaultOpen))
		{

			float zero = 0.0f;
			ImGui::Text("");
			ImGui::SameLine(0.0f);
			ImGui::NewLine();      //!ImGui::IsWindowHovered() &&

			if (bCheckSize)
			{
				for (auto width1 : widths)
				{
					ImGui::NewLine();       ShowFloat("Width", &width1);
				}
				for (auto height1 : heights)
				{
					ImGui::NewLine();		ShowFloat("Height", &height1);
				}
			}
			else
			{
				ImGui::NewLine();       ShowFloat("Width", &width);
				ImGui::NewLine();		ShowFloat("Height", &height);
			}

			if (bCheckOff)
			{
				for (auto offsetx1 : offsetxs)
				{
					ImGui::NewLine();       ShowFloat("OffSet.X", &offsetx1);
				}
				for (auto offsety1 : offsetys)
				{
					ImGui::NewLine();		ShowFloat("OffSet.Y", &offsety1);
				}
			}
			else
			{
				ImGui::NewLine();       ShowFloat("OffSet.X", &offsetx);
				ImGui::NewLine();		ShowFloat("OffSet.Y", &offsety);
			}

			ImGui::NewLine();
			ImGui::Button("Save");
		}
	}
	ImGui::EndChild();
}

void Tool_Sprite::DragDrop()
{
	auto data = DragDrop::GetDragDropPayload(DragDropPayloadType::Texture);
	if (data.length())
	{
		texture = resourceManager->Load<Texture2D>(data);
	}
}

void Tool_Sprite::Mouse()
{
	//ShowExampleAppCustomRendering
	//bool bCheck = false;
	////bCheck |= !camera;//카메라가 없다면 픽킹의 의미가 없다.
	//bCheck |= !ImGui::IsMouseClicked(0);//0이면 왼쪽 마우스클릭이 안되면 픽킹필요없다.
	//bCheck |= !ImGui::IsWindowHovered
	//(
	//	ImGuiHoveredFlags_AllowWhenBlockedByPopup |
	//	ImGuiHoveredFlags_AllowWhenBlockedByActiveItem
	//);

	//if (bCheck) //위에하나라도 트루면 픽킹이안된다.
	//	return;
	if (texture)
	{
		ImVec2 windowPos = ImGui::GetCursorPos() + ImGui::GetWindowPos();
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		ImVec2 firstMousePos = ImGui::GetIO().MouseClickedPos[0];
		ImVec2 lastMousePos;
		
		this->gridColor= D3DXCOLOR(0.5f, 1,4.3f, 1);
		
		
		
		if (ImGui::IsMouseDown(0) )
		{
			lastMousePos = ImGui::GetMousePos();
			drawList->AddRectFilled(firstMousePos, lastMousePos, gridColor);
			
			mouses.clear();
			bRender = false;
			
	    }
		if (ImGui::IsMouseReleased(0))
		{

			lastMousePos = ImGui::GetMousePos();

			mouses.emplace_back(lastMousePos);
			bRender = true;
		}
		if (bRender)
		{
			for (auto mouse : mouses)
				drawList->AddRectFilled(firstMousePos, mouse, gridColor);
			
		}
	}

}


