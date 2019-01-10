#pragma once
//����
//�� ������� C^Dll - BUFFEtDESC ����ü�� M D l 1_SUBRES0URCE_DATA ����ü
//�� ä���� ID3DllDevice : : CreateBuf fer�� ȣ���ؾ� �Ѵ�.������ ���� ���۴�
//ID3DllDeviceContext : : IASetVertexBuf fers �޼��带 �̿��ؼ� �Է� ������
//	�ܰ迡 ����) ���� ���۴� IMDllDeviceContext : : IASetlndexBuf fer �޼��带
//	�̿��ؼ� ���´�.����ȭ���� ���� ���ϱ����� ID3DllDeviceContext : : Draw �޼�
//	��� �׸�������ȭ�� ���ϱ����� ID3DllDeviceContext : : Drawlndexed �޼���
//	�α׸���.

class VertexBuffer //������ ����� ���ؽ� ���۷� ����� ���ε� ���������� �Լ��� ���������ο� ���ν�Ų��.
{
public:
	VertexBuffer(class Context* context);
	virtual ~VertexBuffer();
	
	template<typename T>
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);//DEFAULT�� 
	//���� �����ΰ��� ������ �װ��� �����ϰ� �ȳ����� ����Ʈ�ȴ�.
	void Clear();

	void* Map();//ó���� ���ؽ��� �����Ҷ� updatesubresorce�Լ��� �̿��ؾ� ���������ο� ����ȴ�.
	//fense����
	void Unmap();

	void BindPipeline();

private:
	class Graphics* graphics;

	ID3D11Buffer* vbuffer; //�������� �������·� �ٲ㼭 ���������ο� ���´�.
	uint stride;
	uint offset; //���� ������ ��ȣ
};

template<typename T> //���ø��Լ��� ����� �������.
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE & usage)
{
	assert(!vertices.empty());//���࿡ T�� ��������� ���ؽ����۸� �����ʿ䰡 �����ϱ� assert�� ���´�.
	//vertices.empty ��Ƽ�� Ʈ�� ���Ʈ�ȿ��� Ʈ��� �׳��н��ϱ� ���Ʈ�ȿ��ִ°� �޽��θ������Ѵ�.
	
	Clear(); //Ŭ����� �ʱ�ȭ

	stride = sizeof(T); //T�������� ��ŭ�� ������
	

	D3D11_BUFFER_DESC bufferDesc;//ID3D11Buffer�� �������->DESC�� ����ȴ�
	
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC)); //USAGE->�̹��۸� ��� ����ϴ°������� ���� 
	
	if (usage == D3D11_USAGE_DYNAMIC)
	{
		bufferDesc.Usage = usage; //USAGE�� �б⸸ �Ҽ��ְ� ���������� ��������.
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
		bufferDesc.Usage = usage;

	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(T)*vertices.size();

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = vertices.data();//�ڱⰡ �������ִ� �迭�� ��������Ʈ�� �ѱ��->&vertices[0]; ��Ƽ������ 0���� �迭�ּ�
//�� ����	
	HRESULT hr = graphics->GetDevice()->CreateBuffer
	(
		&bufferDesc,
		&subData,
		&vbuffer
	);
	assert(SUCCEEDED(hr));
}
