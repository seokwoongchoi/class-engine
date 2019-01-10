#pragma once
#include "IResource.h"

class Shader:public IResource
{
public:
	Shader(class Context* context);
	virtual ~Shader();

	class InputLayout* GetInputLayout()const  { return inputLayout; }

	class VertexShader* GetVertexShader()const { return vertexShader; }
	class PixelShader* GetPixelShader()const { return pixelShader; }

	void CreateVertexShader(const string& filePath,const string& functionName="VS");
	void CreatePixelShader(const string& filePath, const string& functionName = "PS");

	void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* descs = nullptr, const uint& count = 0);



	virtual void LoadFromFile(const string& loadFilePath);//원래 버텍스쉐이더를 따로따로 불러왔었다.
	//이제 이 쉐이더클래스를 만들어서 버텍스,픽셀셰이더를 한번에 불러올수있다.
	
private:
	class InputLayout* inputLayout;
	class VertexShader* vertexShader;
	class PixelShader* pixelShader;

};