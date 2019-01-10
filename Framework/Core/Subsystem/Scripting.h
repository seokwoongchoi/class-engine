#pragma once
#include "ISubsystem.h"

class Scripting:public ISubsystem
{
public:
	Scripting(class Context* context);
	virtual ~Scripting();

	const bool Initialize()override;

	//Script Engine
	class asIScriptEngine* GetAsIScriptEngine();

	//Context
	class asIScriptContext* RequestContext();
	void ReturnContext(class asIScriptContext* ctx); //�������̽������� �����Ҵ��� ���ִ°��� �ǵ����ش�.
	//Ǯ��

	//Calls
	const bool ExecuteCall//ȣ�����
	(
		class asIScriptFunction* scriptFunc,
		class asIScriptObject* obj //��ü
	);

	//Module
	void DiscardModule(const string& moduleName); //Ư������� �����Ҷ����
	
	
	
	void Clear();


private:
	void LogExceptionInfo(class asIScriptContext* ctx);//���ܻ��� ������ �����°�
	void Message_CallBack(const struct asSMessageInfo& msg);//Ư�� �޼��������� �������°�
private:
	class asIScriptEngine* scriptEngine; //angel script interpace
	vector<class asIScriptContext*> ctxs;
};
