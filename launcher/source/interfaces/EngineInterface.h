#pragma once
#include <wtypes.h>
struct StartContext
{
	HWND* myWindowsInstance;
	int myWindowWidth;
	int myWindowHeight;
};

class EngineInterface 
{
public:
	virtual void OnStart(StartContext& const someData) = 0;
	virtual void OnUpdate() = 0;
	virtual void OnWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};