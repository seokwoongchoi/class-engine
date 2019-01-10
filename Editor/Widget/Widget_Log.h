
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
	void SetCallback(function<void(const LogPair&)>&& func)//int type =10; 엘 벨류 알 벨류 엘벨류의 알벨류값을 바로받아오게한다.
		//메모리 절약가능.
	{
		this->func = forward<function<void(const LogPair&)>>(func); //forward 엘벨류로 받아온것을 알벨류로 바꿔준다.
		//받아온 알벨류를 엘벨류값으로 받기위한 케스팅
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
	//과제 deque 조사
	deque<LogPair> logs;
	uint maxLogCount;
	bool bShowInfo;
	bool bShowWarning;
	bool bShowError;
	bool bScroll;
};

