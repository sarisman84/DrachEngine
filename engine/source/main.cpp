#include "main.h"
#include <iostream>


void Engine::OnUpdate()
{

}

void Engine::OnStart(StartContext& const someData)
{
	
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