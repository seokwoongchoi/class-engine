#pragma once
#include "stdafx.h"

namespace Window
{
	HINSTANCE Instance;
	HWND Handle;
	function<LRESULT(HWND, UINT, WPARAM, LPARAM)> EditorProc;
	function<LRESULT(UINT, WPARAM, LPARAM)> MouseProc;
	function<void(const uint&, const int&)> Resize;

	inline LRESULT CALLBACK WndProc
	(
		HWND handle, //�������� �ڵ�
		uint message, //�޼���
		WPARAM wParam, //�ΰ�����
		LPARAM lParam //�ΰ�����
	)
	{
		if (EditorProc != nullptr)
			EditorProc(handle, message, wParam, lParam);

		if (MouseProc != nullptr)
			MouseProc(message, wParam, lParam);

		//switch ��
		//case���� ������ ���� �� ����
		switch (message)
		{
		case WM_DISPLAYCHANGE:
			if (Resize != nullptr && wParam != SIZE_MINIMIZED)
				Resize(lParam & 0xffff, (lParam >> 16) & 0xffff);
			break;
		case WM_SIZE: // ������ â�� ũ�Ⱑ �ٲ������
			if (Resize != nullptr && wParam != SIZE_MINIMIZED)
				Resize(lParam & 0xffff, (lParam >> 16) & 0xffff);
			break;
		case WM_CLOSE:
			DestroyWindow(handle);
			break;
		case WM_DESTROY:// �����찡 �ı�������
			PostQuitMessage(0); // ����޼����� ����
			break;
		default:
			//������ ó������ ���� �޼����� ó��
			return DefWindowProc(handle, message, wParam, lParam);
		}
		return 0;
	}

	inline void Create(HINSTANCE instance, const wstring& title, const uint& width, const uint& height, const bool& bFullScreen)
	{
		//������ Ŭ���� �����
		WNDCLASSEX wndClass;
		wndClass.cbClsExtra = 0;//�������� �߰�����
		wndClass.cbWndExtra = 0;//�������� �߰�����
		wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�������� ����
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);//Ŀ��
		wndClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);//������
		wndClass.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);//����������
		wndClass.hInstance = instance;//�������� ��ü
		wndClass.lpfnWndProc = (WNDPROC)WndProc; //������ ���ν����� �Լ� ������ //�Լ��� �̸��� �ּҰ�
		wndClass.lpszClassName = title.c_str(); // Ŭ�����̸�
		wndClass.lpszMenuName = nullptr; // �޴��̸�
		wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // ������ ��Ÿ��
		wndClass.cbSize = sizeof(WNDCLASSEX);

		//������ Ŭ���� ���
		WORD wHr = RegisterClassEx(&wndClass);
		assert(wHr != 0);
		//����׸�� �϶��� ����
		//���ڰ��� false�϶� �ߴ�, true�̸� ������

		if (bFullScreen)
		{
			DEVMODE devMode;
			ZeroMemory(&devMode, sizeof(DEVMODE));

			devMode.dmSize = sizeof(DEVMODE);
			devMode.dmPelsWidth = static_cast<DWORD>(width);
			devMode.dmPelsHeight = static_cast<DWORD>(height);
			devMode.dmBitsPerPel = 32;
			devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
		}

		DWORD option = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		if (bFullScreen == true)
			option |= WS_POPUP;
		else
			option |= WS_OVERLAPPEDWINDOW;

		//������ ����
		Handle = CreateWindowEx
		(
			WS_EX_APPWINDOW,//������ ��Ÿ��
			title.c_str(),//Ŭ������
			title.c_str(),//Ÿ��Ʋ��
			option,
			CW_USEDEFAULT,//x
			CW_USEDEFAULT,//y
			CW_USEDEFAULT,//width
			CW_USEDEFAULT,//height
			nullptr,
			nullptr,
			instance,
			nullptr
		);
		assert(Handle != nullptr);

		//������ �����ֱ�
		RECT rect;//left, top, right, bottom
		ZeroMemory(&rect, sizeof(RECT));

		rect.left = 0;
		rect.top = 0;
		rect.right = static_cast<LONG>(width);
		rect.bottom = static_cast<LONG>(height);

		uint centerX
			= static_cast<uint>((GetSystemMetrics(SM_CXSCREEN) - width) * 0.5f);
		uint centerY
			= static_cast<uint>((GetSystemMetrics(SM_CYSCREEN) - height) * 0.5f);

		//���������� ������ RECT�� ����
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		//������â �̵�
		MoveWindow
		(
			Handle,
			centerX,
			centerY,
			(rect.right - rect.left),
			(rect.bottom - rect.top),
			TRUE
		);

	}

	inline void Show()
	{
		//�츮�� ������â�� ȭ�� ���� �տ� ���
		SetForegroundWindow(Handle);

		//��Ŀ��
		SetFocus(Handle);

		//Ŀ�����̰�
		ShowCursor(TRUE);

		//������ �����ֱ�
		ShowWindow(Handle, SW_SHOWNORMAL);

		//������ ������Ʈ
		UpdateWindow(Handle);
	}

	inline const bool Update()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);//Ű���� �Է°��� ���ؼ���
			DispatchMessage(&msg);//WndProc, ���������ν����� �޼��� ����
		}

		return  msg.message != WM_QUIT;
	}

	inline void Destroy()
	{
		if (Settings::Get()->GetIsFullScreen() == true)
			ChangeDisplaySettings(nullptr, 0);

		//������ �ı�
		DestroyWindow(Handle);
		//����س��� �����츦 ��� ����
		UnregisterClass(Settings::Get()->GetAppName().c_str(), Instance);
	}

	inline const uint GetWidth()
	{
		RECT rect;
		GetClientRect(Handle, &rect);
		return static_cast<uint>(rect.right - rect.left);
	}

	inline const uint GetHeight()
	{
		RECT rect;
		GetClientRect(Handle, &rect);
		return static_cast<uint>(rect.bottom - rect.top);
	}
}
//#pragma once
//
//class Window final //���� �ڿ� final ���̸� ��Ŭ������ ���̻� ��ӽ�ų������.
//{
//public:
//	static function<void(const uint&, const uint&)> Resize;
//
//public:
//	Window();
//	virtual ~Window();//����Ҷ� �籸���Ҽ��ֵ��� virtual�� �ٿ��ش�.
//	                  // �����찡 ��ӹ����� �ȹ����� �𸣴ϱ� �Ҹ��ھտ� ���������� ��Ӹ��޴´�.
//	void Initialize();
//};