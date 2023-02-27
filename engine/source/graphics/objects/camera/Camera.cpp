#include "precompile-header/coreIncludes.h"
#include "Camera.h"
#include "util/Transform.h"
#include "logging/Logger.h"


drach::Camera::Camera()
{
}

drach::Camera::Camera(entt::registry* aReg, const entt::entity anEntity, ProjectionInterface* anInterface)
	:myRegistry(aReg), myEntity(anEntity), myProjection(std::shared_ptr<ProjectionInterface>(anInterface))
{
	myRegistry->get_or_emplace<Transform>(myEntity, myRegistry, myEntity);
}

drach::Matrix4x4f drach::Camera::ViewMatrix()
{
	if (!myRegistry)
	{
		LOG_ERROR("Attempting to calculate view matrix with an invalid camera! Returning an identity matrix instead!");
		return Matrix4x4f();
	}

	Transform& transform = myRegistry->get<Transform>(myEntity);
	return Matrix4x4f::GetFastInverse(transform.GetMatrix(true)) * myProjection->CalculateProjection();
}
