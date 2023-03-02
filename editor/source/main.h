#pragma once
#include "interfaces/EditorInterface.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imguizmo/ImGuizmo.h"

namespace editor_drach
{
	class EditorAPI : public EditorInterface
	{
	public:
		~EditorAPI();
		// Inherited via EditorInterface
		virtual void OnStart(EditorContext& someContext) override;
		virtual void OnUpdate(EditorRuntimeContext& aRuntimeContext) override;

	};
}