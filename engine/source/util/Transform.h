#pragma once
#include "math/Vector3.h"
#include "math/Matrix4x4.h"
#include "componentSys/Entity.h"
#include <vector>

FORWARD_DECLARE_REG


namespace drach
{
	class Transform
	{
	public:
		Transform();
		Transform(const Transform& aTransform);
		Transform operator=(const Transform& aTransform);
		Transform(ecs::Registry* const aRegistry, ecs::Entity anEntityID);
		~Transform();

		

		void AddChild(const ecs::Entity anEntity);
		inline std::vector<ecs::Entity>& GetChildren()
		{
			return myChildElementIDs;

		}
		Matrix4x4f GetMatrix(const bool aCacheMatrixImmmediate = false);
		Matrix4x4f GetLocalMatrix(const bool aCacheMatrixImmmediate = false);
		

	public:
		void CacheTransform();

	public:
		Vector3f position;
		Vector3f rotation;
		Vector3f size;

	private:
		Matrix4x4f myCachedLocalMatrix;
		std::vector<ecs::Entity> myChildElementIDs;
		ecs::Entity myParentID;
		ecs::Entity myEntityID;
		ecs::Registry* myRegistry;

	};
}