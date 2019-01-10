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
	prevTime = chrono::high_resolution_clock::now(); //���� �ð� ��ȯ
	
	return true;
}

void Time::Update()
{
	auto curTime = chrono::high_resolution_clock::now();
	chrono::duration<double, milli> ms = curTime - prevTime;//����ð�
	//��������, �и��β�����.������ �� ũ�⶧���� �����ѽð����Ҽ��ִ�.

	prevTime = curTime; //����ð��� ����ð��� ���.

	deltaTimeMs = static_cast<float>(ms.count());
	deltaTimeSec = static_cast<float>(ms.count() *0.001);
	
}
