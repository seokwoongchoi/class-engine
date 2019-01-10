#pragma once

class Settings
{
public:
	static Settings* Get();
	static void Delete();

public:
	const wstring& GetAppName() const { return appName; }
	//이렇게 하는 이유는 카피를 안하기 위해서 카피를하면 메모리를 하나더 할당하므로 비효율적
	HINSTANCE GetWindowInstance() const { return hInstance; }
	HWND GetWindowHandle() const { return handle; }
	const float& GetWidth() const { return width; }
	const float& GetHeight() const { return height; }
	const bool& GetIsVsync() const { return bVsync; }
	const bool& GetIsFullScreen() const { return bFullScreen; }
	const D3D11_VIEWPORT& GetViewport() const { return viewport; }
	//return 앞에 const로 묶어버리면 반환되는 값들을 수정을 불가하게 만든다 값을 변경못하게 묶어버린다.
	
	const Vector2& GetRelative()const { return relative; }

	void SetAppName(const wstring& appName) { this->appName = appName; }
	void SetWindowInstance(HINSTANCE hInstance) { this->hInstance = hInstance; }
	void SetWindowHandle(HWND handle) { this->handle = handle; }
	void SetWidth(const float& width) { this->width = width; }
	void SetHeight(const float& height) { this->height = height; }
	void SetIsVsync(const bool& bVsync) { this->bVsync = bVsync; }
	void SetIsFullScreen(const bool& bFullScreen) { this->bFullScreen = bFullScreen; }
	void SetViewport(const D3D11_VIEWPORT& viewport) { this->viewport = viewport; }

	void SetRelative(const Vector2& relative) { this->relative = relative; }

private:
	Settings();
	~Settings() {}

private:
	static Settings* instance;

	wstring appName;
	HINSTANCE hInstance;
	HWND handle;
	float width;
	float height;
	bool bVsync;//수직 동기화
	bool bFullScreen;

	D3D11_VIEWPORT viewport;
	Vector2 relative; //줄어든만큼의 상대적인 좌표`
};