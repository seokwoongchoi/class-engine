#include "stdafx.h"
#include "Vertex.h"
#define VERTEX_DATA D3D11_INPUT_PER_VERTEX_DATA
#define DXGI_FORMAT DXGI_FORMAT_R32G32B32_FLOAT

D3D11_INPUT_ELEMENT_DESC Vertex::Desc[]= //å ã�ƺ���
{
	{"POSITION",0,DXGI_FORMAT,0,0,VERTEX_DATA,0}//SemanticName:�����ϴ� �̸� ,SemanticIndex:�ø�ƽ��ȣ
	//DXGI_FORMAT_R32G32B32_FLOAT RGB32��Ʈ XYZ�� 4����Ʈ�� �÷������̴�
	//AlignedButeOffset :���ĵ� ����Ʈ�ɼ� �������� �����ǵ��������� �˷��ش�.
};

D3D11_INPUT_ELEMENT_DESC VertexColor::Desc[] = 
{
	{ "POSITION",0,DXGI_FORMAT,0,0,VERTEX_DATA,0 },
    { "COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,VERTEX_DATA,0 }
};

D3D11_INPUT_ELEMENT_DESC VertexTexture::Desc[] =
{
	{ "POSITION",0,DXGI_FORMAT,0,0,VERTEX_DATA,0 },
    { "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,VERTEX_DATA,0 }
};