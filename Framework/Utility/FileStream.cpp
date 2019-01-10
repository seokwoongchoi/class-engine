#include "stdafx.h"
#include "FileStream.h"



void FileStream::Open(const string & filePath, const StreamMode & mode)
{
	this->mode = mode;

	switch (mode)
	{
	case StreamMode::Write:
		out.open(filePath, ios::out | ios::binary);
		assert(!out.fail());
		break;
	case StreamMode::Read:
		in.open(filePath, ios::in | ios::binary);
		assert(!in.fail());
		break;
	}
}

void FileStream::Close()
{
	switch (mode)
	{
	case StreamMode::Write:
		out.flush();
		out.close();
		break;
	case StreamMode::Read:
		in.clear();
		in.close();
		break;
	}
}

void FileStream::Write(const string & value)
{
	auto length = static_cast<uint>(value.length());//string쓸때는 먼저 string길이를 먼저 저장해야한다.
	Write(length);

	out.write(value.c_str(), length);
}

void FileStream::Write(const Vector2 & value)
{
	out.write(reinterpret_cast<const char*>(&value),sizeof(Vector2));
}

void FileStream::Write(const Vector3 & value)
{
	out.write(reinterpret_cast<const char*>(&value), sizeof(Vector3));
}

void FileStream::Write(const Vector4 & value)
{
	out.write(reinterpret_cast<const char*>(&value), sizeof(Vector4));
}

void FileStream::Write(const D3DXCOLOR & value)
{
	out.write(reinterpret_cast<const char*>(&value), sizeof(D3DXCOLOR));
}

void FileStream::Write(const Matrix & value)
{
	out.write(reinterpret_cast<const char*>(&value), sizeof(Matrix));
}

void FileStream::Write(const vector<uint>& value)
{
	auto length = static_cast<uint>(value.size());//백터도 길이 먼저 저장해줘야한다.
	Write(length);

	out.write(reinterpret_cast<const char*>(value.data()),sizeof(uint)*length); //벡터의 시작주소= data
}

void FileStream::Write(const vector<VertexTexture>& value)
{
	auto length = static_cast<uint>(value.size());//백터도 길이 먼저 저장해줘야한다.
	Write(length);

	out.write(reinterpret_cast<const char*>(value.data()), sizeof(VertexTexture)*length);
}

void FileStream::Read(string & value)
{
	uint length = 0;
	Read(length);

	value.resize(length);
	in.read(const_cast<char*>(value.c_str()),length);
}

void FileStream::Read(Vector2 & value)
{
	in.read(reinterpret_cast<char*>(&value), sizeof(Vector2));
}

void FileStream::Read(Vector3 & value)
{
	in.read(reinterpret_cast<char*>(&value), sizeof(Vector3));
}

void FileStream::Read(Vector4 & value)
{
	in.read(reinterpret_cast<char*>(&value), sizeof(Vector4));
}

void FileStream::Read(D3DXCOLOR & value)
{
	in.read(reinterpret_cast<char*>(&value), sizeof(D3DXCOLOR));
}

void FileStream::Read(Matrix & value)
{
	in.read(reinterpret_cast<char*>(&value), sizeof(Matrix));
}

void FileStream::Read(vector<uint>& value)
{
	uint length = 0;//백터도 길이 먼저 저장해줘야한다.
	Read(length);

	value.reserve(length);
	value.resize(length);

	in.read(reinterpret_cast<char*>(value.data()), sizeof(uint)*length); //벡터의 시작주소= data
}
void FileStream::Read(vector<VertexTexture>& value)
{
	uint length = 0;//백터도 길이 먼저 저장해줘야한다.
	Read(length);

	value.reserve(length);
	value.resize(length);

	in.read(reinterpret_cast<char*>(value.data()), sizeof(VertexTexture)*length); //벡터의 시작주소= data
}

