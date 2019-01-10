#pragma once
#include "ISubsystem.h"

class Task
{
public:
	Task(function<void()>&&func)//r벨류 참조
	{
		this->func = forward<function<void()>>(func);

	}
	void Execute()
	{
		func();
	}
private:
	function<void()> func;
};


class Thread :public ISubsystem//쓰레드는 번갈아가면서 일한다.
{//하나의 프로세서의 자원들을 공유해서 문제가 많이 발생한다. 
public:
	Thread(class Context* context);
	virtual ~Thread();

	const bool Initialize()override;
	void Invoke();//실행하다.하나의 쓰레드를 실행시킨다.
	 template<typename Function>
	 void AddTask(Function&& func);
private:
	vector<thread>threads;//thread는 stl
	queue<Task*> tasks;//fifo
	mutex taskMutex;
	condition_variable conditionVar; //조건변수 쓰레드들간에 통신,,api의 메세지같은거 쓰레드들에게 명령을내린다.
	uint threadCount;
	bool bStopping;
};

template<typename Function>
inline void Thread::AddTask(Function && func)
{
	if (threads.empty())
	{
		func();
		return;
	}
	unique_lock<mutex> lock(taskMutex);// 락가드의 상위버전 잠그고 여는것을 유연하게 할수있다.

	tasks.push(new Task(bind(forward<Function>(func))));
	//큐에넣고
	lock.unlock(); //락해제
	conditionVar.notify_one(); //쓰레드 한놈을 실행시켜라.
}
