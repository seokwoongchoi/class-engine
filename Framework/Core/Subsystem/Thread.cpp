#include "stdafx.h"
#include "Thread.h"

Thread::Thread(Context * context)
	:ISubsystem(context)
	,bStopping(false)
{
	threadCount = thread::hardware_concurrency()-1;//��ǻ�͸��� �������ִ� �ھ� ������ŭ ���´� ����ȭ���� �ϳ����°Ŵ� ���ν�����
}

Thread::~Thread()
{
	//��羲������� �۾��ϰ��ִٸ�
	unique_lock<mutex> lock(taskMutex);
	bStopping = true;

	lock.unlock();

	conditionVar.notify_all();

	for (auto& thread : threads)
		thread.join(); //��������� ��γ��������� ������������� ����ϴٰ� �Ѳ����� Ŭ����

	threads.clear();
	threads.shrink_to_fit();
	
}

const bool Thread::Initialize()
{
	for (uint i = 0; i < threadCount; i++)
		threads.emplace_back(thread(&Thread::Invoke,this));

	return true;
}

void Thread::Invoke()
{
	Task* task = nullptr;
	while (true)
	{
		unique_lock<mutex> lock(taskMutex);

		conditionVar.wait(lock, [this]() {return !tasks.empty() || bStopping; });//��忡�� ���� ���������� ����϶�� ��ȣ�ش�.

		if (bStopping && tasks.empty()) return;

		task = tasks.front();
		tasks.pop(); //�����°� �����

		lock.unlock();
		task->Execute();

		SAFE_DELETE(task);
	}
}
