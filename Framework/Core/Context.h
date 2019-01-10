#pragma once
#include "stdafx.h"
#include "./Subsystem/ISubsystem.h"

class Context
{
public:
	Context() {}
	virtual ~Context() 
	{
		/*for (auto subsystem : subsystems)
			SAFE_DELETE(subsystem);*/
		
		for (uint i = subsystems.size() - 1; i > 0; i--)
			SAFE_DELETE(subsystems[i]);//뒤에서부터 지우게 바꿧다. 0은일부러 안들어가게 했다.
	}

	//void UpdateSubsystem()
	//{//timer같은 경우는 계속해서 업데이트 되야하니까 따로 만들어준다
	//	for (auto subsystem : subsystems)
	//		subsystem->Update();
	//}

	void RegistSubsystem(class ISubsystem* subsystem)
	{
		if (!subsystem)
			assert(false);

		//subsystem->Initialize();
		subsystems.push_back(subsystem);
	}

	template <typename T>
	T* GetSubsystem();

private:
	vector<class ISubsystem*> subsystems;
};

template<typename T>
inline T * Context::GetSubsystem()
{
	for (auto subsystem : subsystems)
	{
		if (typeid(T) == typeid(*subsystem))//ISubSystem클래스가 나온다
			return static_cast<T*>(subsystem);//타입아이디 안에 넣으면 그이름이 나온다 subsystem을 넣으면 
	}
	return nullptr;
}
