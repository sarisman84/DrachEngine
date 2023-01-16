#include "BaseContainer.h"
#include "logging/Logger.h"


unsigned long BaseContainer::GenerateID(unsigned long& id) {
#if _DEBUG
	if (id != 0) {
		LOG("Generated second container");//ERROR: this is not supposed to EVER happen
		return id;
	}
#endif

	static unsigned long generatorID = 1;
	id = generatorID++;
	return id;
}