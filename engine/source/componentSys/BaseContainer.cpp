#include "BaseContainer.h"

static unsigned long generatorID = 1;
unsigned long BaseContainer::GenerateID() {
	return generatorID++;
}