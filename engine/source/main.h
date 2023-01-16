#pragma once
#include "interface/EngineInterface.h"
#include "graphics/GraphicsEngine.h"

#include <memory>


template<typename T, int N>
struct counter_id {
	constexpr static int id = counter_id<T, N + 1>::id;
};



class Engine : public EngineInterface
{
public:
	void OnUpdate() override;
	void OnStart(StartContext& const someData) override;
	void OnWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
private:
	std::unique_ptr<GraphicsEngine> myGraphicsEngine;
};



