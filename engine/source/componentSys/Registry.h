#pragma once
#include <unordered_map>
#include <cassert>
#include <iostream>

#include "Entity.h"
#include "Container.h"

namespace drach
{
	struct InitializeContext;
	struct RuntimeContext;

	

	namespace ecs
	{
		class Registry
		{
		public:
			Registry();
			~Registry();

			//-------------- COMPONENT MANAGEMENT -------------------

			//Fetches an entity from a specific component type
			template<typename ComponentType>
			ComponentType* Get(const Entity anEntity) const {
				Container<ComponentType>* container = GetContainer<ComponentType>();
				if (container)
					return container->Get(anEntity);
				return nullptr;
			}

			//Adds an entity to a specific component type
			template<typename ComponentType>
			ComponentType& Add(const Entity anEntity) {
				Container<ComponentType>* container = GetContainer<ComponentType>();
				if (!container)
				{
					container = new Container<ComponentType>();//create new container
					containers[container->id] = (BaseContainer*)container;
				}
				return container->Add(anEntity);
			}

			//Removes an entity from a specific component type
			template<typename ComponentType>
			void Remove(const Entity anEntity) {
				Container<ComponentType>* container = GetContainer<ComponentType>();
				if (container)
					container->Remove(anEntity);
			}

			//Fetches the container of a specific component type
			template<typename ComponentType>
			Container<ComponentType>* GetContainer() const {
				if (!containers.contains(Container<ComponentType>::id))//there is no container of that type
					return nullptr;
				return (Container<ComponentType>*)containers.at(Container<ComponentType>::id);
			}

			//Checks if an entity exists in a specific component type
			template<typename ComponentType>
			const bool Contains(const Entity anEntity) const
			{
				Container<ComponentType>* container = GetContainer<ComponentType>();
				if (!container) return false; //If the container type doesnt exist, return false

				ComponentType* type = container->Get(anEntity);

				if (!type) return false; //If the container does not contain said entity, return false

				return true; //otherwise, return true
			}



			//----------------- ENTITY MANAGEMENT ------------------
		
			//Creates a new entity
			Entity CreateEntity() const;
			//Destroys an entity
			void DestroyEntity(const Entity anEntity);

			//----------------- METHOD CALLS -----------------------
		
		
			//Attemps to call a Start method call should any datatypes contain said Start method
			void Start(InitializeContext& const someInitContext);
			//Attempts to call an Update method call should any datatypes contain said Update method
			void Update(RuntimeContext& const someUpdateContext);

		private:
			std::unordered_map<unsigned long, BaseContainer*> containers;
		};
	}
}
