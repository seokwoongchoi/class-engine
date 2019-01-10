#pragma once
#include "stdafx.h"

class ILogger
{
public:
	
	virtual ~ILogger(){}
	virtual void Log(const string& log, const int& type) = 0;
};