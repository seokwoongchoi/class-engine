#pragma once
#include "IResource.h"
class Material:public IResource//오브젝트의 재료는 텍스쳐다, 쉐이더도 메테리얼.
{
public:
	Material(class Context* context);
	virtual ~Material();

	class Shader* GetShader() const { return shader; }
	class Texture2D* GetDiffuseTexture()const { return diffuseTexture; } 
	//자기가내는 색이 diffusetexture

	void SetShader(const string& filePath);
	void SetDiffuseTexture(const string& filePath);

    void SaveToFile(const string& saveFilePath)override;
   
    void LoadFromFile(const string& loadFilePath)override;
	
private:
	class Shader* shader;
	class Texture2D* diffuseTexture;

	D3DXCOLOR diffuseColor;
};

