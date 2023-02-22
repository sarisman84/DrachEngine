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
	std::shared_ptr<drach::GraphicsEngine> myGraphicsEngine;
	std::shared_ptr<drach::ShaderFactory> myShaderFactory;
	std::shared_ptr<drach::MeshFactory> myMeshFactory;
	std::shared_ptr<drach::PollingStation> myPollingStation;
	std::shared_ptr<drach::Renderer> myRenderer;
};



