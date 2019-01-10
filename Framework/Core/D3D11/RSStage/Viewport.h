#pragma once
class Viewport
{//렌더링 파이프라인에서 vs단계에서 월드변환하고 rs단계에서 이것들을 랜더링할것인가 말것인가 결정한다.
public:
	Viewport(class Context* context);
	virtual ~Viewport();
	
	void SetViewport(const float& width, const float& height);
	void SetViewport(
	const float &x,
		const float &y, 
		const float &width,
		const float &height, 
		const float &minDepth, 
		const float &maxDepth);

	void BindPipeline();

private:
	class Graphics* graphics;
	D3D11_VIEWPORT viewport;
};

