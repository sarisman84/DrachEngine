#pragma once
#define NOMINMAX
#include "interfaces/EngineInterface.h"
#include "interfaces/EditorInterface.h"
#include <memory>



namespace drach
{
	class Scene;
	class GraphicsEngine;
	class ShaderFactory;
	class MeshFactory;
	class TextureFactory;
	class PollingStation;
	class Renderer;
}


class Engine : public EngineInterface
{
public:
	bool OnUpdate(RuntimeContext& someContext) override;
	bool OnStart(StartContext& someData, EditorInterface* anEditorAPI) override;
	void OnWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
public:
	inline const drach::PollingStation& GetPollingStation() { return *myPollingStation; }
	inline const drach::Scene& GetScene() { return *myTestScene; }
private:
	void InitConsole();
private:
	EditorInterface* myEditorInterface;
private:
	std::shared_ptr<drach::Scene> myTestScene;
private:
	std::shared_ptr<drach::GraphicsEngine> myGraphicsEngine;
	std::shared_ptr<drach::ShaderFactory> myShaderFactory;
	std::shared_ptr<drach::MeshFactory> myMeshFactory;
	std::shared_ptr<drach::TextureFactory> myTextureFactory;
	std::shared_ptr<drach::PollingStation> myPollingStation;
	std::shared_ptr<drach::Renderer> myRenderer;

};



