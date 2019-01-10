#include "stdafx.h"
#include "Framework/Core/Window.h"
#include "Editor/Editor.h"

static Context* context;
static Editor* editor;
static Engine* engine;
static Graphics* graphics;
void Initialize();
void Resize(const uint& , const uint& );
void Destroy();
int WINAPI WinMain //���α׷��� ������ ���α׷��� ����Ǹ� ������� ������� ����ȴ�.
(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpszCmdParam, 
	int nCmdShow
)
{
	srand(static_cast<uint>(time(nullptr)));//��ڷ������� ��ȯ���� <>�� ǥ�����ش�)
	
	Window::Create(hInstance, L"D2D11Game", 1280, 720, false);
	Window::Show();

	Initialize();
	
	while(Window::Update())
	{
		engine->Update();

		graphics->BeginScene();
		{
			editor->Render();
		}
		graphics->EndScene();
	}
	Destroy();


	Window::Destroy();
	
	//���α׷��� ����ɶ� ����ó�� �ʱ�ȭ��

	//Game* game = new Game(); //������ �����

	//WPARAM wParam = game->Run(); //��������

	//SAFE_DELETE(game); //��������.
	//return wParam;  
	return 0;

}
//Object ->(class->Ʋ,instance->������üȭ)
//ĳ���� ���� static_cast ->�⺻��        dynamic_cast ->rti��� �����Լ� ���� (��� ����
//             const_cast-> ����� ����   reinterpret_cast ->()���� ����ȯ

//nullptr 
void Initialize()
{
	Settings::Get()->SetAppName(L"D2D11Game");
	Settings::Get()->SetWindowInstance(Window::Instance);
	Settings::Get()->SetWindowHandle(Window::Handle);
	Settings::Get()->SetWidth(static_cast<float>(Window::GetWidth()));
	Settings::Get()->SetHeight(static_cast<float>(Window::GetHeight()));
	Settings::Get()->SetIsVsync(true);
	Settings::Get()->SetIsFullScreen(false);
	Settings::Get()->SetRelative
	(
		Vector2
		(
			static_cast<float>(Window::GetWidth())
		   ,static_cast<float>(Window::GetHeight())
		)
	);

	context = new Context();
	editor = new Editor();
	
	engine = new Engine(context);
	engine->Initialize();
	
	editor->Initialize(context);
	graphics = context->GetSubsystem<Graphics>();

	Window::EditorProc = Editor::EditorProc;
	Window::MouseProc = Input::MouseProc;
	Window::Resize = Resize;

	

}
void Resize(const uint& width,const uint& height)
{
	if (!graphics || !editor)
		return;
	graphics->Resize(width, height);
	editor->Resize();
}
void Destroy()
{
	SAFE_DELETE(editor);
	SAFE_DELETE(engine);
	SAFE_DELETE(context);
}
