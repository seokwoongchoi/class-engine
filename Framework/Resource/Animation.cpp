#include "stdafx.h"
#include "Animation.h"

Animation::Animation(Context * context)
  :IResource(context)
	,repeatType(AnimationRepeatType::Once)
{
}

Animation::~Animation()
{
}

const Keyframe & Animation::GetkeyFrameFromIndex(const uint & index)
{
	assert(index < keyframes.size()); //안에가 트루여야지 넘어간다.
	return keyframes[index];
	
}


void Animation::AddKeyframe(const Keyframe & keyframe)
{
	keyframes.push_back(keyframe);

}

void Animation::SaveToFile(const string & saveFilePath)
{
	Xml::XMLDocument doc;
    Xml::XMLDeclaration* decl = doc.NewDeclaration();//메인으로 decl을 만들고 만들어진거를 doc에 링크해줘야한다.
	doc.LinkEndChild(decl);//doc의 첫번째 자식은 decl이다. 그러나 실직전인 첫번째 자식은 root이다. 

	Xml::XMLElement* root = doc.NewElement("SpriteAnimation");//하나의 원소에 이름을 달아준다.
	doc.LinkEndChild(root);//원소를 넣은것도 doc에 넣어준다.

	root->SetAttribute("AnimationName",name.c_str());
	root->SetAttribute("RepeatType", static_cast<uint>(repeatType));

	for (const auto& keyframe : keyframes)
	{
		Xml::XMLElement* firstElem = doc.NewElement("Keyframe");
		root->LinkEndChild(firstElem);

		firstElem->SetAttribute("TexturePath", keyframe.texture->GetResourcePath().c_str());
		firstElem->SetAttribute("OffsetX",keyframe.offset.x);
		firstElem->SetAttribute("OffsetY", keyframe.offset.y);
		firstElem->SetAttribute("SizeX", keyframe.size.x);
		firstElem->SetAttribute("SizeY", keyframe.size.y);
		firstElem->SetAttribute("Time", keyframe.time);
	}
	doc.SaveFile(saveFilePath.c_str());
}

void Animation::LoadFromFile(const string & loadFilePath)
{
	Xml::XMLDocument doc;
	Xml::XMLError error = doc.LoadFile(loadFilePath.c_str());
	assert(error == Xml::XMLError::XML_SUCCESS);
	Xml::XMLElement* root = doc.FirstChildElement();//doc가가진 첫번째 자식원소를 꺼내준다.
	name = root->Attribute("AnimationName");
	repeatType = static_cast<AnimationRepeatType>(root->IntAttribute("RepeatType"));

	Xml::XMLElement* firstElem = root->FirstChildElement();
	for (; firstElem != nullptr; firstElem = firstElem->NextSiblingElement()) //sibling->형제 root밑에 딸려있는것들을 체크할수있다.
	{
		Keyframe keyframe;
		string texturePath = firstElem->Attribute("TexturePath");

		keyframe.texture = resourceManager->Load<Texture2D>(texturePath);
		keyframe.offset.x = firstElem->FloatAttribute("OffsetX");
		keyframe.offset.y = firstElem->FloatAttribute("OffsetY");
		keyframe.size.x = firstElem->FloatAttribute("SizeX");
		keyframe.size.y = firstElem->FloatAttribute("SizeY");
		keyframe.time = firstElem->FloatAttribute("Time");

		keyframes.push_back(keyframe);
	}
	
}
