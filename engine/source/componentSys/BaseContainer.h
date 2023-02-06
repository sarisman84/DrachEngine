#pragma once
#include "Entity.h"

namespace drach
{
	struct InitializeContext;
	struct RuntimeContext;

	namespace ecs
	{
		class BaseContainer
		{
		public:
			unsigned long id;
			BaseContainer(unsigned long id) : id(id) {}

			static unsigned long GenerateID(unsigned long& id);


			virtual void Remove(const Entity entity) = 0;
			virtual void Start(InitializeContext& someInitContext) = 0;
			virtual void Update(RuntimeContext& someRuntimeContext) = 0;
		};
	}
}
