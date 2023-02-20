#pragma once
#include "math/Vector3.h"
#include "math/Matrix4x4.h"
#include "entt/single_include/entt/entt.hpp"
#include <vector>
#include <string>

namespace drach
{
	class Transform
	{
	public:
		Transform();
		Transform(const Transform& aTransform);
		Transform(Transform&& aTransform);

		Transform& operator=(const Transform& aTransform);
		Transform& operator=(Transform&& aTransform);


		Transform(entt::registry* const aRegistry, entt::entity anEntityID);
		~Transform();



		void AddChild(const entt::entity anEntity);
		inline std::vector<entt::entity>& GetChildren()
		{
			return myChildElements;

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
		std::vector<entt::entity> myChildElements;
		entt::entity myParent = entt::entity(-1);
		entt::entity myEntity = entt::entity(-1);
		entt::registry* myRegistry;

	};
}