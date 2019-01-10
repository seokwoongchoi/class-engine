#include "stdafx.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(class Context* context)
	:vbuffer(nullptr) //�����ʹ� �׻� �η� �ʱ�ȭ���ִ� ���� ����. �η� �ʱ�ȭ���ϸ� �����Ⱚ����
	//�����ϰ������� �׳� ����Ǽ� �޸��Ҵ��� ���� ���¿��� delete�� �õ��ϰԵǱ⶧���� �������ȴ�.
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
	D3D11_MAPPED_SUBRESOURCE mappedResource; //�۾��� �����ҵ��� fense�� ó�ش�.
	HRESULT hr = graphics->GetDeviceContext()->Map(
		vbuffer,//�б� ���� ������ ���ϴ� �ڿ��� ����Ű�� ������
		0,//�� �ڿ��� ��� �κ��ڿ��� ����
		D3D11_MAP_WRITE_DISCARD, // �ϵ����� ���� ���۸� ����ϰ� �� ���۸�
		/*�Ҵ��ؼ� �� �����͸� �����޶�� �����Ѵ�.�̷��� �ϸ� ���� �Ҵ�� ���ۿ� ��
		�Ḧ ����ϴ� ���� �ϵ��� ���� ���ۿ� ������ �۾��� ��� ������ �� ��
		���Ƿ� �ϵ������ ������ �Ͻ������� ���ߴ� ���� �����ȵ�*/
		//D3D11_MAP_WRITE_NO_OVERWRITE:�ʱ�ȭ���Ѻκп��� �ڷ���
		0,
		&mappedResource//�̸����ؼ� ���ۿ� �ڷḦ ����ϰų� �д´�.
	);
	assert(SUCCEEDED(hr));
	return mappedResource.pData; //pData�� ���ŵ� �ڷ���� ����ȴ�.
}

void VertexBuffer::Unmap()

{
	graphics->GetDeviceContext()->Unmap(vbuffer, 0);
}

void VertexBuffer::BindPipeline()
{
	graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &vbuffer, &stride, &offset);//1.���۽���,�� ù�� �������۸� ���� �Է½����� ���� �� 16����
	//2.�Է½��Ե鿡 ���� �������� ����,3.�������� �� �迭�� ù ���Ҹ� ����Ű�� ������,4.����(stride)���� �迭�� ù���Ҹ� ����Ű�� ������ �ش����������� �ѿ�����
	//����Ʈ ����ũ���̴�.,5.�����µ��� �迭�� ù���Ҹ� ����Ű�� ������ �Է���������ܰ谡 �����ڷḦ �б� ������ �������۾� ��ġ������ �Ÿ�
}
