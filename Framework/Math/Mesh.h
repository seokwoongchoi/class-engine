#pragma once
#include "stdafx.h"

template <class T> //템플릿 클래스는 무조건 전역에서 정의되어야한다. 네임스페이스에 포함되면안된다.
//class위에 다른것이 있으면 안된다. 템플릿위에 다른 참조가 있으면안된다~~~
//정점 데이터, 버텍스 버퍼, 인덱스버퍼를 모아서 관리하는 클래스
class Mesh
{
public:
	Mesh() {}
	virtual ~Mesh() {}

	void Clear();
	void AddVertex(const T& vertex);
	void AddVertices(const vector<T>& vertices);
	void SetVertices(const vector<T>& vertices);

	void AddIndex(const uint& index);
	void AddIndices(const vector<uint>& indices);
	void Setindices(const vector<uint>& indices);
	//위의 함수는 추가만한것이고 밑에함수는 값을빼올수있는 함수를 만든다.
	const uint VerticesCount()const { return vertices.size(); }
	const uint IndicesCount()const { return indices.size(); }
	const uint TriangleCount()const { return IndicesCount() / 3; }
	
	void Append(vector<T>& vertices,vector<uint>& indices); //
	void Append(
		const uint& vertexOffset,
		const uint& vertexCount,
		const uint& indexOffset,
		const uint& indexCount,
		vector<T>&vertices,
		vector<uint>& indices
	);

	const vector<T>& AppendVertices() const { return vertices; }
	void AppendVertices(vector<T>& vertices);
	void AppendVertices
	(
		const uint& offset,
		const uint& count,
		vector<T>&vertices
	);
	
	const vector<uint>& AppendIndices()const { return indices; }
	void AppendIndices(vector<uint>& indices);
	void AppendIndices
	(
		const uint& offset,
		const uint& count,
		vector<uint>&indices
	);
private:
	vector<T> vertices;
	vector<uint> indices;

};
#include "Mesh.inl"
