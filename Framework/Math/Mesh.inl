#include "Mesh.h"



template<class T>
inline void Mesh<T>::Clear()
{
	this->indices.clear();
	this->indices.shrink_to_fit();

	this->vertices.clear();
	this->vertices.shrink_to_fit();
}

template<class T>
inline void Mesh<T>::AddVertex(const T & vertex)
{
	this->vertices.emplace_back(vertex); //push_back은 내부적으로 객체를 복사하여 임시객처를 생성하기 때문에 복사생성자가 
	//호출되고 다시 임시객체를 삭제하기 위해 소멸자가 호출된다.
	//컨테이너에 들어가는 객체가 동적할당된 객체의 포인터이면 도움이 되지않을것이다. 포인터형변수의 복사 삭제가 성능에
	//큰영향을 주지는 않기 떄문
}

template<class T>
inline void Mesh<T>::AddVertices(const vector<T>& vertices)
{
	this->vertices.insert(this->vertices.end(), vertices.begin(), vertices.end());
	//내꺼의 맨뒤에다가 들어오는 놈의 비긴이랑 들어오는놈의 앤드를 넣겠다.
}

template<class T>
inline void Mesh<T>::SetVertices(const vector<T>& vertices)
{
	Clear();
	this->vertices.assign(vertices.begin(), vertices.end());
}

template<class T>
inline void Mesh<T>::AddIndex(const uint & index)
{
	this->indices.emplace_back(index);
}

template<class T>
inline void Mesh<T>::AddIndices(const vector<uint>& indices)
{
	this->indices.insert(This->indices.end(), indices.begin(), indices.end());
}

template<class T>
inline void Mesh<T>::Setindices(const vector<uint>& indices)
{
	Clear();
	this->indices.assign(indices.begin(), indices.end());
}

template<class T>
inline void Mesh<T>::Append(vector<T>& vertices, vector<uint>& indices)
{
	AppendVertices(vertices);
	AppendIndices(indices);
}

template<class T>
inline void Mesh<T>::Append(const uint & vertexOffset, const uint & vertexCount, const uint & indexOffset, const uint & indexCount, vector<T>& vertices, vector<uint>& indices)
{
	AppendVertices(vertexOffset,vertexCount,vertices);
	AppendIndices(indexOffset, indexCount, indices)
}

template<class T>
inline void Mesh<T>::AppendVertices(vector<T>& vertices)
{
	vertices = this->vertices;
	//vertices.assign(this->vertices.begin(), this->vertices.end());
}

template<class T>
inline void Mesh<T>::AppendVertices(const uint & offset, const uint & count, vector<T>& vertices)
{
	auto first = this->vertices.begin() + offset; //시작부터 오프셋부터 이동한위치
	auto last = this->vertices.begin() + offset + count;  
	//벡터가 배열의 형태를 하고있기때문에 가능하다.
	
	vertices.assign(first, last);
}

template<class T>
inline void Mesh<T>::AppendIndices(vector<uint>& indices)
{
	indices.assign(this->indices.begin(), this->indices.end());
}

template<class T>
inline void Mesh<T>::AppendIndices(const uint & offset, const uint & count, vector<uint>& indices)
{
	auto first = this->indices.begin() + offset; //시작부터 오프셋부터 이동한위치
	auto last = this->indices.begin() + offset + count;
	//벡터가 배열의 형태를 하고있기때문에 가능하다.

	indices.assign(first, last);
}
