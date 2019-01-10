#pragma once
#include "IWidget.h"
class Widget_Scene :public IWidget
{
public:
	Widget_Scene(class Context* context);
	virtual ~Widget_Scene();

	//void Initialize(class Context* context) override;
	void Render()override;
private:
	void ShowFrame();
	void ShowGizmo();

private:
	void Picking();
	void DragDrop();
private:

	class SceneManager* sceneManager;
	class Renderer* renderer;
	class ColliderManager* collidermanager;
	class Camera* camera;
	//class Collider* collider;
	Vector2 framePos;//신의 시작점
	Vector2 frameSize;
	Vector2 mousePos;
};

