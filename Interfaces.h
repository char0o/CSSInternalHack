#pragma once
#include "util.h"
#include "EntityList.h"
#include "Engine.h"
#include "IVDebugOverlay.h"



class Interfaces
{
public:
	IVDebugOverlay* debugOverlay;
	Engine* engine;
	EntityList* entityList;
	Interfaces()
	{
		debugOverlay = find_interface<IVDebugOverlay*>("engine.dll", "VDebugOverlay003");
		entityList = find_interface<EntityList*>("client.dll", "VClientEntityList003");
		engine = find_interface<Engine*>("engine.dll", "VEngineClient013");
	}
	~Interfaces();

};