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
	subData.pSysMem = indices.data();//버퍼를 초기화할 자료를 담은 시스템메모리 배열을 가리키는 포인터 정점 n개를 담는 버퍼를 초기화하는 경우 
	//초기화가 제대로 일어나려면 그배열의 원소가 적어도n개여야한다.

	HRESULT hr = graphics->GetDevice()->CreateBuffer(
		&bufferDesc, //생성할 버퍼를 서술하는 구조체
		&subData, //버퍼를 초기화하는데 사용할 자료
		&ibuffer //생성된 버퍼가 여기에 설정된다.
	);
	assert(SUCCEEDED(hr));
}

void IndexBuffer::Clear()
{
	SAFE_RELEASE(ibuffer);
}

void* IndexBuffer::Map()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource; //작업을 수행할동안 fense를 처준다.
	HRESULT hr = graphics->GetDeviceContext()->Map(
		ibuffer,
		0,
		D3D11_MAP_WRITE_DISCARD, //discard는 정보를 다쓰고나서버린다
		0,
		&mappedResource
	);
	assert(SUCCEEDED(hr));
	return mappedResource.pData; //pData에 갱신될 자료들이 저장된다.
}

void IndexBuffer::Unmap()
{
	graphics->GetDeviceContext()->Unmap(ibuffer, 0);
}

void IndexBuffer::BindPipeline()
{
	graphics->GetDeviceContext()->IASetIndexBuffer(ibuffer, DXGI_FORMAT_R32_UINT, 0);
}
