
#pragma once
#include "IWidget.h"
#include "../../Framework/Log/ILogger.h"
struct LogPair 
{
	string text;
	int type;
};

class EngineLogger :public ILogger
{
public:
	void SetCallback(function<void(const LogPair&)>&& func)//int type =10; �� ���� �� ���� �������� �˺������� �ٷι޾ƿ����Ѵ�.
		//�޸� ���డ��.
	{
		this->func = forward<function<void(const LogPair&)>>(func); //forward �������� �޾ƿ°��� �˺����� �ٲ��ش�.
		//�޾ƿ� �˺����� ������������ �ޱ����� �ɽ���
	}
	void Log(const string& text, const int& type)	override
	{
		LogPair pair;
		pair.text = text;
		pair.type = type;

		func(pair);
	}
private:
	function<void(const LogPair&)>func;
};
class Widget_Log :public IWidget
{
public:
	Widget_Log(class Context* context);
	virtual ~Widget_Log();

	//void Initialize(class Context* context) override;
	void Render()override;

	void AddLog(const LogPair& logPair);
	void Clear();
private:
	EngineLogger* logger;
	//���� deque ����
	deque<LogPair> logs;
	uint maxLogCount;
	bool bShowInfo;
	bool bShowWarning;
	bool bShowError;
	bool bScroll;
};

