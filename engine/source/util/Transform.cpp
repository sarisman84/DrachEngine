#include "precompile-header/coreIncludes.h"
#include "Transform.h"
#include "componentSys/Registry.h"
#include "logging/Logger.h"




drach::Transform::Transform(entt::registry* const aRegistry, entt::entity anEntityID)
	:myRegistry(aRegistry), myEntity(anEntityID)
{
}

drach::Transform::~Transform() = default;

drach::Transform::Transform() = default;

drach::Transform::Transform(const Transform& aTransform)
{
	myCachedLocalMatrix = aTransform.myCachedLocalMatrix;
	myChildElements = aTransform.myChildElements;
	myEntity = aTransform.myEntity;
	myParent = aTransform.myParent;
	myRegistry = aTransform.myRegistry;
	position = aTransform.position;
	rotation = aTransform.rotation;
	size = aTransform.size;
}

drach::Transform::Transform(Transform&& aTransform)
{
	myCachedLocalMatrix = aTransform.myCachedLocalMatrix;
	myChildElements = aTransform.myChildElements;
	myEntity = aTransform.myEntity;
	myParent = aTransform.myParent;
	myRegistry = aTransform.myRegistry;
	position = aTransform.position;
	rotation = aTransform.rotation;
	size = aTransform.size;

	delete& aTransform;
}

drach::Transform& drach::Transform::operator=(const Transform& aTransform)
{

	myCachedLocalMatrix = aTransform.myCachedLocalMatrix;
	myChildElements = aTransform.myChildElements;
	myEntity = aTransform.myEntity;
	myParent = aTransform.myParent;
	myRegistry = aTransform.myRegistry;
	position = aTransform.position;
	rotation = aTransform.rotation;
	size = aTransform.size;
	return *this;
}

drach::Transform& drach::Transform::operator=(Transform&& aTransform)
{
	myCachedLocalMatrix = aTransform.myCachedLocalMatrix;
	myChildElements = aTransform.myChildElements;
	myEntity = aTransform.myEntity;
	myParent = aTransform.myParent;
	myRegistry = aTransform.myRegistry;
	position = aTransform.position;
	rotation = aTransform.rotation;
	size = aTransform.size;

	delete& aTransform;

	return *this;
}



void drach::Transform::AddChild(const entt::entity anEntity)
{
	if (!myRegistry)
	{
		LOG_ERROR("Tried to add a child to an invalid transform!");
		return;
	}
	if (myRegistry->any_of<Transform>(anEntity))
	{
		myChildElements.push_back(anEntity);
		myRegistry->get<Transform>(anEntity).myParent = myEntity;
		return;
	}
	LOG_ERROR("Entity " + std::to_string(static_cast<uint32_t>(anEntity)) + " does not contain a transform!");
}

drach::Matrix4x4f drach::Transform::GetMatrix(const bool aCacheMatrixImmmediate)
{

	if (myParent != entt::entity(-1))
	{
		return GetLocalMatrix() * myRegistry->get<Transform>(myParent).GetMatrix(aCacheMatrixImmmediate);
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
