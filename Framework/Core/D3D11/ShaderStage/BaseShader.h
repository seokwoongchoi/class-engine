#pragma once

class BaseShader
{
public:
	BaseShader(class Context* context);
	virtual ~BaseShader();

	virtual void BindPipeline() = 0;//���������Լ�->��ӿ�
protected:
	bool CheckShaderError(const HRESULT& hr, ID3D10Blob* error); //ID3D10Blob<-�����ϵ� ���̴��� ���´�.
protected:
	class Graphics* graphics;
	string ShaderfilePath;
	string functionName;

};