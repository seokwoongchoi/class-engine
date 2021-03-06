#include "stdafx.h"
#include "RenderTexture.h"

RenderTexture::RenderTexture(Context * context)
	:context(context)
	,rtvTexture(nullptr)
	,rtv(nullptr)
	,srv(nullptr)
{
	graphics = context->GetSubsystem<Graphics>();

	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.MaxDepth = 1.0f;
}

RenderTexture::~RenderTexture()
{
	SAFE_RELEASE(srv);
	SAFE_RELEASE(rtv);
	SAFE_RELEASE(rtvTexture);
}

void RenderTexture::Create(const uint & width, const uint & height, const DXGI_FORMAT & textureFormat)
{
	//Create Viewport
	{
		viewport.Width =static_cast<float>(width);
		viewport.Height = static_cast<float>(height);
	}
	
	//Create Render Target Texture
	{
		D3D11_TEXTURE2D_DESC textureDesc;
		ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = textureFormat;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			//텍스쳐 한장으로 렌더타겟뷰랑 쉐이더 리소스뷰를 만든다.
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		HRESULT hr = graphics->GetDevice()->CreateTexture2D(
			&textureDesc,
			nullptr,
			&rtvTexture
		);//비어있는 텍스쳐 한장 만들었다 이제
		assert(SUCCEEDED(hr));
	}
	
	//Create Render Target View
	{
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		ZeroMemory(&rtvDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		rtvDesc.Format = textureFormat;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;//2D로 만들어졌다는 것을 알려준다.
		rtvDesc.Texture2D.MipSlice = 0;

		HRESULT hr = graphics->GetDevice()->CreateRenderTargetView
		(
			rtvTexture,
			&rtvDesc,
			&rtv
		);
		assert(SUCCEEDED(hr));
	}

	//Create Shader Resource View
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

		srvDesc.Format = textureFormat;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D; //멀로 만들어졌는지 알수있다.이거는 2D로 만들어짐
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;

		HRESULT hr = graphics->GetDevice()->CreateShaderResourceView
		(
			rtvTexture//텍스쳐원본
			, &srvDesc
			, &srv
		);
		assert(SUCCEEDED(hr));

	}
}

void RenderTexture::Clear(const D3DXCOLOR & color)
{
	graphics->GetDeviceContext()->ClearRenderTargetView(rtv, color); //현재 렌더타겟뷰를 특정색깔로 싹지운다.
}

void RenderTexture::Clear(const float & r, const float & g, const float & b, const float & a)
{
	Clear(D3DXCOLOR(r, g, b, a));
}

void RenderTexture::SetRenderTarget()
{
	graphics->GetDeviceContext()->RSSetViewports(1, &viewport);
	graphics->GetDeviceContext()->OMSetRenderTargets(1, &rtv,nullptr);//OM은 8장 까지 만들수있고 1번은 구중 1번을사용한다.
	//rtv자원을 넣는다. 3번째인자는 depth
	
}

void RenderTexture::Save(const string & filePath)
{
	HRESULT hr = D3DX11SaveTextureToFileA(
		//텍스처를 파일로저장한다.
		graphics->GetDeviceContext(),
		rtvTexture,
		D3DX11_IFF_PNG,
		filePath.c_str()
	);
	assert(SUCCEEDED(hr));
		
}
