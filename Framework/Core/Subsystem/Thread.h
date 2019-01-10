#pragma once
#include "ISubsystem.h"

class Task
{
public:
	Task(function<void()>&&func)//r���� ����
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


class Thread :public ISubsystem//������� �����ư��鼭 ���Ѵ�.
{//�ϳ��� ���μ����� �ڿ����� �����ؼ� ������ ���� �߻��Ѵ�. 
public:
	Thread(class Context* context);
	virtual ~Thread();

	const bool Initialize()override;
	void Invoke();//�����ϴ�.�ϳ��� �����带 �����Ų��.
	 template<typename Function>
	 void AddTask(Function&& func);
private:
	vector<thread>threads;//thread�� stl
	queue<Task*> tasks;//fifo
	mutex taskMutex;
	condition_variable conditionVar; //���Ǻ��� ������鰣�� ���,,api�� �޼��������� ������鿡�� �����������.
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
	unique_lock<mutex> lock(taskMutex);// �������� �������� ��װ� ���°��� �����ϰ� �Ҽ��ִ�.

	tasks.push(new Task(bind(forward<Function>(func))));
	//ť���ְ�
	lock.unlock(); //������
	conditionVar.notify_one(); //������ �ѳ��� ������Ѷ�.
}
