#include"stdafx.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(Context* context)
	:cbuffer(nullptr)
{
		graphics = context->GetSubsystem<Graphics>();
}

ConstantBuffer::~ConstantBuffer()
{
	Clear();
}

void ConstantBuffer::Clear()
{
	SAFE_RELEASE(cbuffer);
}

void * ConstantBuffer::Map() 
{
	D3D11_MAPPED_SUBRESOURCE mappedResource; //작업을 수행할동안 fense를 처준다. 열고
	HRESULT hr = graphics->GetDeviceContext()->Map(
		cbuffer,
		0,
		D3D11_MAP_WRITE_DISCARD, //discard는 정보를 다쓰고나서버린다
		0,
		&mappedResource
	);
	assert(SUCCEEDED(hr));
	return mappedResource.pData; //pData에 갱신될 자료들이 저장된다. 매 프레임 갱신된다. 초기값이 없다.
	
}

void ConstantBuffer::Unmap()
{
	graphics->GetDeviceContext()->Unmap(cbuffer, 0); //잠근다.
}

void ConstantBuffer::BindPipeline()
{
	auto dc = graphics->GetDeviceContext();

	switch (shaderType)
	{
	case ShaderType::VS:  dc->VSSetConstantBuffers(slot,1,&cbuffer);break;
	case ShaderType::PS:  dc->PSSetConstantBuffers(slot,1,&cbuffer);break;
	case ShaderType::GS:  dc->GSSetConstantBuffers(slot,1,&cbuffer);break;//정점 하나로 여러개의 정점만들수있다.
	case ShaderType::CS:  dc->CSSetConstantBuffers(slot,1,&cbuffer);break; //쓰레드 그래픽계산용
	}
}

