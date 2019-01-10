#pragma once
//버텍스를 할당해서 
struct Vertex //구조체는 기본적으로 퍼블릭 class는 기본적으로 private
{
	Vertex():Position(0,0,0){}//아무거도 안넣으면 0,0,0으로 셋팅
	Vertex(const Vector3& Position)
		:Position(Position){}
	Vertex(const float& x,const float& y,const float& z)
		:Position(x,y,z){}
	
	Vector3 Position;
	
	static D3D11_INPUT_ELEMENT_DESC Desc[];//버텍스가 몇개던 무조건 한개다
	static const uint Count = 1; //버텍스가 몇개던 무조건 한개다
};

struct VertexColor //구조체는 기본적으로 퍼블릭 class는 기본적으로 private
{
	VertexColor() 
		:Position(0, 0, 0) 
		,Color(0,0,0,1)
	    {}//아무거도 안넣으면 0,0,0으로 셋팅
	VertexColor(const Vector3& Position,const D3DXCOLOR& Color)
		:Position(Position),Color(Color)
	{}
	VertexColor(const float& x, const float& y, const float& z,
		const float& r, const float& g, const float& b, const float& a)
		:Position(x, y, z),Color(r,g,b,a)
	{}

	Vector3 Position;
	D3DXCOLOR Color;
	static D3D11_INPUT_ELEMENT_DESC Desc[];//버텍스가 몇개던 무조건 한개다
	static const uint Count = 2; //컬러가 추가되서 2가됬다.
};
struct VertexTexture //구조체는 기본적으로 퍼블릭 class는 기본적으로 private
{
	VertexTexture() :Position(0, 0, 0), Uv(0,0)
	{}//아무거도 안넣으면 0,0,0으로 셋팅
	VertexTexture(const Vector3& Position,const Vector2& Uv)
		:Position(Position), Uv(Uv)
	{}
	VertexTexture(const float& x, const float& y, const float& z,
		const float& u, const float& v)
		:Position(x, y, z), Uv(u,v)
	{}

	Vector3 Position;
	Vector2 Uv;
	static D3D11_INPUT_ELEMENT_DESC Desc[];//버텍스가 몇개던 무조건 한개다
	static const uint Count = 2; //컬러가 추가되서 2가됬다.
};