#include "stdafx.h"
#include "Settings.h"

Settings* Settings::instance = nullptr;//instance�� static�̹Ƿ� �ʱ�ȭ

Settings * Settings::Get()
{
	if (!instance)//or instance==false
		instance = new Settings();

	return instance;
}

void Settings::Delete()//�Ҹ��� ���
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
	, bFullScreen(false)//���� �̰��� �ʱ�ȭ�Ұ��ΰ� �Լ��� �����Ǳ����� �ʱ�ȭ�Ҷ� ����Ѵ�.
	//int& a; ������ �Ҵ�ȵ������� ��������. ������ ������ �Լ��� �����Ǳ����� �ʱ�ȭ�ϸ鼭 �޸𸮸� �̸������
	,relative(0,0)
{
}
