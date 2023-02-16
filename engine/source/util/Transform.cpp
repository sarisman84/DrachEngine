#include "precompile-header/coreIncludes.h"
#include "Transform.h"
#include "componentSys/Registry.h"
#include "logging/Logger.h"


drach::Transform::Transform(ecs::Registry* const aRegistry, ecs::Entity anEntityID)
	:myRegistry(aRegistry), myEntityID(anEntityID)
{
}

drach::Transform::~Transform() = default;

drach::Transform::Transform()
	:myRegistry(nullptr), myEntityID(ecs::nullentity)
{

}

drach::Transform::Transform(const Transform& aTransform)
{
	memcpy(this, &aTransform, sizeof(Transform));
	/*myCachedLocalMatrix = aTransform.myCachedLocalMatrix;
	myChildElementIDs = aTransform.myChildElementIDs;
	myEntityID = aTransform.myEntityID;
	myParentID = aTransform.myParentID;
	myRegistry = aTransform.myRegistry;
	position = aTransform.position;
	rotation = aTransform.rotation;
	size = aTransform.size;*/
}

drach::Transform::Transform(Transform&& aTransform)
{
	memcpy(this, &aTransform, sizeof(Transform));
	memset(&aTransform, 0, sizeof(Transform));
}

drach::Transform& drach::Transform::operator=(const Transform& aTransform)
{
	memcpy(this, &aTransform, sizeof(Transform));
	/*myCachedLocalMatrix = aTransform.myCachedLocalMatrix;
	myChildElementIDs = aTransform.myChildElementIDs;
	myEntityID = aTransform.myEntityID;
	myParentID = aTransform.myParentID;
	myRegistry = aTransform.myRegistry;
	position = aTransform.position;
	rotation = aTransform.rotation;
	size = aTransform.size;*/
	return *this;
}

drach::Transform& drach::Transform::operator=(Transform&& aTransform)
{
	memcpy(this, &aTransform, sizeof(Transform));
	memset(&aTransform, 0, sizeof(Transform));

	return *this;
}



void drach::Transform::AddChild(const ecs::Entity anEntity)
{
	if (!myRegistry)
	{
		LOG_ERROR("Tried to add a child to an invalid transform!");
		return;
	}
	if (myRegistry->Contains<Transform>(anEntity))
	{
		myChildElementIDs.push_back(anEntity);
		myRegistry->Get<Transform>(anEntity)->myParentID = myEntityID;
		return;
	}
	LOG_ERROR("Entity " + std::to_string(anEntity) + " does not contain a transform!");
}

drach::Matrix4x4f drach::Transform::GetMatrix(const bool aCacheMatrixImmmediate)
{

	if (myParentID != ecs::nullentity)
	{
		return GetLocalMatrix() * myRegistry->Get<Transform>(myParentID)->GetMatrix(aCacheMatrixImmmediate);
	}

	return GetLocalMatrix(aCacheMatrixImmmediate);
}

drach::Matrix4x4f drach::Transform::GetLocalMatrix(const bool aCacheMatrixImmmediate)
{
	if (aCacheMatrixImmmediate)
		CacheTransform();

	return myCachedLocalMatrix;
}

void drach::Transform::CacheTransform()
{

	myCachedLocalMatrix = Matrix4x4f::TRS(position, rotation, size);
}
