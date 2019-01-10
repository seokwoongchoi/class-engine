#pragma once
#include "ISubsystem.h"
enum class RenderableType :uint
{
	OpaqueObject, //불투명객체
	TransparentObject, //투명객체
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
		//렌더텍스쳐->텍스쳐에 렌더하는놈이고 그 텍스쳐를 반환해줄놈이다.
	}
	class Camera* GetMainCamera()const { return mainCamera; }
	void SetRenderables(class Scene* scene);//특정 씬을 받아온다.

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
	//vector가 빠른이유가 인덱스로 바로접근가능하다. unordered map은 해쉬를 사용 해쉬도 인덱스로 접근한다.
	//map과 unordered_map 사용처알아보기
};

