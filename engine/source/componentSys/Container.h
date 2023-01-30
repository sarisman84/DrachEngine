#pragma once
#include "BaseContainer.h"

#include "util/other/SMap.h"
#include "Entity.h"

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

		private:
			//NOTE: use an Sparse Set, if the quick clearing of all elements will ever be required
			SMap<Entity, ComponentType> container;
		};


		template<typename ComponentType>
		unsigned long Container<ComponentType>::id = 0;
	}
}
