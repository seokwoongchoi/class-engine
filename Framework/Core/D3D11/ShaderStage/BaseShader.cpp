#include "stdafx.h"
#include "BaseShader.h"

BaseShader::BaseShader(Context* context)
	:ShaderfilePath("")
	,functionName("")
{
	graphics = context->GetSubsystem<Graphics>();
}

BaseShader::~BaseShader()
{
}



bool BaseShader::CheckShaderError(const HRESULT & hr, ID3D10Blob * error)//매개변수를 참조를했다는것은 값이무조건들어온다 포인터는 널이들어올수있다.
{
	if (FAILED(hr))
	{
		if (error != nullptr)
		{
			string str = reinterpret_cast<const char*>(error->GetBufferPointer());
			//getbufferpointer<-의 시작주소를 뽑아준다. string에 넣어주기위해 캐스팅했다.
			MessageBoxA
			(
				Settings::Get()->GetWindowHandle(),
				str.c_str(),
				"Shader Error!!",
				MB_OK
			);
		}
		return false;
	}
	return true;//hr이 성공했다면 트루 반환
}
