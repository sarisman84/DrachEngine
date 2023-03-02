#include "precompile-header/coreIncludes.h"
#include "main.h"
#include "../../engine/source/main.h"
#include "util/other/PollingStation.h"
#include <d3d11.h>

#pragma comment (lib, "d3d11.lib")

extern "C"
{
	_declspec(dllexport) EditorInterface* ExportInterface()
	{
		return new editor_drach::EditorAPI();
	}
}

editor_drach::EditorAPI::~EditorAPI()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	ImGuizmo::Enable(false);
}

void editor_drach::EditorAPI::OnStart(EditorContext& someContext)
{
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(someContext.myWindowsInstance);
	ImGui_ImplDX11_Init(someContext.myDevice, someContext.myContext);
	ImGuizmo::Enable(true);
}


void editor_drach::EditorAPI::OnUpdate(EditorRuntimeContext& aRuntimeContext)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	auto& pollingStation = aRuntimeContext.myEngineIns.GetPollingStation();


	ImGui::Render();

}
