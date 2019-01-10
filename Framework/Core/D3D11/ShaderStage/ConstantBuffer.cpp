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
	D3D11_MAPPED_SUBRESOURCE mappedResource; //�۾��� �����ҵ��� fense�� ó�ش�. ����
	HRESULT hr = graphics->GetDeviceContext()->Map(
		cbuffer,
		0,
		D3D11_MAP_WRITE_DISCARD, //discard�� ������ �پ�����������
		0,
		&mappedResource
	);
	assert(SUCCEEDED(hr));
	return mappedResource.pData; //pData�� ���ŵ� �ڷ���� ����ȴ�. �� ������ ���ŵȴ�. �ʱⰪ�� ����.
	
}

void ConstantBuffer::Unmap()
{
	graphics->GetDeviceContext()->Unmap(cbuffer, 0); //��ٴ�.
}

void ConstantBuffer::BindPipeline()
{
	auto dc = graphics->GetDeviceContext();

	switch (shaderType)
	{
	case ShaderType::VS:  dc->VSSetConstantBuffers(slot,1,&cbuffer);break;
	case ShaderType::PS:  dc->PSSetConstantBuffers(slot,1,&cbuffer);break;
	case ShaderType::GS:  dc->GSSetConstantBuffers(slot,1,&cbuffer);break;//���� �ϳ��� �������� ����������ִ�.
	case ShaderType::CS:  dc->CSSetConstantBuffers(slot,1,&cbuffer);break; //������ �׷��Ȱ���
	}
}

