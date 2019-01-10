#pragma once
#include "ISubsystem.h"

enum EngineFlags : unsigned long
{
	EngineFlags_Update = 1UL << 0, //UL->����ε� ��Ʈ 0X00000001
	EngineFlags_Render = 1UL << 1, //0X00000010
	EngineFlags_Game   = 1UL << 2, //0X00000100 ������������ ���޾� �ɼ��ְ�
};
class Engine:public ISubsystem
{

public:
	static const unsigned long& GetEngineFlags() { return engineFlags; }
	static void SetEngineFlags(const unsigned long& flags) { engineFlags = flags; }
	static void OnEngineFlags(const EngineFlags& flags) { engineFlags |= flags; }
	static void OffEngineFlags(const EngineFlags& flags) { engineFlags &= ~flags; } //��Ʈ���꿡���� ~�� not�̴�
	static void ToggleEngineFlags(const EngineFlags& flags) { engineFlags = !IsOnEngineFlags(flags) ? engineFlags| flags : engineFlags & ~flags; } //switch key
	static const bool IsOnEngineFlags(const EngineFlags& flags) { return (engineFlags& flags)>0UL; } //0UL���� ũ�� true
//0000000100
//0000010000
//0000000000
public:
	Engine(class Context* context);
	virtual ~Engine();

	const bool Initialize()override;
	void Update();

private:
	static unsigned long engineFlags;

	class Time* timer;
	class Input* input;
	class SceneManager* sceneManager;

	class Renderer* renderer;

};

