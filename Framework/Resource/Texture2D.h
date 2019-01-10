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
		return size;	}//���⼭ �ȸ����.
	//�ؽ����� ����ũ�⸦ ������ �Լ��� �����.
	

	void CreateTextureFromFile(const string& filePath);
	void CreateTexture2D(const float& width,const float& heihgt,const DXGI_FORMAT& format);
	void Clear();
	void BindPipeline(const ShaderType& type, const uint& slot);

	virtual void LoadFromFile(const string& loadFilePath) override;

private:
	//class Context* context;
	class Graphics* graphics;
	ID3D11ShaderResourceView* srv; //view�پ������� �ؽ��ĵ� ��ȯ�����ִ³���̴�.
	 //<-�̳��� srv�� �����̳��� srv�� ����.

	//string filePath;


	//�ȼ����� rgba�� �̷���������ϱ� ���̰��� �����ϱ����� �Ǵٸ� ��ȭ���� ����ٴ� ����
	//
	Vector2 size;
	DXGI_FORMAT format;

};