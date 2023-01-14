#pragma once
#include "interface/EngineInterface.h"


class Engine : public EngineInterface
{
public:
	virtual void OnUpdate() override;
	virtual void OnStart(StartContext& const someData) override;
	virtual void OnWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};



