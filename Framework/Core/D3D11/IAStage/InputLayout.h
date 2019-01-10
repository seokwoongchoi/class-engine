#pragma once
class InputLayout
{
public:
	InputLayout(class Context* context);
	virtual ~InputLayout();

	//ia에서 버텍스버퍼로 버꿔서 정점정보를 넣고 ,레이아웃넣고 정점의 위치 
	void Create
	(
		D3D11_INPUT_ELEMENT_DESC* descs,
		const uint& count,
		ID3D10Blob* vsBlob
	);

	void Create(ID3D10Blob* vsBlob);
	void Clear();

	void BindPipeline();
private:
	class Graphics* graphics;
	ID3D11InputLayout* inputLayout;
};

