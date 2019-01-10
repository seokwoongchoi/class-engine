#pragma once
class Sampler
{
public:
	Sampler(class Context* context);
	virtual ~Sampler();

	ID3D11SamplerState* GetState()const { return state; }
	void Create(
		const ShaderType& shaderType,
		const uint& slot,
		const D3D11_FILTER& filter=D3D11_FILTER_ANISOTROPIC, //���漺����
		const D3D11_TEXTURE_ADDRESS_MODE addressMode=D3D11_TEXTURE_ADDRESS_WRAP, //uv��ǥ 0,0~1,1(*x)�� �����ϰ� ���ºκ��� ��� ä�������
		const D3D11_COMPARISON_FUNC& comparisonFunc =D3D11_COMPARISON_ALWAYS);
	void Clear();

	void BindPipeline();

private:
	class Graphics* graphics;
	ID3D11SamplerState* state;
	ShaderType shaderType;
	uint slot;

	D3D11_FILTER filter;
	D3D11_TEXTURE_ADDRESS_MODE addressMode;
	D3D11_COMPARISON_FUNC comparisonFunc;
};

