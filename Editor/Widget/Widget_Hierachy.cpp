#include "stdafx.h"
#include "Widget_Hierachy.h"
#include "./Editor/Utillity/EditorHelper.h"
#include "Framework/Scene/Scene.h"
#include "Framework/Scene/GameObject.h"
#include "Framework/Scene/Component/Transform.h"
#include "Framework/Scene/Component/Renderable.h"
#include "Framework/Scene/Component/Collider.h"
#include "../Utillity/DragDrop.h"



Widget_Hierachy::Widget_Hierachy(Context * context)
	:IWidget(context)
{
	title = "Hierachy";
	sceneManager = context->GetSubsystem<SceneManager>();
	//auto colliderMnager = context->GetSubsystem<ColliderManager>();
}

Widget_Hierachy::~Widget_Hierachy()
{
}



void Widget_Hierachy::Render()
{
	ShowHierarchy();


	if (ImGui::IsWindowHovered())
	{
		if (ImGui::GetIO().MouseDown[1])
			ImGui::OpenPopup("Hierachy MenuPopup");
	}
	ShowPopup();
}

void Widget_Hierachy::ShowHierarchy()
{
	auto scenes = sceneManager->GetScenes();
	for (auto scene : scenes)
		AddScene(scene.second);
}

void Widget_Hierachy::AddScene(Scene * scene)
{
	if (!scene) return;
	
	auto objects = scene->GetObjects();
	if (ImGui::CollapsingHeader(scene->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		for (auto object : objects)
		{
			AddObject(object);

			if (ImGui::IsItemClicked())
			{
				EditorHelper::CurrentObject = object;
			}
		}
	}
		
}

void Widget_Hierachy::AddObject(GameObject * object)
{
	if (!object) return;

	if (ImGui::TreeNodeEx(object->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))//treenode시작
	{


		ImGui::TreePop();//treenode 끝
	}
}

void Widget_Hierachy::ShowPopup()
{
	MenuPopup();
}

void Widget_Hierachy::MenuPopup()
{
	if (ImGui::BeginPopup("Hierachy MenuPopup"))
	{
		if(ImGui::MenuItem("Copy")){}
		if (ImGui::MenuItem("Delete")) {}

		ImGui::Separator();
		if (ImGui::MenuItem("Empty Object"))CreateEmpty();
		
		if (ImGui::BeginMenu("Create"))
		{
			if (ImGui::MenuItem("Quad")) CreateQuad();
			if (ImGui::MenuItem("Circle")) CreateCircle();
			ImGui::EndMenu();
		}

		ImGui::EndPopup();
	}
}

GameObject * Widget_Hierachy::CreateEmpty()//transform만 가지고있는 오브젝트만 만들어서 넣어준다.
{
	auto scene = sceneManager->GetCurrentScene();

	if (scene)
	{
		auto object = scene->CreateObject();
		return object;
	}

	return nullptr;
}

void Widget_Hierachy::CreateQuad()
{
	auto object = CreateEmpty();

	if (object)
	{
		auto renderable = object->AddComponent<Renderable>();
		renderable->SetModelType(ModelType::Quad);
		object->SetName("Quad");
	
		object->GetComponent<Transform>()->SetScale(Vector3(50.f,50.f,1.f));
		/*Collider* collider = object->GetComponent<Collider>();
	    collider->SetCenter(object->GetTransform()->GetPosition());
	    collider->SetSize(object->GetTransform()->GetScale());*/
		
	}
}

void Widget_Hierachy::CreateScreenQuad()
{
}

void Widget_Hierachy::CreateCircle()
{
	auto object = CreateEmpty();

	if (object)
	{
		auto renderable = object->AddComponent<Renderable>();
		renderable->SetModelType(ModelType::Circle);
		object->SetName("Circle");

		object->GetComponent<Transform>()->SetScale(Vector3(30.f, 30.f, 1.f));
	}
}
