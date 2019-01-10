#include "stdafx.h"
#include "IconProvider.h"
#include "../ImGui/Source/imgui.h"

static Thumbnail noThumbail;

void IconProvider::Initialize(Context * context)
{
	this->context = context;
	
	Load("../_Assets/Icon/AudioSourceGizmo.png",IconType::Audio);
	Load("../_Assets/Icon/CameraGizmo.png", IconType::Camera);
	Load("../_Assets/Icon/LightGizmo.png", IconType::Light);
	Load("../_Assets/Icon/folder.png", IconType::Folder);
	Load("../_Assets/Icon/file.png", IconType::File);
	Load("../_Assets/Icon/playButton.png", IconType::Play);
	Load("../_Assets/Icon/pauseButton.png", IconType::Pause);
	Load("../_Assets/Icon/stopButton.png", IconType::Stop);
	Load("../_Assets/Icon/log_info.png", IconType::Log_Info);
	Load("../_Assets/Icon/log_warning.png", IconType::Log_Warning);
	Load("../_Assets/Icon/log_error.png", IconType::Log_Error);
	
}

const Thumbnail & IconProvider::Load(const string & filePath, const IconType & type)
{
	if (type != IconType::Custom)//우리가원하는 그림넣는게 custom 파일을 찾아야한다.
	{
		for (auto& thumbnail : thumbnails)
		{
			if (thumbnail.type == type)
				return thumbnail;
		}
	}
	else
	{
		for (auto& thumbnail : thumbnails)
		{
			if (thumbnail.filePath == filePath)
				return thumbnail;
		}
	}

	if (FileSystem::IsDirectory(filePath))
		return GetThumbnailFromType(IconType::Folder);
	if (FileSystem::IsSupportImageFile(filePath))
	{
		auto texture = new Texture2D(context);
		texture->LoadFromFile(filePath);

		thumbnails.emplace_back(type, texture, filePath);
		
		
		
		//방금 만든객체를 내보내줘야한다.
		return thumbnails.back();
	}
	return GetThumbnailFromType(IconType::File);//폴더 경로가 들어오면 폴더가 나오고 이미지파일이 아니라 xml파일이라던가하면
	//그냥 그 파일 이미지가 나오게한다. 텍스쳐가아니라.
}


ID3D11ShaderResourceView * IconProvider::GetShaderResourceFromType(const IconType & type)
{
	return Load("",type).texture->GetShaderResourceView();
}

ID3D11ShaderResourceView * IconProvider::GetShaderResourceFromPath(const string & filePath)
{
	return Load(filePath).texture->GetShaderResourceView();
}

const bool IconProvider::ImageButton(const IconType & type, const float & size)
{
	bool bPressed = ImGui::ImageButton
	(
		GetShaderResourceFromType(type),
		ImVec2(size,size)//이 사이즈만큼의 이미지를 가진 아이콘이 나온다.
	);

	return bPressed;
}

const bool IconProvider::ImageButton(const string & filePath, const float & size)
{
	bool bPressed = ImGui::ImageButton
	(
		GetShaderResourceFromPath(filePath),
		ImVec2(size, size)//이 사이즈만큼의 이미지를 가진 아이콘이 나온다.
	);

	return bPressed;
}

const Thumbnail & IconProvider::GetThumbnailFromType(const IconType & type)
{
	for (auto& thumbnail : thumbnails)
	{
		if (thumbnail.type == type) return thumbnail;

	}
	return noThumbail;
}
