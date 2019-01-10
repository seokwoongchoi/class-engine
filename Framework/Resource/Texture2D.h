#pragma once
#include "IResource.h"
class Texture2D:public IResource
{
public:
	Texture2D(class Context* context);
	virtual ~Texture2D();
	
	ID3D11ShaderResourceView* GetShaderResourceView()const { return srv; }

	//const string& GetFilePath() const { return filePath; }
	const Vector2& GetSize() const {
		return size;	}//여기서 안만든다.
	//텍스쳐의 원본크기를 얻어오는 함수를 만든다.
	

	void CreateTextureFromFile(const string& filePath);
	void CreateTexture2D(const float& width,const float& heihgt,const DXGI_FORMAT& format);
	void Clear();
	void BindPipeline(const ShaderType& type, const uint& slot);

	virtual void LoadFromFile(const string& loadFilePath) override;

private:
	//class Context* context;
	class Graphics* graphics;
	ID3D11ShaderResourceView* srv; //view붙어있으면 텍스쳐들 변환시켜주는놈들이다.
	 //<-이놈이 srv의 원본이놈이 srv에 들어간다.

	//string filePath;


	//픽셀값은 rgba로 이루어져있으니까 깊이값을 저장하기위해 또다른 도화지를 만든다는 개념
	//
	Vector2 size;
	DXGI_FORMAT format;

};