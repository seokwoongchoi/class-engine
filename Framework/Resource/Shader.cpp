#include "stdafx.h"
#include "Shader.h"

Shader::Shader(Context * context)
	:IResource(context)
     ,pixelShader(nullptr)
	 , vertexShader(nullptr)
	,inputLayout(nullptr)

{
	
}

Shader::~Shader()
{
	SAFE_DELETE(pixelShader);
	SAFE_DELETE(vertexShader);
}

void Shader::CreateVertexShader(const string & filePath, const string & functionName)
{
	if (vertexShader)
		vertexShader->Clear();
	else
	    vertexShader = new VertexShader(context);

	vertexShader->CreateVertexShader(filePath, functionName);
	
}

void Shader::CreatePixelShader(const string & filePath, const string & functionName)
{
	if (pixelShader)
		pixelShader->Clear();
	else
		pixelShader = new PixelShader(context);

	pixelShader->CreatePixelShader(filePath, functionName);
	
}

void Shader::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC * descs, const uint & count)
{
	if (inputLayout)
		inputLayout->Clear();
	else
		inputLayout = new InputLayout(context);

	if (descs == nullptr || count == 0)
		inputLayout->Create(vertexShader->GetBlob());
	else
		inputLayout->Create(descs, count, vertexShader->GetBlob());
}

void Shader::LoadFromFile(const string & loadFilePath)
{
	if (loadFilePath.rfind(".hlsl") != string::npos)
	{
		CreateVertexShader(loadFilePath);
		CreatePixelShader(loadFilePath);
		CreateInputLayout();
	}
	else
	{
		//TODO:
	}
}
