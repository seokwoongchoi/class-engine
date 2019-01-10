#include "stdafx.h"
#include "SceneManager.h"
#include "../../Scene/Scene.h"
SceneManager::SceneManager(Context * context)
	:ISubsystem(context)
	,currentScene(nullptr) //�����ʹ� ������ �η��������Ѵ�.
{
}

SceneManager::~SceneManager()
{
	//������� ù��° ���
	/*map<string, Scene*>::iterator iter = sceneTable.begin();
	for (auto iter = sceneTable.begin(); iter != sceneTable.end(); iter++)
		SAFE_DELETE(iter->second);*/
	for (auto scene : scenes)
		SAFE_DELETE(scene.second);
}





void SceneManager::SetCurrentScene(const string & sceneName)
{
	assert(scenes.count(sceneName) > 0);//0����ũ�� �Ѿ�� ������ ���Ʈ�ɸ���.
	currentScene = scenes[sceneName];
}

void SceneManager::RegistScene(const string & sceneName, Scene * scene)
{
	assert(scenes.count(sceneName) <1);
	scene->SetName(sceneName);
	scenes[sceneName] = scene;//���� �ʿ� �־��ش�. 1�����
	//sceneTable.insert(make_pair(sceneName, scene));//make_pair�� �̿��ؼ� �ʿ��־��ش� 2�����
}


void SceneManager::Update()
{
	if (currentScene)
	{
		currentScene->Update();
	}
}

