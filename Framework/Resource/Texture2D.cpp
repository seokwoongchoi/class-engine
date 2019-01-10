#include "stdafx.h"
#include "Texture2D.h"

Texture2D::Texture2D(Context * context)
	:IResource(context)
	,srv(nullptr)
	,size(1,1)
	,format(DXGI_FORMAT_R8G8B8A8_UNORM)

{
	graphics = context->GetSubsystem<Graphics>();
	
	
}

Texture2D::~Texture2D()
{
	Clear();
	
}



void Texture2D::CreateTextureFromFile(const string & filePath)
{
	this->filePath = filePath;
	HRESULT hr = D3DX11CreateShaderResourceViewFromFileA(//���Լ��� ����create�Լ��� ������ �������ش�.
		graphics->GetDevice(),
		filePath.c_str(),
		nullptr,
		nullptr,
		&srv, //�̳𿡼� �����͸� �̾Ƴ����Ѵ�.
		nullptr


	);
	assert(SUCCEEDED(hr));

	ID3D11Texture2D* srctexture = nullptr; //���� �ؽ���
	srv->GetResource(reinterpret_cast<ID3D11Resource**>(&srctexture));
	D3D11_TEXTURE2D_DESC desc;
	//desc�� �̾Ƴ����Ѵ�. 
	srctexture->GetDesc(&desc);//�ؽ����� ������ ���´�.
	 //ID3D11Resource�� ������ �̾ƿü��ִ�.
	//���� �ý��ĸ� ���Դ�. 
	size.x = static_cast<float>(desc.Width);
	size.y = static_cast<float>(desc.Height);
	format = desc.Format;
}

void Texture2D::CreateTexture2D(const float & width, const float & heihgt, const DXGI_FORMAT & format)
{//���� ������ Ǯ� ��� ���ư����� �����ֱ����� �ۼ��� �Լ��̴�.
	//texDesc.Width = static_cast<uint>(width);
	//texDesc.Height = static_cast<uint>(heihgt);
	//texDesc.MipLevels = 1;//�Ӹ��� ����� ��� ������ ũ��� �߶���°�?
	////���� �� ȭ�鿡 100,100�������� �׷ȴ�. ����ٰ� �ؽ��� 2000,2000¥�� �� ���̷��� �ؽ��ĸ� ������Ѽ�
	////�־���Ѵ�. ������ ��Ű�� ������ ���ֱ����ؼ�  �Ȱ��� �׸��� ����������� ������ �������´�. �̰��� �Ӹ�
	//texDesc.ArraySize = 1; //�ؽ��ĸ� ���常������������ �ؽ��ĸ� �迭�� �������ִ�. 
	//texDesc.Format = format; //�ؽ��� ������ �ȼ��� ���Ʈ�� �������� ���İ��� �������� �����ش�.
	//texDesc.SampleDesc.Count = 1;
	//texDesc.SampleDesc.Quality = 0; //����ǥ��ȭ suptersamplingantialiasing ssaa ������� ��ȭ ->2D��
	////MSAA �ؽ�����ü�� �ٿ��� ��������ȭ ->����ǥ��ȭ(MULTISAMPLING) 3D������ ���ϳ��� �ﰢ������ �̷���������ϱ�
	////�󱼺κи� �ָ������� �ƿ� ���������Ѵ�.
	//texDesc.Usage = D3D11_USAGE_DEFAULT;
	//texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;//3���Ǻ��߿� ��𿡹����� ����������Ѵ�.
	//texDesc.CPUAccessFlags = 0;
	//texDesc.MiscFlags = 0;
	////���Ǽ��������� �������� ������ �������Ѵ�
	//HRESULT hr = graphics->GetDevice()->CreateTexture2D
	//(
	//	&texDesc,
	//	nullptr,
	//	&texture
	//);
	//assert(SUCCEEDED(hr));

	//srvDesc.Format = format;//�ؽ������� ���� �����̵���.
	//srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D; //�ַ� ����������� �˼��ִ�.�̰Ŵ� 2D�� �������
	//srvDesc.Texture2D.MostDetailedMip = 0;
	//srvDesc.Texture2D.MipLevels = 1;

	//hr = graphics->GetDevice()->CreateShaderResourceView
	//(
	//	texture//�ؽ��Ŀ���
	//	, &srvDesc
	//	, &srv
	//);
	//assert(SUCCEEDED(hr));
}

void Texture2D::Clear()
{
	SAFE_RELEASE(srv);
}

void Texture2D::BindPipeline(const ShaderType & type, const uint & slot)
{
	auto dc = graphics->GetDeviceContext();

	switch (type)
	{

	case ShaderType::VS:dc->VSSetShaderResources(slot,1,&srv);	break;
	case ShaderType::PS:dc->PSSetShaderResources(slot,1,&srv);	break;
	case ShaderType::GS:dc->GSSetShaderResources(slot,1,&srv);	break;
	case ShaderType::CS:dc->CSSetShaderResources(slot,1,&srv);	break;
	}
}

void Texture2D::LoadFromFile(const string & loadFilePath)
{
	//Create(loadFilePath);
	if (loadFilePath.rfind(".xml") != string::npos)
	{

	}
	else
		CreateTextureFromFile(loadFilePath);
}
