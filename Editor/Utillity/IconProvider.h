#pragma once


enum class IconType :uint
{
	Audio,
	Camera,
	Light,
	Folder,
	File,
	Play,
	Pause,
	Stop,
	Custom,
	Log_Info,
	Log_Error,
	Log_Warning,
};

struct Thumbnail//미리보기 이미지
{
	Thumbnail()
		:type(IconType::Custom)
		,texture(nullptr)
		,filePath("")
	{}
	Thumbnail(const IconType& type,Texture2D* texture, const string& filePath)
		:type(type)
		,texture(texture)
		,filePath(filePath)
	{}

	IconType type;
	Texture2D* texture;

	string filePath;
};
class IconProvider
{public:
	static IconProvider& Get()
	{
		static IconProvider instance;
		return instance;
	}

	void Initialize(class Context* context);

	const Thumbnail& Load
	(
		const string& filePath,
		const IconType& type =IconType::Custom
		
	);

	//texture2d안에 srv같은것들을 빼온다.
	ID3D11ShaderResourceView* GetShaderResourceFromType(const IconType& type);
	ID3D11ShaderResourceView* GetShaderResourceFromPath(const string& filePath);


	const bool ImageButton(const IconType& type,const float& size);
	const bool ImageButton(const string& filePath, const float& size);
	

private:
	IconProvider(){}
	 ~IconProvider(){}

	 const Thumbnail& GetThumbnailFromType(const IconType& type);

private:
	class Context* context;
	vector<Thumbnail> thumbnails;


};

