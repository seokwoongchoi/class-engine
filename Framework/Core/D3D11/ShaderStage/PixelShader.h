#pragma once
#include "BaseShader.h"

class PixelShader:public BaseShader
{
public:
	PixelShader(class Context* context);
	virtual ~PixelShader();
	
	void CreatePixelShader(const string& filePath, const string& functionName="PS");
	void Clear();
	void BindPipeline() override;
private:
	ID3D11PixelShader* pixelShader;
};