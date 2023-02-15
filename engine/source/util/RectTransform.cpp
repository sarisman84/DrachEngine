#include "precompile-header/coreIncludes.h"
#include "RectTransform.h"
#include "componentSys/Registry.h"
#include "logging/Logger.h"

drach::RectTransform::RectTransform()
{
}

drach::RectTransform::RectTransform(ecs::Registry* const aRegistry, ecs::Entity anEntityID)
{
}

drach::RectTransform::RectTransform(const RectTransform& aTransform)
{
	myCachedLocalMatrix = aTransform.myCachedLocalMatrix;
	myChildElementIDs = aTransform.myChildElementIDs;
	myEntityID = aTransform.myEntityID;
	myParentID = aTransform.myParentID;
	myRegistry = aTransform.myRegistry;
	position = aTransform.position;
	rotation = aTransform.rotation;
	size = aTransform.size;
}

drach::RectTransform drach::RectTransform::operator=(const RectTransform& aTransform)
{
	myCachedLocalMatrix = aTransform.myCachedLocalMatrix;
	myChildElementIDs = aTransform.myChildElementIDs;
	myEntityID = aTransform.myEntityID;
	myParentID = aTransform.myParentID;
	myRegistry = aTransform.myRegistry;
	position = aTransform.position;
	rotation = aTransform.rotation;
	size = aTransform.size;
	return *this;
}

drach::RectTransform::~RectTransform() = default;

void drach::RectTransform::AddChild(const ecs::Entity anEntity)
{
	if (!myRegistry)
	{
		LOG_ERROR("Tried to add a child to an invalid rect transform!");
		return;
	}

	if (myRegistry->Contains<RectTransform>(anEntity))
	{
		myChildElementIDs.push_back(anEntity);
		myRegistry->Get<RectTransform>(anEntity)->myParentID = myEntityID;
		return;
	}

	LOG_ERROR("Entity " + std::to_string(anEntity) + " does not contain a rect transform!");
}

drach::Matrix4x4f drach::RectTransform::GetMatrix(const bool aCacheMatrixImmmediate)
{
	if (myParentID != ecs::nullentity)
	{
		return GetLocalMatrix(aCacheMatrixImmmediate) * myRegistry->Get<RectTransform>(myEntityID)->GetMatrix(aCacheMatrixImmmediate);
	}
	return GetLocalMatrix(aCacheMatrixImmmediate);
}

drach::Matrix4x4f drach::RectTransform::GetLocalMatrix(const bool aCacheMatrixImmmediate)
{
	if (aCacheMatrixImmmediate)
		CacheTransform();
	return myCachedLocalMatrix;
}

void drach::RectTransform::CacheTransform()
{
	myCachedLocalMatrix = Matrix4x4f::TRS({ (float)position.x, (float)position.y, 0 }, { 0,0, rotation }, { (float)size.x, (float)size.y, 1 });
}
