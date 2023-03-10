#pragma once
#include <memory>
#include "util/math/Matrix4x4.h"
#include "entt/single_include/entt/entt.hpp"
#include "ProjectionInterface.h"

namespace drach
{
	class Camera
	{
	public:
		Camera();
		Camera(entt::registry* aReg, const entt::entity anEntity, ProjectionInterface* anInterface);
	public:
		Matrix4x4f ViewMatrix();
	private:
		entt::registry* myRegistry;
		entt::entity myEntity;
		std::shared_ptr<ProjectionInterface> myProjection;
	};
}