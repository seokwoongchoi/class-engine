#pragma once
#include "IWidget.h"

class Widget_ProgressBar :public IWidget
{
public:
	Widget_ProgressBar(class Context* context);
	virtual~Widget_ProgressBar();

private:
	void Begin() override;
	void Render()override;
private:
	string status;
	float progress;
};

