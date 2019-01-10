#pragma once
#include "IComponent.h"
class AudioSource:public IComponent
{
public:
	AudioSource(class Context * context
		, class GameObject* gameobject,
		class Transform* transform);//기본생성자(), 복사생성자(const&), 이동생성자(const&&)<-주소로 움직인다.
	virtual ~AudioSource();

	void OnInitialize() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnStop() override;
	void OnDestroy() override;

	void SetAudioClip(const string& filePath);
	void SetAudioClip(class AudioClip* audioClip);

	void Play();
	void Stop();

	const bool& IsLoop()	const { return bLoop; }
	const bool& IsMute()	const { return bMute; }
	const int& GetPriority() const { return priority; }
	const float& GetVolume()	const { return volume; }
	const float& GetPitch()const { return pitch; }
	const float& GetPan()const { return pan; }


	void SetIsLoop(const bool&bLoop)	{ this->bLoop= bLoop; }
	void SetIsMute(const bool&bMute);
	void SetPriority(const int&priority);
	void SetVolume(const float&volume);
	void SetPitch(const float&pitch);
	void SetPan(const float& pan);
	
private:
	
	class AudioClip* audioClip;
	string filePath;
	bool bMute;
	bool bLoop;
	int priority;
	float volume;
	float pitch;
	float pan;
};

