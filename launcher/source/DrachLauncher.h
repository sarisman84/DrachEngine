#pragma once
#include "resource.h"
#include "../../vendor/source/interfaces/EditorInterface.h"
#include "../../vendor/source/interfaces/EngineInterface.h"

typedef EngineInterface* (*EngineAPI)();
typedef EditorInterface* (*EditorAPI)();