#pragma once
#include "ISubsystem.h"
class Audio:public ISubsystem //사운드 매니져
{//dll->동적,lib->정적
public: 
	Audio(class Context* context);
	virtual ~Audio();

	FMOD::System* GetFMODSystem()const { return system; }

	const bool Initialize()override;
	void Update();
	
private:
	//class Transform* listener;
	FMOD::System* system; //system device와 context역활
	int maxChannel; // 재생목록
	float distanceFactor; //거리에따른 소리 크기
	int result; //어썰트용
	bool bInitialized;//초기화됬냐 안됬냐판단 초기화안된상태에서는 실행이안되기때문에 필요


};