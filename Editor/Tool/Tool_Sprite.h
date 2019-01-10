#pragma once
class Tool_Sprite
{
public:
	static Tool_Sprite& Get() 
	{
		static Tool_Sprite instance;
		return instance;
	}

	void Initialize(class Context* context);
	void Render();

	bool& IsVisible() { return bVisible; }
private:
	Tool_Sprite(){}
	virtual ~Tool_Sprite(){}

	void ShowSpriteFrame(const struct ImVec2& size);
	void ShowSpriteInfo(const struct ImVec2& size);
	void ShowSpriteEdit(const struct ImVec2& size);

	void DragDrop();
	void Mouse();
private:
	class Context* context;
	class ResourceManager* resourceManager;
	class Texture2D* texture;

	float gridSpacing;
	D3DXCOLOR gridColor;

	bool bVisible;
	bool bRender;
	bool bCheckSize;
	bool bCheckOff;
	float width;
	float height;
	float offsetx;
	float offsety;
	vector<ImVec2>mouses;
	vector<float>widths;
	vector<float>heights;
	vector<float>offsetxs;
	vector<float>offsetys;
};

