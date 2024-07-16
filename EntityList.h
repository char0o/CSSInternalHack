#pragma once
#include "util.h"
#include "CBaseEntity.h"
class EntityList
{
public:
	void* GetClientEntity(int index)
	{
		typedef void* (__thiscall* GetClientEntityFn)(void*, int);
		return CallFunc<GetClientEntityFn>(this, 3)(this, index);
	}

};