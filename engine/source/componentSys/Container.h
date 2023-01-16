#pragma once
#include "BaseContainer.h"

#include <unordered_map>
#include "Entity.h"

template<typename ComponentType>
class Container : BaseContainer {
public:
	static unsigned long id;

	Container() : container(), BaseContainer(GenerateID(id)) {}
	~Container() {
		for (auto& [entity, component] : container) {//free all components
			delete component;
		}
	}

	ComponentType* Get(const Entity anEntity) const {
		auto itr = container.find(anEntity);
		if (itr == container.end()) {//didnt find any
			return nullptr;
		}
		return itr->second;
		//return container[anEntity];
	}

	ComponentType* Add(const Entity anEntity) {
		//NOTE: not accounting for duplicates
		container[anEntity] = new ComponentType();
		return container[anEntity];
	}

	virtual void Remove (const Entity anEntity) override {
		if (!container.contains(anEntity))
			return;
		delete container[anEntity];//NOTE: not accounting for duplicates
		container.erase(anEntity);
	}

private:
	//TODO: use an Sparse Set
	std::unordered_map<Entity, ComponentType*> container;
};


template<typename ComponentType>
unsigned long Container<ComponentType>::id = 0;