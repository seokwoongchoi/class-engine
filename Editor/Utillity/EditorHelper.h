#pragma once
#include "../ImGui/Source/imgui.h"
#include "../Utillity/IconProvider.h"

struct Item
{
	Item(const string& filePath, const Thumbnail& thumbnail)
		:filePath(filePath)
		, thumbnail(thumbnail)
	{
		label = FileSystem::GetFrileNameFromPath(filePath);
	}

	Thumbnail thumbnail;
	string filePath;
	string label;

};
class EditorHelper
{
public:
	static class GameObject* CurrentObject;

public:
	static const ImVec2 ToImVec2(const Vector2& vec) { return ImVec2(vec.x, vec.y); }
	static const ImVec4 ToImVec3(const Vector3& vec) { return ImVec4(vec.x, vec.y, vec.z, 0.0f); }
	static const ImVec4 ToImVec4(const D3DXVECTOR4& vec) { return ImVec4(vec.x, vec.y, vec.z, vec.w); }

	static const Vector2 ToDxVec2(const ImVec2& vec) { return Vector2(vec.x, vec.y); }
	static const Vector3 ToDxVec3(const ImVec4& vec) { return Vector3(vec.x, vec.y, vec.z); }
	static const D3DXVECTOR4 ToDxVec4(const ImVec4& vec) { return D3DXVECTOR4(vec.x, vec.y, vec.z, vec.w); }
};

static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)
{
	return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs)
{
	return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y);
}