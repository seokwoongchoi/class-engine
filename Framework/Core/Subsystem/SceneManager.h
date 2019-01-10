#pragma once
#include "ISubsystem.h"

class SceneManager: public ISubsystem
{
public:
	SceneManager(class Context* context);
	virtual ~SceneManager();


	const map<string, class Scene*>& GetScenes()const { return scenes; }

	class Scene* GetCurrentScene() const { return currentScene; }
	void SetCurrentScene(const string& sceneName); //<-map의 key값을 넣어준다.

	void RegistScene(const string& sceneName, class Scene* scene);

	const bool Initialize() override { return true; }
	
	void Update();

private:
	class Scene* currentScene; //현재 씬이 머하는씬인지 구별할수있게해준다.
	map<string, class Scene*> scenes;// 그 상황에맞는 씬을뽑아와야하니까 맵쓴다
	
};