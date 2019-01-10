#pragma once
#include "IComponent.h"
class Camera:public IComponent //ī�޶�� ����ý��ۿ� �ȳִ´�. ī�޶� �������ʿ����������ֱ⶧����
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

	//	//D3DXMatrixOrthoLH();//zn->znear zf->zfar ������ ������ ����� ��´� 
	//	//D3DXMatrixOrthoOffCenterLH();//left,right,bottom,top �� ������� ������´�. ���콺��ǥ�����⽱���Ϸ�����.


	//	void SetOrthographicOffCenterLH(const float& l, const float& r, const float& b, const float& t,
	//		const float& zn, const float& zf);

		const Vector3 ScreenToWorldPoint(const Vector2& screenPoint);//���콺 ��ǥ�踦 �޾Ƽ� ����ιٲ۴�.
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