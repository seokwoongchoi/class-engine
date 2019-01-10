#pragma once
#include "ISubsystem.h"
class Time :public ISubsystem
{
public:
	Time(class Context* context);
	virtual ~Time();

	const float& GetDeltaTimeMs()const { return deltaTimeMs; }
	const float& GetDeltaTimeSec() const { return deltaTimeSec; }

	const bool Initialize() override;
	void Update();

private:
	float deltaTimeMs;
	float deltaTimeSec;

	chrono::high_resolution_clock::time_point prevTime;
};