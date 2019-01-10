#pragma once
#include "IWidget.h"
class Widget_Hierachy:public IWidget
{
public:
	Widget_Hierachy(class Context* context);
	virtual ~Widget_Hierachy();

	
	void Render() override;

private:
	void ShowHierarchy();
	void AddScene(class Scene* scene);
	void AddObject(class GameObject* object);
private:
	void ShowPopup();
	void MenuPopup();

private:
	class GameObject* CreateEmpty();
	void CreateQuad();
	void CreateScreenQuad();
	void CreateCircle();

private:
	class SceneManager* sceneManager;
};

