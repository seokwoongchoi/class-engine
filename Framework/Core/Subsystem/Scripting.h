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
	void ReturnContext(class asIScriptContext* ctx); //인터페이스때문에 내부할당이 되있는것을 되돌려준다.
	//풀링

	//Calls
	const bool ExecuteCall//호출실행
	(
		class asIScriptFunction* scriptFunc,
		class asIScriptObject* obj //객체
	);

	//Module
	void DiscardModule(const string& moduleName); //특정모듈을 삭제할때사용
	
	
	
	void Clear();


private:
	void LogExceptionInfo(class asIScriptContext* ctx);//예외상의 정보를 빼오는것
	void Message_CallBack(const struct asSMessageInfo& msg);//특정 메세지정보를 가져오는것
private:
	class asIScriptEngine* scriptEngine; //angel script interpace
	vector<class asIScriptContext*> ctxs;
};
