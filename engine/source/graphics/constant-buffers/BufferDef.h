#pragma once
#include "util/math/Matrix4x4.h"
namespace drach
{
	struct FrameBuffer
	{
		Matrix4x4f myViewMatrix;
	};

	struct ObjectBuffer
	{
		Matrix4x4f myModelMatrix;
	};
}