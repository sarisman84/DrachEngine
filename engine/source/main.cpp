#include "main.h"
#include <iostream>
#include <d3d11.h>

void Engine::OnUpdate()
{

}

void Engine::OnStart(StartContext& const someData)
{
	myGraphicsEngine.reset(new GraphicsEngine(someData.myWindowsInstance, someData.myWindowWidth, someData.myWindowHeight, 120));
}

void Engine::OnWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
}

extern "C"
{
	_declspec(dllexport) EngineInterface* ExportInterface()
	{
		return new Engine();
	}
}