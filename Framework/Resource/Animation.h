#pragma once
#include "IResource.h"
enum class AnimationRepeatType :uint
{
	Once,Loop
};

struct Keyframe
{
	Texture2D* texture;
	Vector2 offset;
	Vector2 size;
	float time;
};
class Animation: public IResource
{
public:
	Animation(class Context* context);
	virtual ~Animation();

	
	const AnimationRepeatType& GetRepeatType() const { return repeatType; }//
	const Keyframe& GetkeyFrameFromIndex(const uint& index);//몇번프레임인지 빼온다.
	const uint GetKeyframeSize() const {	return keyframes.size();}//
	

	void SetRepeatType(const AnimationRepeatType& repeatType) { this->repeatType = repeatType; }
	void AddKeyframe(const Keyframe& keyframe);
	
	//void SetName(const string& name) { this->name = name; }//
	
	

	virtual void SaveToFile(const string& saveFilePath)override;
	virtual void LoadFromFile(const string& loadFilePath)override;
	


private:
	class Context* context;
	AnimationRepeatType repeatType;
	vector<Keyframe>keyframes;

};