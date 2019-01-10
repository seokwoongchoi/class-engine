#pragma once
#include "IComponent.h"
class Animator:public IComponent
{
public:
	Animator(
		class Context * context
	,  class GameObject* gameobject,
		class Transform* transform
	);
	virtual ~Animator();

	 void OnInitialize() override;
	 void OnStart() override;
	 void OnUpdate() override;
	 void OnStop() override;
	 void OnDestroy() override;



	Animation* GetCurrentAnimation()const { return currentAnimation; }	
	const Keyframe& GetCurrentKeyframe();//현재 선택된 에니메이션의 몇번째 프래임을 꺼내오는것.

	void SetCurrentAnimation(const string& animationName);
	void AddAnimation(const string& filePath);
	void AddAnimation(Animation* animation);

	void Play();
	void Stop();
	void Pause();


	const bool IsPlaying() { return animationMode == AnimationMode::Play; }
	const bool IsStop() { return animationMode == AnimationMode::Stop; }
	const bool IsPause() { return animationMode == AnimationMode::Pause; }

private:
	enum class AnimationMode :uint
	{
		Play,Stop,Pause
	};

private:
	
	class ResourceManager* resourceManager;
	class Time* timer;

	AnimationMode animationMode;
	uint curClipNum;
	float frameTimer;

	Animation* currentAnimation;
	map<string, Animation*>animationTable; //map은 검색은빠른데 순환은 느리다.
};

