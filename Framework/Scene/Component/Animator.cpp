#include "stdafx.h"
#include "Animator.h"


Animator::Animator(class Context * context
	, class GameObject* gameobject,
	class Transform* transform)
	:IComponent(context,gameobject,transform)
	,animationMode(AnimationMode::Stop)
	,curClipNum(0)
	,frameTimer(0.0f)
	,currentAnimation(nullptr)
{
	timer = context->GetSubsystem<Time>();
	resourceManager = context->GetSubsystem<ResourceManager>();
}


Animator::~Animator()
{
}

void Animator::OnInitialize()
{
}

void Animator::OnStart()
{
}

void Animator::OnUpdate()
{
	bool bCheck = true;
	bCheck &= currentAnimation != nullptr;
	bCheck &= animationMode == AnimationMode::Play;

	if (bCheck)
	{
		frameTimer += timer->GetDeltaTimeMs();//1000분의 1초 

		if (frameTimer > currentAnimation->GetkeyFrameFromIndex(curClipNum).time)
		{
			curClipNum++;

			switch (currentAnimation->GetRepeatType())
			{
			case AnimationRepeatType::Once:

				if (curClipNum >= currentAnimation->GetKeyframeSize())
				{
					curClipNum = currentAnimation->GetKeyframeSize() - 1;
					Pause();
				}
				break;
			case AnimationRepeatType::Loop:
				curClipNum %= currentAnimation->GetKeyframeSize();//루프 알고리즘
				break;
			}
			frameTimer = 0.0f;

		}
	}
}

void Animator::OnStop()
{
}

void Animator::OnDestroy()
{
}

const Keyframe & Animator::GetCurrentKeyframe()
{
	assert(GetCurrentAnimation() != nullptr);
	return currentAnimation->GetkeyFrameFromIndex(curClipNum);
}

void Animator::SetCurrentAnimation(const string & animationName)
{
	assert(animationTable.count(animationName) > 0);
	currentAnimation = animationTable[animationName];
}

void Animator::AddAnimation(const string & filePath)
{
	auto animation = resourceManager->Load<Animation>(filePath);
	AddAnimation(animation);
}

void Animator::AddAnimation(Animation * animation)
{
	assert(animationTable.count(animation->GetResourceName()) < 1);
	animationTable[animation->GetResourceName()] = animation;
}

void Animator::Play()
{
	animationMode = AnimationMode::Play;
	frameTimer = 0.f;
}

void Animator::Stop()
{
	animationMode = AnimationMode::Stop;
	frameTimer = 0.f; 
	curClipNum = 0;
}

void Animator::Pause()
{
	animationMode = AnimationMode::Pause;
}

