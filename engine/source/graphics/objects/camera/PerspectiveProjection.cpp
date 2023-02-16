#include "precompile-header/coreIncludes.h"
#include "PerspectiveProjection.h"

drach::Perspective::Perspective(const float aWidth, const float aHeight, const float someFOV, const float aNearPlane, const float aFarPlane)
	:ProjectionInterface(aWidth, aHeight), myFOV(someFOV), myNearPlane(aNearPlane), myFarPlane(aFarPlane)
{
}

drach::Matrix4x4f drach::Perspective::CalculateProjection()
{
	Matrix4x4f result;

	float x = 1.0f / (std::tan(myFOV / 2.0f));
	float y = (myResolution.myWidth / myResolution.myHeight) * (1.0f / (std::tan(myFOV / 2.0f)));
	float z1 = myFarPlane / (myFarPlane - myNearPlane);
	float z2 = -(myNearPlane * myFarPlane) / (myFarPlane - myNearPlane);

	result(1, 1) = x;
	result(2, 2) = y;
	result(3, 3) = z1;
	result(4, 3) = z2;

	return result;
}
