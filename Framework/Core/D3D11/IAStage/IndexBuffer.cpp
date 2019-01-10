#include "stdafx.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(class Context* context)
	:ibuffer(nullptr)
{
	graphics = context->GetSubsystem<Graphics>();
}

IndexBuffer::~IndexBuffer()
{
	Clear();
}

void IndexBuffer::Create(const vector<uint>& indices, const D3D11_USAGE& usage)
{
	assert(!indices.empty());
	Clear();

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	if (usage == D3D11_USAGE_DYNAMIC)
	{
		bufferDesc.Usage = usage;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
		bufferDesc.Usage = usage;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(uint)*indices.size();
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = indices.data();//���۸� �ʱ�ȭ�� �ڷḦ ���� �ý��۸޸� �迭�� ����Ű�� ������ ���� n���� ��� ���۸� �ʱ�ȭ�ϴ� ��� 
	//�ʱ�ȭ�� ����� �Ͼ���� �׹迭�� ���Ұ� ���n�������Ѵ�.

	HRESULT hr = graphics->GetDevice()->CreateBuffer(
		&bufferDesc, //������ ���۸� �����ϴ� ����ü
		&subData, //���۸� �ʱ�ȭ�ϴµ� ����� �ڷ�
		&ibuffer //������ ���۰� ���⿡ �����ȴ�.
	);
	assert(SUCCEEDED(hr));
}

void IndexBuffer::Clear()
{
	SAFE_RELEASE(ibuffer);
}

void* IndexBuffer::Map()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource; //�۾��� �����ҵ��� fense�� ó�ش�.
	HRESULT hr = graphics->GetDeviceContext()->Map(
		ibuffer,
		0,
		D3D11_MAP_WRITE_DISCARD, //discard�� ������ �پ�����������
		0,
		&mappedResource
	);
	assert(SUCCEEDED(hr));
	return mappedResource.pData; //pData�� ���ŵ� �ڷ���� ����ȴ�.
}

void IndexBuffer::Unmap()
{
	graphics->GetDeviceContext()->Unmap(ibuffer, 0);
}

void IndexBuffer::BindPipeline()
{
	graphics->GetDeviceContext()->IASetIndexBuffer(ibuffer, DXGI_FORMAT_R32_UINT, 0);
}
