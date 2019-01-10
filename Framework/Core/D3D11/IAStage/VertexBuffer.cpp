#include "stdafx.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(class Context* context)
	:vbuffer(nullptr) //포인터는 항상 널로 초기화해주는 것이 좋다. 널로 초기화안하면 쓰레기값들어가고
	//컴파일과정에서 그냥 통과되서 메모리할당이 없는 상태에서 delete를 시도하게되기때문에 문제가된다.
	,stride(0)
	,offset(0)
{
	graphics = context->GetSubsystem<Graphics>();
}

VertexBuffer::~VertexBuffer()
{
	Clear();
}

void VertexBuffer::Clear()
{
	SAFE_RELEASE(vbuffer);
	stride = 0;
	offset = 0;
}

void* VertexBuffer::Map()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource; //작업을 수행할동안 fense를 처준다.
	HRESULT hr = graphics->GetDeviceContext()->Map(
		vbuffer,//읽기 쓰기 접근을 원하는 자원을 가리키는 포인터
		0,//그 자원에 담긴 부분자원의 색인
		D3D11_MAP_WRITE_DISCARD, // 하드웨어에게 현재 버퍼를 폐기하고 새 버퍼를
		/*할당해서 그 포인터를 돌려달라고 지시한다.이렇게 하면 새로 할당된 버퍼에 자
		료를 기록하는 동안 하드웨어가 폐기된 버퍼에 렌더링 작업을 계속 진행할 수 있
		으므로 하드웨어의 실행이 일시적으로 멈추는 일이 방지된디*/
		//D3D11_MAP_WRITE_NO_OVERWRITE:초기화안한부분에만 자료기록
		0,
		&mappedResource//이를통해서 버퍼에 자료를 기록하거나 읽는다.
	);
	assert(SUCCEEDED(hr));
	return mappedResource.pData; //pData에 갱신될 자료들이 저장된다.
}

void VertexBuffer::Unmap()

{
	graphics->GetDeviceContext()->Unmap(vbuffer, 0);
}

void VertexBuffer::BindPipeline()
{
	graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &vbuffer, &stride, &offset);//1.시작슬룻,즉 첫쨰 정점버퍼를 묶을 입력슬룻의 색인 총 16개다
	//2.입력슬롯들에 묶을 정점버퍼 개수,3.정점버퍼 뷰 배열의 첫 원소를 가리키는 포인터,4.보폭(stride)들의 배열의 첫원소를 가리키는 포인터 해당정점버퍼의 한원소의
	//바이트 단위크기이다.,5.오프셋들의 배열의 첫원소를 가리키는 포인터 입력조리립기단계가 정점자료를 읽기 시작할 정점버퍼안 위치까지의 거리
}
