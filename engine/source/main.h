#pragma once
#include "interface/EngineInterface.h"


class Engine : public EngineInterface
{
public:
	// Inherited via EngineInterface
	virtual void OnStart() override;
	virtual void OnUpdate() override;
};



