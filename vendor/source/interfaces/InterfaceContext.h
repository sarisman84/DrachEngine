#pragma once
#include <wtypes.h>
struct StartContext
{
	HWND& myWindowsInstance;
	int myWindowWidth;
	int myWindowHeight;
};

struct RuntimeContext
{
	float myDeltaTime;
};
