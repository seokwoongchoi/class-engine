#pragma once
class ScriptInterface
	//스크립트는 기본언어밖에없어서 우리가 기존에 만들어 놓은 클래스들을 셋팅해주는 클래스
	
{
public:
	void Register(class Context* context, class asIScriptEngine* scriptEngine);
private:
	void RegisterEnumerations();
	void RegisterTypes();
	void RegisterSettings();
	void RegisterTimer();
	void RegisterInput();
	void RegisterGameObject();
	void RegisterTransform();
	void RegisterRenderable();
	void RegisterMaterial();
	void RegisterCamera();
	void RegisterMath();
	void RegisterVector2();
	void RegisterVector3();
private:
	class Context* context;
	class asIScriptEngine* scriptEngine;

};

