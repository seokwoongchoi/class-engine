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
	scriptInterface->Register(context, scriptEngine); //�츮�� �������ִ� ���ӿ�����Ʈ�� �־��ش�.������ũ��Ʈ���� �ν��Ҽ��ְ�

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
		LogExceptionInfo(ctx);//����ã��
		ReturnContext(ctx);//������Ǯ���� �����͸����� �پ��� �ٽ� �����ش�
		return false;//�ɷȴٴ°Ŵ� ����ȉ�ٴ°Ŵϰ� false
	}

	ReturnContext(ctx);
	return true;
	//���ؽ���û�ؼ� ������ ���ؽ����� ����� ctx�� �غ���·ιٲٰ� ������Ʈ �����ϰ�
}

void Scripting::DiscardModule(const string & moduleName)
{
	scriptEngine->DiscardModule(moduleName.c_str());
}
void Scripting::Clear()
{
	for (auto ctx : ctxs) //�����͸� �Ѱܿö� Ȥ�ó� �����Ͱ� �ȹ޾������ &�ٿ��ش�.
		//���纻������������ ����������������
		ctx->Release();

	ctxs.clear();
	ctxs.shrink_to_fit();
}
void Scripting::LogExceptionInfo(asIScriptContext * ctx)
{
	string execoptionDescription = ctx->GetExceptionString();//���翡���� ��𼭳����� ���ڷ� �޾ƿ�
	const asIScriptFunction* function = ctx->GetExceptionFunction();

	string functionDeclaration = function->GetDeclaration();
	string moduleName = function->GetModuleName();
	string scriptPath = function->GetScriptSectionName();
	string scriptFile = FileSystem::GetFrileNameFromPath(scriptPath);
	string excoptionLine = to_string(ctx->GetExceptionLineNumber());

}

void Scripting::Message_CallBack(const asSMessageInfo & msg)
{
	string fileName = FileSystem::GetIntactFileNameFromPath(msg.section);//section->��ġ���
	string message = msg.message;
	
	string finalMessage;
	if (fileName != "")
		finalMessage = fileName + "" + message;
	else
		finalMessage = message;
}
