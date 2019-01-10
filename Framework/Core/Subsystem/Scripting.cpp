#include "stdafx.h"
#include "Scripting.h"
#include <AngelScript\angelscript.h>
#include <AngelScript\scriptstdstring\scriptstdstring.cpp>
#include "../../Scripting/ScriptInterface.h"


Scripting::Scripting(Context * context)
	:ISubsystem(context)
	, scriptEngine(nullptr)
{
}

Scripting::~Scripting()
{
	Clear();

	if (scriptEngine)
	{
		scriptEngine->ShutDownAndRelease();
		scriptEngine = nullptr;
	}
}

const bool Scripting::Initialize()
{
	scriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	assert(scriptEngine);

	RegisterStdString(scriptEngine);

	auto scriptInterface = new ScriptInterface();
	scriptInterface->Register(context, scriptEngine); //우리가 가지고있는 게임오브젝트를 넣어준다.엔젤스크립트에서 인식할수있게

	scriptEngine->SetMessageCallback
	(
		asMETHOD(Scripting, Message_CallBack),
		this,
		asCALL_THISCALL
	);

	scriptEngine->SetEngineProperty(asEP_BUILD_WITHOUT_LINE_CUES, true);

	SAFE_DELETE(scriptInterface);

	return true;
}

asIScriptEngine * Scripting::GetAsIScriptEngine()
{
	return scriptEngine;
}



asIScriptContext * Scripting::RequestContext()
{
	asIScriptContext* ctx = nullptr;
	if (ctxs.size())
	{
		ctx = *ctxs.rbegin();

		ctxs.pop_back();
	}
	else
		ctx = scriptEngine->CreateContext();


	return ctx;
}

void Scripting::ReturnContext(asIScriptContext * ctx)
{
	assert(ctx);
	ctxs.push_back(ctx);
	ctx->Unprepare();
}

const bool Scripting::ExecuteCall(asIScriptFunction * scriptFunc, asIScriptObject * obj)
{
	asIScriptContext* ctx = RequestContext();

	ctx->Prepare(scriptFunc);
	ctx->SetObject(obj);
	
	int result = ctx->Execute();

	if (result == asEXECUTION_EXCEPTION)
	{
		LogExceptionInfo(ctx);//에러찾기
		ReturnContext(ctx);//데이터풀에서 데이터를쓰고 다쓰면 다시 돌려준다
		return false;//걸렸다는거는 실행안됬다는거니가 false
	}

	ReturnContext(ctx);
	return true;
	//컨텍스요청해서 없으면 콘텍스츠를 만들고 ctx를 준비상태로바꾸고 오브젝트 셋팅하고
}

void Scripting::DiscardModule(const string & moduleName)
{
	scriptEngine->DiscardModule(moduleName.c_str());
}
void Scripting::Clear()
{
	for (auto ctx : ctxs) //포인터를 넘겨올때 혹시나 포인터가 안받아질까봐 &붙여준다.
		//복사본을받을것인지 원본을받을것인지
		ctx->Release();

	ctxs.clear();
	ctxs.shrink_to_fit();
}
void Scripting::LogExceptionInfo(asIScriptContext * ctx)
{
	string execoptionDescription = ctx->GetExceptionString();//현재에러가 어디서났는지 문자로 받아옴
	const asIScriptFunction* function = ctx->GetExceptionFunction();

	string functionDeclaration = function->GetDeclaration();
	string moduleName = function->GetModuleName();
	string scriptPath = function->GetScriptSectionName();
	string scriptFile = FileSystem::GetFrileNameFromPath(scriptPath);
	string excoptionLine = to_string(ctx->GetExceptionLineNumber());

}

void Scripting::Message_CallBack(const asSMessageInfo & msg)
{
	string fileName = FileSystem::GetIntactFileNameFromPath(msg.section);//section->위치경로
	string message = msg.message;
	
	string finalMessage;
	if (fileName != "")
		finalMessage = fileName + "" + message;
	else
		finalMessage = message;
}
