#pragma once
#include "IWidget.h"
class Widget_Menubar:public IWidget
{
public:
	Widget_Menubar(class Context* context);
		
		
	virtual ~Widget_Menubar(){}

	void Begin()override{}
	void End()override {}

	void Render() override;

private:
	void OpenFileDialog(string filePath = "");
	void SaveFileDialog(string filePath = "");

private:
	bool bShowMetricsWindow;
	bool bShowStyleEditor;
	bool bShowDemoWindow;
};
