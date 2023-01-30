#include "Registry.h"
#include "Container.h"
namespace drach
{
	namespace ecs
	{
		Registry::Registry() : containers() {}

		Registry::~Registry() {
			for (int i = (int)containers.size() - 1; i >= 0; i--)
			{
				delete containers[i];
			}
		}


		Entity Registry::CreateEntity() const {
			static unsigned long generationID = 0;
			return generationID++;
		}

		void Registry::DestroyEntity(const Entity anEntity) {//destroys all components coupled to this entity
			for (auto& [id, container] : containers)
			{
				container->Remove(anEntity);
			}
		}
	}
}
