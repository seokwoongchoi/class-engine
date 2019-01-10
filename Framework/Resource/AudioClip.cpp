#include "stdafx.h"
#include "AudioClip.h"

AudioClip::AudioClip(Context * context)
	:IResource(context)
	, sound(nullptr)
	, channel(nullptr)
	, playMode(PlayMode::Sound)
	, loopMode(FMOD_LOOP_OFF)
	, rolloffMode(FMOD_3D_LINEARROLLOFF)
	, minDistance(1.0f)
	, maxDistance(10000.f)
{
	system = context->GetSubsystem<Audio>()->GetFMODSystem();
}

AudioClip::AudioClip(const AudioClip & rhs)
	:IResource(rhs.context)
	, sound(nullptr)
	, channel(nullptr)
	, playMode(rhs.playMode)
	, loopMode(rhs.loopMode)
	, rolloffMode(rhs.rolloffMode)
	, minDistance(rhs.minDistance)
	, maxDistance(rhs.maxDistance)
{
	system = rhs.system;
	LoadFromFile("../_Assets/Audio/"+rhs.filePath);
}

AudioClip::~AudioClip()
{
	if (!sound) return;

	result = sound->release();
	assert(result == FMOD_OK);
}

void AudioClip::Play()
{
	//���尡 �÷��� ������ üũ�ؾ��Ѵ�
	if (IsChannelValid())
	{
		bool bPlaying = false;
		result = channel->isPlaying(&bPlaying);
		assert(result == FMOD_OK);
		
		//���� ������̸� ����
		if (bPlaying) return;
	}
	//���� �÷��� 
	result = system->playSound(sound, nullptr, false, &channel);
	assert(result == FMOD_OK);
}

void AudioClip::Pause()
{
	if (!IsChannelValid())
	{
		return;
	}
	//���尡 �Ͻ����� �������� üũ
	bool bPaused = false;
	result = channel->getPaused(&bPaused);
	assert(result == FMOD_OK);
	
	//���尡 �Ͻ����� �����̸� ����
	if (bPaused)
		return;


	//���� �Ͻ�����
	result = channel->setPaused(true);
	assert(result == FMOD_OK);
}

void AudioClip::Update()
{
	//TODO:
}

void AudioClip::SetLoop(const bool & bLoop)
{
	loopMode = bLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

	if (!sound) return;

	if (bLoop) {
		result = sound->setLoopCount(-1);
		assert(result == FMOD_OK);
	}

	result = sound->setMode(GetSoundMode());
	assert(result == FMOD_OK);
}

void AudioClip::SetVolume(const float & volume)
{
	if (!IsChannelValid()) return;
	result = channel->setVolume(volume);
	assert(result == FMOD_OK);
}

void AudioClip::SetMute(const bool & bMute)
{
	if (!IsChannelValid()) return;
	result = channel->setMute(bMute);
	assert(result == FMOD_OK);
}

void AudioClip::SetPriority(const int & priority)
{
	if (!IsChannelValid()) return;
	result = channel->setPriority(priority);
	assert(result == FMOD_OK);
}

void AudioClip::SetPitch(const float & pitch)
{
	if (!IsChannelValid()) return;
	result = channel->setPitch(pitch);
	assert(result == FMOD_OK);
}

void AudioClip::SetPan(const float & pan)
{
	if (!IsChannelValid()) return;
	result = channel->setPan(pan);
	assert(result == FMOD_OK);
}

const bool AudioClip::IsPlaying()
{
	if (!IsChannelValid()) return false;

	bool bPlaying = false;
	result = channel->isPlaying(&bPlaying);
	assert(result == FMOD_OK);
	return bPlaying;
	
}

void AudioClip::SaveToFile(const string & saveFilePath)
{
}

void AudioClip::LoadFromFile(const string & loadFilePath)
{
	switch (playMode)
	{
	case PlayMode::Sound:CreateSound(loadFilePath); break;
	case PlayMode::Stream:CreateStream(loadFilePath); break;
	}
}

void AudioClip::CreateSound(const string & filePath)
{
	result = system->createSound(filePath.c_str(), GetSoundMode(), nullptr, &sound);
	assert(result == FMOD_OK);
	result = sound->set3DMinMaxDistance(minDistance, maxDistance);
	assert(result == FMOD_OK);
}

void AudioClip::CreateStream(const string & filePath)
{
	result = system->createStream(filePath.c_str(), GetSoundMode(), nullptr, &sound);
	assert(result == FMOD_OK);
	result = sound->set3DMinMaxDistance(minDistance, maxDistance);
	assert(result == FMOD_OK);
}

const int AudioClip::GetSoundMode() const
{
	return FMOD_3D | loopMode | rolloffMode;
}

const bool AudioClip::IsChannelValid() const
{//ä���� ��ȿ�Ѱ� �Ǵ�
	if (!channel) return false;
	
	bool dummy;
	return channel->isPlaying(&dummy) == FMOD_OK; //ä���� ��ȿ�ϴ�.
}
