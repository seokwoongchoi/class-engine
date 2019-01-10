#pragma once
#include "stdafx.h"
enum class ResourceType : uint //다른곳에 똑같은이름이 있어도 충돌되지 않는다
{//번호 바로 매칭이안된다.
	Unknown,
	Texture,
	Shader,
	Animation,
	Audio,
	Model
};
class IResource //->interface 다중상속을 받아도 꼬임의 걱정이 없다.
{
public:
	template<typename T>
	static ResourceType DeduceResourceType(); //추론하다
public:
	IResource(class Context* context)
		:context(context)
	{
		resourceManager = context->GetSubsystem<ResourceManager>();
	}
	virtual ~IResource(){}

	const string& GetResourceName()const { return name; }
	const string& GetResourcePath()const { return filePath; }
	const ResourceType& GetResourceType()const { return type; }

	void  SetResourceName(const string& name) { this-> name=name; }
	void  SetResourcePath(const string& filePath) { this-> filePath=filePath; }
	void SetResourceType(const ResourceType& type) { this->type=type; }

	virtual void SaveToFile(const string& saveFilePath)
	{

	}
	virtual void LoadFromFile(const string& loadFilePath)
	{

	}


protected:
	class Context* context;
   class ResourceManager* resourceManager;

	string name;
	string filePath;
	ResourceType type;
};

template<typename T>
inline ResourceType IResource::DeduceResourceType()
{
	string resourceType = typeid(T).name();
	ResourceType enumType = ResourceType::Unknown;
	if (resourceType.find("Texture") != string::npos)//저문자열이 있는 값의 공간을 찾아준다. npos와 같지않다는것은 공간을 찾았다는뜻
		enumType = ResourceType::Texture;
	else if (resourceType.find("Shader") != string::npos)
		enumType = ResourceType::Shader;
	else if (resourceType.find("Animation") != string::npos)
		enumType = ResourceType::Animation;
	else if (resourceType.find("Audio") != string::npos)
		enumType = ResourceType::Audio;
	else if (resourceType.find("Model") != string::npos)
		enumType = ResourceType::Model;
	return enumType;
}
