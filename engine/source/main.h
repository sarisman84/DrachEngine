#pragma once
#define NOMINMAX
#include "interface/EngineInterface.h"
#include <memory>



namespace drach
{
	class Scene;
	class GraphicsEngine;
	class ShaderFactory;
	class MeshFactory;
	class PollingStation;
	class Renderer;
}


template<typename T, int N>
struct counter_id {
	constexpr static int id = counter_id<T, N + 1>::id;
};



class Engine : public EngineInterface
{
public:
	const bool OnUpdate(const float aDeltaTime) override;
	void OnStart(StartContext& const someData) override;
	void OnWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
private:
	void InitConsole();
private:
	std::unique_ptr<drach::Scene> myTestScene;
private:
	std::unique_ptr<drach::GraphicsEngine> myGraphicsEngine;
	std::unique_ptr<drach::ShaderFactory> myShaderFactory;
	std::unique_ptr<drach::MeshFactory> myMeshFactory;
	std::unique_ptr<drach::PollingStation> myPollingStation;
	std::unique_ptr<drach::Renderer> myRenderer;
};



