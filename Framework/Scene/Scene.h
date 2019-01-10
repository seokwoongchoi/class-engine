#pragma once

class Scene //스테이지에 해당하는 장면
{
public:
	Scene(class Context* context);//context를 불러옴으로써 서브시스템폴더안의 기능들을 불러와서사용가능하다
	virtual ~Scene();

	const string& GetName()const { return name; }
	class GameObject* GetMainCamera()const { return mainCamera; }
	const vector<class GameObject*>GetObjects()const { return objects; }

	void SetName(const string& name) { this->name = name; }

	class GameObject* CreateObject();
	void AddObject(class GameObject* object);
	void RemoveObject(class GameObject* object);
	const bool IsExistObject(class GameObject* object);

	void Update();
	

private:
	class Context* context;
	class Renderer* renderer;
	class GameObject* mainCamera;
	vector<class GameObject*> objects;
	string name;
	bool bEditorMode;
	bool bAdded;
};