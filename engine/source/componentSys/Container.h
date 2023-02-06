#pragma once
#include "BaseContainer.h"

#include "util/other/SMap.h"
#include "Entity.h"
#include "util/other/MethodCheck.h"

DEFINE_METHOD_CHECK(Start);
DEFINE_METHOD_CHECK(Update);

namespace drach
{
	namespace ecs
	{
		template<typename ComponentType>
		class Container : BaseContainer
		{
		public:
			static unsigned long id;

			Container() : container(), BaseContainer(GenerateID(id)) {}
			~Container() {
				for (auto& [entity, component] : container)
				{//free all components
					delete component;
				}
			}

			ComponentType* Get(const Entity anEntity) {
				if (!container.contains(anEntity))
					return nullptr;
				return &container[anEntity];
			}

			ComponentType& Add(const Entity anEntity) {
				//NOTE: not accounting for duplicates
				container.insert(anEntity, ComponentType());
				return container[anEntity];
			}

			void Remove(const Entity anEntity) override {
				container.erase(anEntity);
			}

			//Container Start Callback (will only call the start method if it actually exists)
			void Start(InitializeContext& someInitContext) override
			{
				//If the componentType actually contains a method of a return signature void and a single parameter InitializeContext: 
				//assume it is a start method.
				if constexpr (Has_Start<ComponentType, void(InitializeContext)>::value)
				{
					for (auto& [id, data] : container)
					{
						data.Start(someInitContext);
					}
				}
			}
			//Container Update Callback (will only call the update method if it actually exists)
			void Update(RuntimeContext& someRuntimeContext) override
			{
				if constexpr (Has_Update < ComponentType, void(RuntimeContext) > ::value)
				{
					for (auto& [id, data] : container)
					{
						data.Update(someRuntimeContext);
					}
				}
			}


		private:
			//NOTE: use an Sparse Set, if the quick clearing of all elements will ever be required
			SMap<Entity, ComponentType> container;



		};


		template<typename ComponentType>
		unsigned long Container<ComponentType>::id = 0;
	}
}
