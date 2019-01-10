#pragma once
class RenderTexture
{
public:
	RenderTexture(class Context* context);
	virtual ~RenderTexture();

	//텍스쳐에 렌더링한다.-> 텍스쳐를 받아와야한다.->효과를 주기위해서 쉐이더로 보내고 쉐이더의 srv를 받아와야한다
	ID3D11ShaderResourceView* GetShaderResource()const { return srv; }
	


	void Create(
	const uint& width,
		const uint& height,
		const DXGI_FORMAT& textureFormat =DXGI_FORMAT_R8G8B8A8_UNORM);//0~1로만 표현한다.
	void Clear(const D3DXCOLOR& color=D3DXCOLOR(0xff555566)); //여기다 1,1,1,1넣으면 흰색으로 덮는다.
	void Clear(const float& r, const float& g, const float& b, const float& a=1.0f);
	void SetRenderTarget();
	void Save(const string& filePath);
private:
	class Context* context;
	class Graphics* graphics;

	ID3D11Texture2D* rtvTexture;
	ID3D11RenderTargetView* rtv;
	ID3D11ShaderResourceView* srv;
	D3D11_VIEWPORT viewport;
};

