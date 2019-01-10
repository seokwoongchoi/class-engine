#pragma once

enum class StreamMode:uint
{
	Read,Write
};
class FileStream
{
public:
	
	void Open(const string& filePath,const StreamMode& mode);
	void Close();
	
	//==================================================================================
	//Write
	template<typename T, typename = typename enable_if<
		is_same<T,char>::value||  //들어온 타입 t 와 자료형이 같다면 true
		is_same<T, unsigned char>::value ||
		is_same<T, int>::value ||
		is_same<T, unsigned int>::value ||
		is_same<T, long>::value ||
		is_same<T, unsigned long>::value ||
		is_same<T, float>::value ||
		is_same<T, double>::value
	
	>::type> void Write(T& value)
	{
		out.write(reinterpret_cast<char*>(&value),sizeof(T));
		//char형 포인트로 바꿔서 그크기만큼 써질수있게

	}
	void Write(const string& value);
	void Write(const Vector2& value);
	void Write(const Vector3& value);
	void Write(const Vector4& value);
	void Write(const D3DXCOLOR& value);
	void Write(const Matrix& value);
	void Write(const vector<uint>& value);
	void Write(const vector<VertexTexture>& value);


	//==================================================================================
	//==================================================================================
	//Read
	//cdecl
	//stdcall조사 대표적함수먼지도 알아보기

	template<typename T, typename = typename enable_if< //조사 숙제
		is_same<T, char>::value ||  //들어온 타입 t 와 자료형이 같다면 true
		is_same<T, unsigned char>::value ||
		is_same<T, int>::value ||
		is_same<T, unsigned int>::value ||
		is_same<T, long>::value ||
		is_same<T, unsigned long>::value ||
		is_same<T, float>::value ||
		is_same<T, double>::value

	>::type> void Read(T& value)
	{
		in.read(reinterpret_cast<char*>(&value), sizeof(T));
		//char형 포인트로 바꿔서 그크기만큼 써질수있게

	}
	void Read(string& value);
	void Read(Vector2& value);
	void Read(Vector3& value);
	void Read(Vector4& value);
	void Read(D3DXCOLOR& value);
	void Read(Matrix& value);
	void Read(vector<uint>& value);
	void Read(vector<VertexTexture>& value);


	//==================================================================================

	
private:
	ifstream in;
	ofstream out;
	StreamMode mode;
};

