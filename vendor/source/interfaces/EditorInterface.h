#pragma once
#include "InterfaceContext.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
class Engine;


struct EditorContext : public StartContext
{
	ID3D11Device* myDevice;
	ID3D11DeviceContext* myContext;
};

struct EditorRuntimeContext : public RuntimeContext
{
	Engine& myEngineIns;
};

class EditorInterface
{
public:
	virtual void OnStart(EditorContext& someContext) = 0;
	virtual void OnUpdate(EditorRuntimeContext& aRuntimeContext) = 0;
};

