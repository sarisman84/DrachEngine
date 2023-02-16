#pragma once
#include "ProjectionInterface.h"

namespace drach
{
	class Perspective : public ProjectionInterface
	{
	public:
		Perspective(const float aWidth, const float aHeight, const float someFOV, const float aNearPlane = 0.1f, const float aFarPlane = 1000.0f);
		Matrix4x4f CalculateProjection() override;

	public:
		float myFOV;
		float myNearPlane;
		float myFarPlane;
	};
}