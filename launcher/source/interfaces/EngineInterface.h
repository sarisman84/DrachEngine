#pragma once


class EngineInterface 
{
public:
	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
};