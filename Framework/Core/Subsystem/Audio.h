#pragma once
#include "ISubsystem.h"
class Audio:public ISubsystem //���� �Ŵ���
{//dll->����,lib->����
public: 
	Audio(class Context* context);
	virtual ~Audio();

	FMOD::System* GetFMODSystem()const { return system; }

	const bool Initialize()override;
	void Update();
	
private:
	//class Transform* listener;
	FMOD::System* system; //system device�� context��Ȱ
	int maxChannel; // ������
	float distanceFactor; //�Ÿ������� �Ҹ� ũ��
	int result; //���Ʈ��
	bool bInitialized;//�ʱ�ȭ��� �ȉ���Ǵ� �ʱ�ȭ�ȵȻ��¿����� �����̾ȵǱ⶧���� �ʿ�


};