#pragma once
#include "math/Vector2.h"
#include "math/Matrix4x4.h"
#include "componentSys/Entity.h"
#include <vector>

FORWARD_DECLARE_REG


namespace drach
{
	class RectTransform
	{

	public:
		RectTransform();
		RectTransform(ecs::Registry* const aRegistry, ecs::Entity anEntityID);
		RectTransform(const RectTransform& aTransform);
		RectTransform operator=(const RectTransform& aTransform);
		~RectTransform();
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
		PixelCoord position;
		PixelCoord size;
		float rotation;

	private:
		Matrix4x4f myCachedLocalMatrix;
		std::vector<ecs::Entity> myChildElementIDs;
		ecs::Entity myParentID;
		ecs::Entity myEntityID;
		ecs::Registry* myRegistry;

	};

};
