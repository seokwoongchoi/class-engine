#include "stdafx.h"
#include "Camera.h"
#include "Transform.h"


Camera::Camera(Context * context, GameObject * gameobject, Transform * transform)
	:IComponent(context,gameobject,transform)
	,timer(nullptr)
	,input(nullptr)
	,nearPlane(0.0f)
	,farPlane(1.0f)
	,zoom(1.0f)
	,bEditorCamera(false)
	
{
	
	view.SetIdentity();
	proj.SetIdentity();
}

Camera::Camera(Context * context)
	:IComponent(context,nullptr,nullptr)
	, nearPlane(0.0f)
	, farPlane(1.0f)
	, zoom(1.0f)
    , bEditorCamera(true)
{
	timer = context->GetSubsystem<Time>();
	input = context->GetSubsystem<Input>();
	transform = new Transform(context, nullptr, nullptr);
	view.SetIdentity();
	proj.SetIdentity();
}

Camera::~Camera()
{
	if (bEditorCamera)
		SAFE_DELETE(transform);
}

void Camera::OnInitialize()
{
}

void Camera::OnStart()
{
}

void Camera::OnUpdate()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void Camera::OnStop()
{
}

void Camera::OnDestroy()
{
}

void Camera::EditorCameraUpdate()
{
	if (!bEditorCamera) return;
	
	Vector3 position = transform->GetPosition();
	Vector3 right = transform->GetRight();
	Vector3 up= transform->GetUp();

	if (input->KeyPress(VK_Shift))
	{
		if (input->KeyPress(VK_W))
			position += up * 200.0f*timer->GetDeltaTimeSec();
		else if (input->KeyPress(VK_S))
			position -= up * 200.0f*timer->GetDeltaTimeSec();
		
		if (input->KeyPress(VK_A))
			position -= right * 200.0f*timer->GetDeltaTimeSec();
		else if (input->KeyPress(VK_D))
			position += right * 200.0f*timer->GetDeltaTimeSec();

	}
	transform->SetPosition(position);

	float delta = input->GetMouseMoveValue().z;//마우스가 얼마나 움직였나
	if (Math::Abs(delta) >= WHEEL_DELTA)//마우스 휠한번 돌리는데 값이 120
	{
		float deltaZoom = 1.0f - Math::Abs(delta)/WHEEL_DELTA/10.0f;
		if (delta < 0)
			zoom *= deltaZoom;
		else
			zoom /= deltaZoom;
		Math::Clamp(zoom,0.1f,100.0f);
	}
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}



//void Camera::SetOrthographicLH(const float & w, const float & h, const float & zn, const float & zf)
//{
//	D3DXMatrixOrthoLH(&proj, w, h, zn, zf);
//}
//
//void Camera::SetOrthographicOffCenterLH(const float & l, const float & r, const float & b, const float & t, const float & zn, const float & zf)
//{//왼쪽상단(내가 그렇게 설정할곳) 이 중앙
//	D3DXMatrixOrthoOffCenterLH(&proj, l, r, b, t, zn, zf);
//}

const Vector3 Camera::ScreenToWorldPoint(const Vector2 & screenPoint)
{
	Vector2 viewport = Settings::Get()->GetRelative();

	//Convert Screen pixel to view space
	float pointX = +2.0f * screenPoint.x / viewport.x - 1.0f;
	float pointY = -2.0f * screenPoint.y / viewport.y + 1.0f;

	//Unprojection point
	Matrix unprojection = (view * proj).Inverse();

	Vector3 worldPoint = Vector3::TransformCoord
	(
		Vector3(pointX, pointY,1.0f),
		unprojection
	);

	return worldPoint;
}

//void Camera::Update()
//{
//	if (input->KeyPress(VK_SHIFT))
//	{
//		if (input->KeyPress(VK_W))
//			position += up * 200.f*timer->GetDeltaTimeSec();
//		else if (input->KeyPress(VK_S))
//			position += -up * 200.0f*timer->GetDeltaTimeSec();
//
//		if (input->KeyPress(VK_A))
//			position += -right * 200.0f*timer->GetDeltaTimeSec();
//		else if (input->KeyPress(VK_D))
//			position += right * 200.0f * timer->GetDeltaTimeSec();
//
//		D3DXMatrixLookAtLH(&view, &position, &(position + forward), &up);
//	}
//}

void Camera::UpdateViewMatrix()
{
	Vector3 position = transform->GetPosition();
	Vector3 forward = transform->GetForward();
	Vector3 up = transform->GetUp();

	view = Matrix::LookAtLH(position, (position + forward), up);
}

void Camera::UpdateProjectionMatrix()
{
	auto viewport = Settings::Get()->GetViewport();
	
	/*if(input->KeyPress(VK_O))
	{
		viewport.Width += 1280 * timer->GetDeltaTimeSec();
		viewport.Height += 720 * timer->GetDeltaTimeSec();
	}
 else if (input->KeyPress(VK_P))
 {
 viewport.Width -= 1280 * timer->GetDeltaTimeSec();
 viewport.Height -= 720 * timer->GetDeltaTimeSec();
 }*/
	
	proj = Matrix::OrthoLH(
		viewport.Width/zoom,
		viewport.Height/zoom,
		nearPlane,
		farPlane
	);
}
