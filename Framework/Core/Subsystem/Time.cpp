#include "stdafx.h"
#include "Time.h"

Time::Time(Context * context)
	:ISubsystem(context)
	,deltaTimeMs(0.0f)
	,deltaTimeSec(0.0f)
{
}

Time::~Time()
{
}

const bool Time::Initialize()
{
	prevTime = chrono::high_resolution_clock::now(); //현재 시간 반환
	
	return true;
}

void Time::Update()
{
	auto curTime = chrono::high_resolution_clock::now();
	chrono::duration<double, milli> ms = curTime - prevTime;//경과시간
	//더블형태, 밀리로꺼낸다.더블이 더 크기때문에 정밀한시간구할수있다.

	prevTime = curTime; //현재시간은 경과시간이 됬다.

	deltaTimeMs = static_cast<float>(ms.count());
	deltaTimeSec = static_cast<float>(ms.count() *0.001);
	
}
