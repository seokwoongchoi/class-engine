#include "stdafx.h"
#include "SceneManager.h"
#include "../../Scene/Scene.h"
SceneManager::SceneManager(Context * context)
	:ISubsystem(context)
	,currentScene(nullptr) //포인터는 무조건 널로잡고시작한다.
{
}

SceneManager::~SceneManager()
{
	//맵지우는 첫번째 방법
	/*map<string, Scene*>::iterator iter = sceneTable.begin();
	for (auto iter = sceneTable.begin(); iter != sceneTable.end(); iter++)
		SAFE_DELETE(iter->second);*/
	for (auto scene : scenes)
		SAFE_DELETE(scene.second);
}





void SceneManager::SetCurrentScene(const string & sceneName)
{
	assert(scenes.count(sceneName) > 0);//0보다크면 넘어가고 작으면 어썰트걸린다.
	currentScene = scenes[sceneName];
}

void SceneManager::RegistScene(const string & sceneName, Scene * scene)
{
	assert(scenes.count(sceneName) <1);
	scene->SetName(sceneName);
	scenes[sceneName] = scene;//씬을 맵에 넣어준다. 1번방법
	//sceneTable.insert(make_pair(sceneName, scene));//make_pair를 이용해서 맵에넣어준다 2번방법
}


void SceneManager::Update()
{
	if (currentScene)
	{
		currentScene->Update();
	}
}

