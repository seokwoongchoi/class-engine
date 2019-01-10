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
int WINAPI WinMain //프로그램의 진입점 프로그램이 실행되면 이헤더가 가장먼저 실행된다.
(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpszCmdParam, 
	int nCmdShow
)
{
	srand(static_cast<uint>(time(nullptr)));//어떤자료형으로 변환할지 <>로 표시해준다)
	
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
	
	//프로그램이 실행될때 제일처음 초기화됨

	//Game* game = new Game(); //게임을 만들고

	//WPARAM wParam = game->Run(); //런돌리고

	//SAFE_DELETE(game); //지워진다.
	//return wParam;  
	return 0;

}
//Object ->(class->틀,instance->실제객체화)
//캐스팅 종류 static_cast ->기본적        dynamic_cast ->rti상속 가상함수 포함 (몇몇 조건
//             const_cast-> 상수성 제거   reinterpret_cast ->()강제 형변환

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
