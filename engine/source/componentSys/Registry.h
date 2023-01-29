#pragma once
#include <unordered_map>
#include <cassert>
#include <iostream>

#include "Entity.h"
#include "Container.h"

class Registry {
public:
	Registry();
	~Registry();

//-------------- COMPONENT MANAGEMENT -------------------
	template<typename ComponentType>
	ComponentType* Get(const Entity anEntity) const {
		Container<ComponentType>* container = GetContainer<ComponentType>();
		if (container)
			return container->Get(anEntity);
		return nullptr;
	}

	template<typename ComponentType>
	ComponentType& Add(const Entity anEntity) {
		Container<ComponentType>* container = GetContainer<ComponentType>();
		if (!container) {
			container = new Container<ComponentType>();//create new container
			containers[container->id] = (BaseContainer*)container;
		}
		return container->Add(anEntity);
	}

	template<typename ComponentType>
	void Remove(const Entity anEntity) {
		Container<ComponentType>* container = GetContainer<ComponentType>();
		if (container)
			container->Remove(anEntity);
	}


	template<typename ComponentType>
	Container<ComponentType>* GetContainer() const {
		if (!containers.contains(Container<ComponentType>::id))//there is no container of that type
			return nullptr;
		return (Container<ComponentType>*)containers.at(Container<ComponentType>::id);
	}



//----------------- ENTITY MANAGEMENT ------------------
	Entity CreateEntity() const;
	void DestroyEntity(const Entity anEntity);


private:
	std::unordered_map<unsigned long, BaseContainer*> containers;
};