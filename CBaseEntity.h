#pragma once
#include "Engine.h"
#include "util.h"
#include "Vector.h"
class CBaseEntity
{
public:
	bool IsLocalPlayer(int index, Engine& engine)
	{
		return index == engine.GetLocalPlayer();
	}
	bool SetupBones(Matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
	{
		using FuncType = bool(__thiscall*)(void*, Matrix3x4*, int, int, float);
		FuncType func = reinterpret_cast<FuncType*>(*(uintptr_t*)this + 0x4)[13];
		return func(this, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}
	int AliveStatus()
	{
		return getFirstByte(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 0x90));
	}
	bool IsAlive()
	{
		return AliveStatus() == 0;
	}
	int GetTeam()
	{
		return *reinterpret_cast<int*>(reinterpret_cast<int>(this) + 0x9C);
	}
	bool IsDormant()
	{
		return *reinterpret_cast<int*>(reinterpret_cast<int>(this) + 0x80) == -65536;
	}
	bool IsPlayer()
	{
		return find_vfunc<bool(__thiscall*)(void*)>(this, 131)(this);
	}
	Vector& GetPos()
	{
		float x = *reinterpret_cast<float*>(reinterpret_cast<int>(this) + 0x260);
		float y = *reinterpret_cast<float*>(reinterpret_cast<int>(this) + 0x264);
		float z = *reinterpret_cast<float*>(reinterpret_cast<int>(this) + 0x268);
		return Vector(x, y, z);
	}
	int GetHealth()
	{
		return find_vfunc<int(__thiscall*)(void*)>(this, 106)(this);
	}
	int getFirstByte(unsigned int value) {
		return (value >> 24) & 0xFF; // Extract the first byte as an int
	}
};