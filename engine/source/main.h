#pragma once
#include "interface/EngineInterface.h"
#include "graphics/GraphicsEngine.h"

#include <memory>

class Engine : public EngineInterface
{
public:
	void OnUpdate() override;
	void OnStart(StartContext& const someData) override;
	void OnWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
private:
	std::unique_ptr<GraphicsEngine> myGraphicsEngine;
};



