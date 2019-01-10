#pragma once
#include "ISubsystem.h"

class SceneManager: public ISubsystem
{
public:
	SceneManager(class Context* context);
	virtual ~SceneManager();


	const map<string, class Scene*>& GetScenes()const { return scenes; }

	class Scene* GetCurrentScene() const { return currentScene; }
	void SetCurrentScene(const string& sceneName); //<-map�� key���� �־��ش�.

	void RegistScene(const string& sceneName, class Scene* scene);

	const bool Initialize() override { return true; }
	
	void Update();

private:
	class Scene* currentScene; //���� ���� ���ϴ¾����� �����Ҽ��ְ����ش�.
	map<string, class Scene*> scenes;// �� ��Ȳ���´� �����̾ƿ;��ϴϱ� �ʾ���
	
};