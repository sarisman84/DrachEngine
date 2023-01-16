#pragma once
#include <vector>
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
	ComponentType* Add(const Entity anEntity) {
		Container<ComponentType>* container = GetContainer<ComponentType>();
		if (!container) {
			container = new Container<ComponentType>();//create new container
			containers.push_back((BaseContainer*)container);
		}
		return container->Add(anEntity);
	}

	template<typename ComponentType>
	Container<ComponentType>* GetContainer() const {
		//do an O(n) thing to find the correct container
		for (BaseContainer* container : containers) {//TODO: make this more efficient
			if (Container<ComponentType>::id == container->id)
				return (Container<ComponentType>*)container;
		}
		return nullptr;
	}



//----------------- ENTITY MANAGEMENT ------------------
	Entity CreateEntity() const;
	void DestroyEntity(const Entity anEntity);


private:
	std::vector<BaseContainer*> containers;
};