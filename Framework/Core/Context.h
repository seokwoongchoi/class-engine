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
			SAFE_DELETE(subsystems[i]);//�ڿ������� ����� �مf��. 0���Ϻη� �ȵ��� �ߴ�.
	}

	//void UpdateSubsystem()
	//{//timer���� ���� ����ؼ� ������Ʈ �Ǿ��ϴϱ� ���� ������ش�
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
		if (typeid(T) == typeid(*subsystem))//ISubSystemŬ������ ���´�
			return static_cast<T*>(subsystem);//Ÿ�Ծ��̵� �ȿ� ������ ���̸��� ���´� subsystem�� ������ 
	}
	return nullptr;
}
