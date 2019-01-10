#pragma once
#include "ISubsystem.h"
enum class RenderableType :uint
{
	OpaqueObject, //������ü
	TransparentObject, //����ü
	Camera
};
class Renderer:public ISubsystem
{
public:
	Renderer(class Context* context);
	virtual ~Renderer();


	ID3D11ShaderResourceView* GetFrameResource()const
	{
		return renderTexture->GetShaderResource();
		//�����ؽ���->�ؽ��Ŀ� �����ϴ³��̰� �� �ؽ��ĸ� ��ȯ���ٳ��̴�.
	}
	class Camera* GetMainCamera()const { return mainCamera; }
	void SetRenderables(class Scene* scene);//Ư�� ���� �޾ƿ´�.

	const bool Initialize()	override;
	
	void Render();
	void Clear();

private:
	void PassPreRender();


private:
	class Graphics* graphics;
	class Camera* mainCamera;
	class Camera* editorCamera;
	class Camera* sceneCamera;

	class RenderTexture* renderTexture;
	class ConstantBuffer* cameraBuffer;
	class ConstantBuffer* transformBuffer;
	class Pipeline* pipeline;

	unordered_map<RenderableType, vector<class GameObject*>>renderables;
	//vector�� ���������� �ε����� �ٷ����ٰ����ϴ�. unordered map�� �ؽ��� ��� �ؽ��� �ε����� �����Ѵ�.
	//map�� unordered_map ���ó�˾ƺ���
};

