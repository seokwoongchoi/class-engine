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
	HRESULT hr = D3DX11CreateShaderResourceViewFromFileA(//이함수가 밑의create함수의 과정을 생략해준다.
		graphics->GetDevice(),
		filePath.c_str(),
		nullptr,
		nullptr,
		&srv, //이놈에서 데이터를 뽑아내야한다.
		nullptr


	);
	assert(SUCCEEDED(hr));

	ID3D11Texture2D* srctexture = nullptr; //원본 텍스쳐
	srv->GetResource(reinterpret_cast<ID3D11Resource**>(&srctexture));
	D3D11_TEXTURE2D_DESC desc;
	//desc를 뽑아내야한다. 
	srctexture->GetDesc(&desc);//텍스쳐의 정보를 얻어온다.
	 //ID3D11Resource로 원본을 뽑아올수있다.
	//원본 택스쳐를 얻어왔다. 
	size.x = static_cast<float>(desc.Width);
	size.y = static_cast<float>(desc.Height);
	format = desc.Format;
}

void Texture2D::CreateTexture2D(const float & width, const float & heihgt, const DXGI_FORMAT & format)
{//위의 과정을 풀어서 어떻게 돌아가는지 보여주기위해 작성한 함수이다.
	//texDesc.Width = static_cast<uint>(width);
	//texDesc.Height = static_cast<uint>(heihgt);
	//texDesc.MipLevels = 1;//밉맵은 사이즈를 모두 스케일 크기로 잘라놓는것?
	////예들 들어서 화면에 100,100사작형을 그렸다. 여기다가 텍스쳐 2000,2000짜리 를 붙이려면 텍스쳐를 압축시켜서
	////넣어야한다. 압축을 시키는 과정을 없애기위해서  똑같은 그림을 여러사이즈로 여러개 만들어놓는다. 이것이 밉맵
	//texDesc.ArraySize = 1; //텍스쳐를 한장만쓸수도있지만 텍스쳐를 배열로 쓸수도있다. 
	//texDesc.Format = format; //텍스쳐 한장의 픽셀을 몇비트로 쓸것인지 알파값을 뺄것인지 정해준다.
	//texDesc.SampleDesc.Count = 1;
	//texDesc.SampleDesc.Quality = 0; //다중표본화 suptersamplingantialiasing ssaa 계단현상 완화 ->2D용
	////MSAA 텍스쳐자체를 줄여서 계단현상완화 ->다중표본화(MULTISAMPLING) 3D에서는 모델하나가 삼각형으로 이루어져있으니까
	////얼굴부분만 멀리있으면 아에 랜더링안한다.
	//texDesc.Usage = D3D11_USAGE_DEFAULT;
	//texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;//3개의뷰중에 어디에묶을지 설정해줘야한다.
	//texDesc.CPUAccessFlags = 0;
	//texDesc.MiscFlags = 0;
	////위의설정값들을 바탕으로 원본을 만들어야한다
	//HRESULT hr = graphics->GetDevice()->CreateTexture2D
	//(
	//	&texDesc,
	//	nullptr,
	//	&texture
	//);
	//assert(SUCCEEDED(hr));

	//srvDesc.Format = format;//텍스쳐위의 원본 포멧이들어간다.
	//srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D; //멀로 만들어졌는지 알수있다.이거는 2D로 만들어짐
	//srvDesc.Texture2D.MostDetailedMip = 0;
	//srvDesc.Texture2D.MipLevels = 1;

	//hr = graphics->GetDevice()->CreateShaderResourceView
	//(
	//	texture//텍스쳐원본
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
