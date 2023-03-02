#pragma once
#include "InterfaceContext.h"

class EditorInterface;

class EngineInterface
{
public:
	virtual bool OnStart(StartContext& someContext, EditorInterface* anEditorInterface) = 0;
	virtual bool OnUpdate(RuntimeContext& aRuntimeContext) = 0;
	virtual void OnWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};