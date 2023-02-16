#pragma once
#include "util/math/Matrix4x4.h"
namespace drach
{
	struct Resolution
	{
		float myWidth, myHeight;
	};
	class ProjectionInterface
	{
	public:
		ProjectionInterface(const float aWidth, const float aHeight);
		virtual Matrix4x4f CalculateProjection() = 0;

		template<typename ProjectionType>
		ProjectionType& As()
		{
			return *static_cast<ProjectionType*>(this);
		}

	public:
		Resolution myResolution;
	};
}