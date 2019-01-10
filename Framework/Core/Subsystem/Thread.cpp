#include "stdafx.h"
#include "Thread.h"

Thread::Thread(Context * context)
	:ISubsystem(context)
	,bStopping(false)
{
	threadCount = thread::hardware_concurrency()-1;//컴퓨터마다 돌릴수있는 코어 갯수만큼 나온다 동기화갯수 하나빼는거는 메인스레드
}

Thread::~Thread()
{
	//모든쓰레드들이 작업하고있다면
	unique_lock<mutex> lock(taskMutex);
	bStopping = true;

	lock.unlock();

	conditionVar.notify_all();

	for (auto& thread : threads)
		thread.join(); //쓰레드들이 모두끝날때까지 먼저끝난놈들은 대기하다가 한꺼번에 클리어

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

		conditionVar.wait(lock, [this]() {return !tasks.empty() || bStopping; });//헤드에서 깨운 쓰레드한태 대기하라고 신호준다.

		if (bStopping && tasks.empty()) return;

		task = tasks.front();
		tasks.pop(); //꺼내온거 지운다

		lock.unlock();
		task->Execute();

		SAFE_DELETE(task);
	}
}
