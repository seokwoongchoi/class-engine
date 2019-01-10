#pragma once
#include"IResource.h"

enum class PlayMode :uint
{
	Sound, //�ѼҸ�
	Stream //�������(�뷮��ū���ϵ�)
};
class AudioClip:public IResource
{
public: AudioClip(class Context*context);//�⺻������
		AudioClip(const AudioClip& rhs);//���� ������
		virtual ~AudioClip();

		void Play();
		void Pause();
		void Stop()
		{
			if (!IsChannelValid())
			{
				return;
			}

			//���尡 �÷��� ������ üũ
			if (!IsPlaying()) return;
			//�ƴ϶�� ���� ����
			result = channel->stop();
			assert(result == FMOD_OK);

			channel = nullptr;
		}
		void Update();//�Ÿ������� �Ǵܰ����͵� ������Ʈ

		void SetLoop(const bool& bLoop);
		void SetVolume(const float& volume);
		void SetMute(const bool& bMute);
		void SetPriority(const int& priority);//�켱����
		
		void SetPitch(const float& pitch);
		void SetPan(const float& pan);

		const bool IsPlaying();//�÷������̳� �ƴϳ�


		virtual void SaveToFile(const string& saveFilePath)override;
		virtual void LoadFromFile(const string& loadFilePath)override;



private:
	void CreateSound(const string& filePath);
	void CreateStream(const string& filePath);

	const int GetSoundMode()const;
	const bool IsChannelValid()const;//ä���� ��ȿ���� �ƴ��� üũ

private:
	FMOD::System* system;
	FMOD::Sound* sound; //���� ��ü 
	FMOD::Channel* channel;//������� ���� null�̸� ������� �������ϳ����� ���

	PlayMode playMode;
	int loopMode;
	int rolloffMode; //�Ҹ� ���� ����
	float minDistance; //���ǼҸ��� �ִ��� ����
	float maxDistance; //���ǼҸ��� ������ ����
	int result;
};