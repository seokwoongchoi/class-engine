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
	const Keyframe& GetCurrentKeyframe();//���� ���õ� ���ϸ��̼��� ���° �������� �������°�.

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
	map<string, Animation*>animationTable; //map�� �˻��������� ��ȯ�� ������.
};

