#pragma once
class InputLayout
{
public:
	InputLayout(class Context* context);
	virtual ~InputLayout();

	//ia���� ���ؽ����۷� ���㼭 ���������� �ְ� ,���̾ƿ��ְ� ������ ��ġ 
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

