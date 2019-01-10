#pragma once
#include "IResource.h"
class Material:public IResource//������Ʈ�� ���� �ؽ��Ĵ�, ���̴��� ���׸���.
{
public:
	Material(class Context* context);
	virtual ~Material();

	class Shader* GetShader() const { return shader; }
	class Texture2D* GetDiffuseTexture()const { return diffuseTexture; } 
	//�ڱⰡ���� ���� diffusetexture

	void SetShader(const string& filePath);
	void SetDiffuseTexture(const string& filePath);

    void SaveToFile(const string& saveFilePath)override;
   
    void LoadFromFile(const string& loadFilePath)override;
	
private:
	class Shader* shader;
	class Texture2D* diffuseTexture;

	D3DXCOLOR diffuseColor;
};

