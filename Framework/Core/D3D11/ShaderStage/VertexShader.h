#pragma once
#include "BaseShader.h"
class VertexShader:public BaseShader
{
public:
	VertexShader(class Context* context);
	virtual ~VertexShader();

	ID3D10Blob* GetBlob()const { return vsBlob; }



	void CreateVertexShader(const string& filePath, const string& functionName = "VS"); //functionName
	void Clear();

	void BindPipeline() override;



private:
	ID3D11VertexShader* vertexShader;
	ID3D10Blob* vsBlob;
};