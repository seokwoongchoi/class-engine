#include"stdafx.h"
#include "Widget_Scene.h"
#include "../Utillity/EditorHelper.h"
#include "../Utillity/Gizmo.h"
#include "../Utillity/DragDrop.h"
#include "../../Framework/Scene/Scene.h"
#include "../../Framework/Scene/GameObject.h"
#include "../../Framework/Scene/Component/Camera.h"
#include "../../Framework/Scene/Component/Transform.h"
#include "../../Framework/Scene/Component/Renderable.h"
#include "../../Framework/Scene/Component/Collider.h"



Widget_Scene::Widget_Scene(Context * context)
	:IWidget(context)
{
	title = "Scene";
	windowFlags |= ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

	camera = nullptr;
	sceneManager = context->GetSubsystem<SceneManager>();
	renderer = context->GetSubsystem<Renderer>();
	collidermanager = context->GetSubsystem<ColliderManager>();
}

Widget_Scene::~Widget_Scene()
{
}



void Widget_Scene::Render()
{
	ShowFrame();
	ShowGizmo();
	Picking();
	DragDrop();
}

void Widget_Scene::ShowFrame()
{
	framePos = EditorHelper::ToDxVec2(ImGui::GetCursorPos() + ImGui::GetWindowPos());
	
	frameSize = EditorHelper::ToDxVec2(ImGui::GetWindowContentRegionMax() - ImGui::GetWindowContentRegionMin());
	frameSize.x -= static_cast<float>((static_cast<int>(frameSize.x) % 2 != 0 ) ? 1 : 0);
	frameSize.y -= static_cast<float>((static_cast<int>(frameSize.y) % 2 != 0 ) ? 1 : 0);


	//ID3D11ShaderResourceView* srv = nullptr;
	ImGui::Image
	(
		renderer ->GetFrameResource(),EditorHelper::ToImVec2(frameSize),ImVec2(0,0),ImVec2(1,1),ImVec4(1,1,1,1),ImColor(50,127,166,255)
	);
	if (Settings::Get()->GetRelative() != frameSize)
		Settings::Get()->SetRelative(frameSize);

	/*auto mainCamera = sceneManager->GetCurrentScene()->GetMainCamera();
	camera = mainCamera->GetComponent<Camera>();*/
	camera = renderer->GetMainCamera();
}

void Widget_Scene::ShowGizmo()
{
	if (!EditorHelper::CurrentObject || !camera)return;
	
	camera->OnUpdate();
	{
		Gizmo::TransformGizmo
		(
			camera,
			EditorHelper::CurrentObject->GetComponent<Transform>(),
			framePos,
			frameSize

		);
	}
}

void Widget_Scene::Picking()
{
	bool bCheck = false;
	bCheck |= !camera;//ī�޶� ���ٸ� ��ŷ�� �ǹ̰� ����.
	bCheck |= !ImGui::IsMouseClicked(0);
	//0�̸� ���� ���콺Ŭ���� �ȵǸ� ��ŷ�ʿ����.
	bCheck |= !ImGui::IsWindowHovered
	(
		ImGuiHoveredFlags_AllowWhenBlockedByPopup |
		ImGuiHoveredFlags_AllowWhenBlockedByActiveItem
	);

	if (bCheck) //�����ϳ��� Ʈ��� ��ŷ�̾ȵȴ�.
		return;
	/*Scene* currentScene = sceneManager->GetCurrentScene();
	vector<GameObject*> objects = currentScene->GetObjects();*/
	Vector2 relativeMousePos
		= EditorHelper::ToDxVec2(ImGui::GetMousePos()) - framePos;
	Vector3 worldMousePos
		= camera->ScreenToWorldPoint(relativeMousePos);
	/*Vector3 mousePos = Vector3(
		 ImGui::GetIO().MouseClickedPos[0].x - framePos.x,
		 ImGui::GetIO().MouseClickedPos[0].y - framePos.y,
		 0.0f
		 );
		
		 Vector3 worldMousePos = camera->ScreenToWorldPoint( Vector2(mousePos.x,mousePos.y));*/

	auto objects = sceneManager->GetCurrentScene()->GetObjects();
	for (auto object : objects)
	{
		if (!object->HasComponent<Renderable>())
		continue;//������ false���´�.->ȭ�鿡 �ȳ��´�.->��ŷ���ʿ����.

		//ture
		auto renderable = object->GetComponent<Renderable>();//�������̺� �����´�.
		auto boundBox = renderable->GetBoundBox();
		//boundbox������Ʈ �ȵ��������������ϱ� ������Ʈ���ش�.
		boundBox = boundBox.Transformed(object->GetComponent<Transform>()->GetWorldMatrix());

	
		
		auto result = boundBox.IsInside(worldMousePos);
		if (result == Intersection::Inside)
		{
			if(EditorHelper::CurrentObject != object)
			EditorHelper::CurrentObject = object;
			
			

		}

		//if(ImGui::IsItemClicked(0))
		//EditorHelper::CurrentObject->GetTransform()->SetPosition(worldMousePos);
		
		
	}
	
	
}

void Widget_Scene::DragDrop()
{
	
	string data = DragDrop::GetDragDropPayload(DragDropPayloadType::Texture);

	if (data.length() != 0)
	{
		if (EditorHelper::CurrentObject)
		{
			auto renderable = EditorHelper::CurrentObject->GetComponent<Renderable>();
			//
			auto material = renderable->GetMaterial();
			//
			material->SetDiffuseTexture(data);
		}
	}
}
