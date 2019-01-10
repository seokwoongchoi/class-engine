#pragma once

class BaseShader
{
public:
	BaseShader(class Context* context);
	virtual ~BaseShader();

	virtual void BindPipeline() = 0;//순수가상함수->상속용
protected:
	bool CheckShaderError(const HRESULT& hr, ID3D10Blob* error); //ID3D10Blob<-컴파일된 쉐이더가 들어온다.
protected:
	class Graphics* graphics;
	string ShaderfilePath;
	string functionName;

};