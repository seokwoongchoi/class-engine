#include "stdafx.h"
#include "Settings.h"

Settings* Settings::instance = nullptr;//instance는 static이므로 초기화

Settings * Settings::Get()
{
	if (!instance)//or instance==false
		instance = new Settings();

	return instance;
}

void Settings::Delete()//소멸자 대신
{
	SAFE_DELETE(instance);
}

Settings::Settings()
	: appName(L"")
	, hInstance(nullptr)
	, handle(nullptr)
	, width(0)
	, height(0)
	, bVsync(true)
	, bFullScreen(false)//언제 이것을 초기화할것인가 함수가 생성되기전에 초기화할때 사용한다.
	//int& a; 공간이 할당안되있으면 오류난다. 저것을 쓸려고 함수가 생성되기전에 초기화하면서 메모리를 미리만든다
	,relative(0,0)
{
}
