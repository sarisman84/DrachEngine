#include "Registry.h"
#include "Container.h"

Registry::Registry() : containers() {}

Registry::~Registry() {
	for (int i = (int)containers.size() - 1; i >= 0; i--) {
		delete containers[i];
	}
}