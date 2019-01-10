#pragma once
#include "IComponent.h"
class Camera:public IComponent //카메라는 서브시스템에 안넣는다. 카메라가 여러개필요해질수도있기때문에
{
public:
	Camera(
		class Context* context,
	    class GameObject* gameobject,
	    class Transform* transform
	);
	Camera(	class Context* context);
	virtual ~Camera();

	void OnInitialize() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnStop() override;
	void OnDestroy() override;

	void EditorCameraUpdate();

	const Matrix& GetViewMatrix()const { return view; }
	const Matrix& GetProjMatrix()const { return proj; }
	const float& GetNearPlane()const { return nearPlane; }
	const float& GetFarPlane()const { return farPlane; }

	void SetNearPlane(const float& nearPlane) { this->nearPlane = nearPlane; }
	void SetFarPlane(const float& farPlane) { this->farPlane = farPlane; }

	//void SetOrthographicLH(const float& w, const float& h, const float& zn, const float& zf);

	//	//D3DXMatrixOrthoLH();//zn->znear zf->zfar 무조건 정점을 가운데에 찍는다 
	//	//D3DXMatrixOrthoOffCenterLH();//left,right,bottom,top 내 마음대로 정점찍는다. 마우스좌표를따기쉽게하려고쓴다.


	//	void SetOrthographicOffCenterLH(const float& l, const float& r, const float& b, const float& t,
	//		const float& zn, const float& zf);

		const Vector3 ScreenToWorldPoint(const Vector2& screenPoint);//마우스 좌표계를 받아서 월드로바꾼다.
	//	void Update();
	const void SetPosition(const Vector3& position) { this->position = position; }

	const bool& IsEditorCamera()const { return bEditorCamera; }
private:
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

private:
	
	class Time* timer;
	class Input* input;
	
	Vector3 position;
	Matrix view;
	Matrix proj;
	float nearPlane;
	float farPlane;
	float zoom;

	bool bEditorCamera;

};