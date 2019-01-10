#pragma once
#include"IResource.h"

enum class PlayMode :uint
{
	Sound, //총소리
	Stream //배경음악(용량이큰파일들)
};
class AudioClip:public IResource
{
public: AudioClip(class Context*context);//기본생성자
		AudioClip(const AudioClip& rhs);//복사 생성자
		virtual ~AudioClip();

		void Play();
		void Pause();
		void Stop()
		{
			if (!IsChannelValid())
			{
				return;
			}

			//사운드가 플레이 중인지 체크
			if (!IsPlaying()) return;
			//아니라면 사운드 중지
			result = channel->stop();
			assert(result == FMOD_OK);

			channel = nullptr;
		}
		void Update();//거리에대한 판단같은것들 업데이트

		void SetLoop(const bool& bLoop);
		void SetVolume(const float& volume);
		void SetMute(const bool& bMute);
		void SetPriority(const int& priority);//우선순위
		
		void SetPitch(const float& pitch);
		void SetPan(const float& pan);

		const bool IsPlaying();//플레이중이냐 아니냐


		virtual void SaveToFile(const string& saveFilePath)override;
		virtual void LoadFromFile(const string& loadFilePath)override;



private:
	void CreateSound(const string& filePath);
	void CreateStream(const string& filePath);

	const int GetSoundMode()const;
	const bool IsChannelValid()const;//채널이 유효한지 아닌지 체크

private:
	FMOD::System* system;
	FMOD::Sound* sound; //음원 객체 
	FMOD::Channel* channel;//재생중인 음원 null이면 재생중지 음악파일넣으면 재생

	PlayMode playMode;
	int loopMode;
	int rolloffMode; //소리 감쇄 관련
	float minDistance; //음악소리가 최대인 지점
	float maxDistance; //음악소리가 최저인 지점
	int result;
};