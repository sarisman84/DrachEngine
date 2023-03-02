#pragma once
#include "imgui.h"
#include "ImGuizmo.h"
#include "util/Transform.h"
#include "graphics/objects/camera/Camera.h"
#include "graphics/objects/camera/PerspectiveProjection.h"

namespace editor_drach
{
	class Renderer;
	class EditorCamera
	{
	public:
		EditorCamera();

		void DrawGizmos();


	private:
		drach::Transform myTransform;
		drach::Camera myCamera;
		Renderer* myRenderer;
	};


	class EditorFramework
	{

	};
}