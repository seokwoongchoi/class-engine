#pragma once
#include "IWidget.h"
class Widget_ToolBar:public IWidget
{
public:
	Widget_ToolBar(class Context* context);
	virtual ~Widget_ToolBar() {}


	//void Initialize(class Context* context) override;
	void Begin() override;
	void Render() override;
	void End() override;
	
public:

	static float ToolBarHeight;
};

