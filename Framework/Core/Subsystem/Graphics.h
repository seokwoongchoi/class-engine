#pragma once
#include "ISubsystem.h"
//Device, DeviceContext �����ϴ³�
class Graphics : public ISubsystem
{
public:
	Graphics(class Context* context);
	virtual ~Graphics();

	//Getter=================================================================
	ID3D11Device* GetDevice() const { return device; }
	ID3D11DeviceContext* GetDeviceContext() const { return deviceContext; }
	IDXGISwapChain* GetSwapChain() const { return swapChain; }
	//=======================================================================

	const bool Initialize() override;//DirecxtX 11 �� �ʱ�ȭ
	 //���⼭�� ������Ʈ�� ������������� �θ� �����߱⶧���� �� �Լ��� �������

	void Resize(const uint& width, const uint& height); //����۸� ������ִ� �Լ�

	//=========������۸�======================================================
	void BeginScene(); //�׸��� �����ϴ� �Լ�
	void EndScene(); //�׸��� ����ϴ� �Լ�
	//========================================================================

private:
	ID3D11Device* device; // ���� ����³�
	ID3D11DeviceContext* deviceContext;// ���� �׸��³�(�����ϴ³�)
	IDXGISwapChain* swapChain; // ���� ���۸�

							   //�ϴ� �Ѿ
	ID3D11Debug* debugDevice;
	uint gpuMemorySize;
	wstring gpuDescription;
	uint numerator;
	uint denominator;

	D3DXCOLOR clearColor;//�ϳ��� ����� ó������� ��α⶧���� ���� ������� ����, �׶� ����ϴ� ����
	ID3D11DepthStencilView* depthStencilView; //���� ���̹���
	ID3D11RenderTargetView* renderTargetView; // ���� ����Ÿ�ٹ���
	D3D11_VIEWPORT viewport;//����Ÿ���� ������â ��� ������ ǥ�������� ���� ��ǥ��, ������ ����
};