#include "stdafx.h"
#include "AudioSource.h"

AudioSource::AudioSource(class Context * context
	, class GameObject* gameobject,
	class Transform* transform)
	:IComponent(context,gameobject,transform)
	, audioClip(nullptr)
	, filePath("")
	, bMute(false)
	, bLoop(false)
	, priority(128)
	, volume(1.0f)
	, pitch(0.0f)
	, pan(0.0f) //좌우 소리대칭
{
}

AudioSource::~AudioSource()
{
	SAFE_DELETE(audioClip);//원본은 리소스매니져에 있고 여기서 복사본을 지운다.
}

void AudioSource::OnInitialize()
{
}

void AudioSource::OnStart()
{
}

void AudioSource::OnUpdate()
{
}

void AudioSource::OnStop()
{
}

void AudioSource::OnDestroy()
{
}


void AudioSource::SetAudioClip(const string & filePath)
{
	SAFE_DELETE(audioClip);

	auto resourceManager = context->GetSubsystem<ResourceManager>();
	auto clip = resourceManager->Load<AudioClip>(filePath);
	audioClip = new AudioClip(*clip); //클립의 주소가 복사된다.
}

void AudioSource::SetAudioClip(AudioClip * audioClip)
{
	SAFE_DELETE(this->audioClip);
	this->audioClip = new AudioClip(*audioClip);
}

void AudioSource::Play()
{
	if (!audioClip)return;
	audioClip->Play();
	audioClip->SetMute(bMute);
	audioClip->SetLoop(bLoop);
	audioClip->SetVolume(volume);
	audioClip->SetPriority(priority);
	audioClip->SetPan(pan);
}

void AudioSource::Stop()
{
	if (!audioClip)return;
	audioClip->Stop();
}

void AudioSource::SetIsMute(const bool & bMute)
{
	if (!audioClip) return;
	if (this->bMute == bMute) return;

	this->bMute = bMute;
	audioClip->SetMute(this->bMute);
}

void AudioSource::SetPriority(const int & priority)
{
	//채널 우선순위
	//0~256까지의 우선순위
	//128이 기본

	if (!audioClip)return;
	if (this->priority == priority)return;
	this->priority = Math::Clamp(priority, 0, 256);
	audioClip->SetPriority(this->priority);
}

void AudioSource::SetVolume(const float & volume)
{
	if (!audioClip)return;
	if (this->volume == volume)return;
	this->volume = Math::Clamp(volume, 0.f, 1.f);
	audioClip->SetVolume(this->volume);
}

void AudioSource::SetPitch(const float & pitch)
{
	if (!audioClip)return;
	if (this->pitch == pitch)return;
	this->pitch = Math::Clamp(pitch, 0.f, 3.f);
	audioClip->SetPitch(this->pitch);
}

void AudioSource::SetPan(const float & pan)
{
	if (!audioClip)return;
	if (this->pan == pan)return;
	this->pan = Math::Clamp(pan, -1.f, 1.f); //-1이면 왼쪽이 더커지고 1이면 오른쪽이 더 커진다.
	audioClip->SetPan(this->pan);
}
