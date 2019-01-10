#include "stdafx.h"
#include "VertexShader.h"

VertexShader::VertexShader(Context* context)
	:BaseShader(context)
	,vertexShader(nullptr)
	,vsBlob(nullptr)
{
	//graphics = context->GetSubsystem<Graphics>();
}

VertexShader::~VertexShader()
{
	Clear();
	
}

void VertexShader::CreateVertexShader(const string & filePath, const string & functionName)
{
	this->ShaderfilePath = filePath;
	this->functionName = functionName;

	ID3D10Blob* error = nullptr;
	
	HRESULT hr = D3DX11CompileFromFileA(
		ShaderfilePath.c_str(), nullptr,nullptr, functionName.c_str(), "vs_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS //FLAG이름 구식문법을 엄밀히 체크해서 금지시킴
		, 0, nullptr, &vsBlob,&error, nullptr); //
	
	assert(CheckShaderError(hr, error));
	
	hr = graphics->GetDevice()->CreateVertexShader
	(
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		nullptr,
		&vertexShader
	);
	assert(SUCCEEDED(hr));
	SAFE_RELEASE(error);
}

void VertexShader::Clear()
{
	SAFE_RELEASE(vertexShader);
	SAFE_RELEASE(vsBlob);
}



void VertexShader::BindPipeline() //정점버퍼뷰에는 rtv와달리 서술자가 필요하지 않다.
{
	//graphics->GetDeviceContext()->IASetInputLayout(inputLayout);
	graphics->GetDeviceContext()->VSSetShader(vertexShader, nullptr, 0);
}

