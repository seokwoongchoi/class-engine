#pragma once
#include "stdafx.h"

template <class T> //���ø� Ŭ������ ������ �������� ���ǵǾ���Ѵ�. ���ӽ����̽��� ���ԵǸ�ȵȴ�.
//class���� �ٸ����� ������ �ȵȴ�. ���ø����� �ٸ� ������ ������ȵȴ�~~~
//���� ������, ���ؽ� ����, �ε������۸� ��Ƽ� �����ϴ� Ŭ����
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
	//���� �Լ��� �߰����Ѱ��̰� �ؿ��Լ��� �������ü��ִ� �Լ��� �����.
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
