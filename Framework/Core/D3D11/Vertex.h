#pragma once
//���ؽ��� �Ҵ��ؼ� 
struct Vertex //����ü�� �⺻������ �ۺ� class�� �⺻������ private
{
	Vertex():Position(0,0,0){}//�ƹ��ŵ� �ȳ����� 0,0,0���� ����
	Vertex(const Vector3& Position)
		:Position(Position){}
	Vertex(const float& x,const float& y,const float& z)
		:Position(x,y,z){}
	
	Vector3 Position;
	
	static D3D11_INPUT_ELEMENT_DESC Desc[];//���ؽ��� ��� ������ �Ѱ���
	static const uint Count = 1; //���ؽ��� ��� ������ �Ѱ���
};

struct VertexColor //����ü�� �⺻������ �ۺ� class�� �⺻������ private
{
	VertexColor() 
		:Position(0, 0, 0) 
		,Color(0,0,0,1)
	    {}//�ƹ��ŵ� �ȳ����� 0,0,0���� ����
	VertexColor(const Vector3& Position,const D3DXCOLOR& Color)
		:Position(Position),Color(Color)
	{}
	VertexColor(const float& x, const float& y, const float& z,
		const float& r, const float& g, const float& b, const float& a)
		:Position(x, y, z),Color(r,g,b,a)
	{}

	Vector3 Position;
	D3DXCOLOR Color;
	static D3D11_INPUT_ELEMENT_DESC Desc[];//���ؽ��� ��� ������ �Ѱ���
	static const uint Count = 2; //�÷��� �߰��Ǽ� 2�����.
};
struct VertexTexture //����ü�� �⺻������ �ۺ� class�� �⺻������ private
{
	VertexTexture() :Position(0, 0, 0), Uv(0,0)
	{}//�ƹ��ŵ� �ȳ����� 0,0,0���� ����
	VertexTexture(const Vector3& Position,const Vector2& Uv)
		:Position(Position), Uv(Uv)
	{}
	VertexTexture(const float& x, const float& y, const float& z,
		const float& u, const float& v)
		:Position(x, y, z), Uv(u,v)
	{}

	Vector3 Position;
	Vector2 Uv;
	static D3D11_INPUT_ELEMENT_DESC Desc[];//���ؽ��� ��� ������ �Ѱ���
	static const uint Count = 2; //�÷��� �߰��Ǽ� 2�����.
};