#pragma once
#include "util.h"
#include "Vector.h"
struct player_info_t
{
	char name[32];
};
class Engine
{
public:
	bool GetPlayerInfo(int index, player_info_t* info)
	{
		typedef bool(__thiscall* GetPlayerInfoFn)(void*, int, player_info_t*);
		return CallFunc<GetPlayerInfoFn>(this, 8)(this, index, info);
	}
	int GetLocalPlayer()
	{
		typedef int(__thiscall* GetLocalPlayerFn)(void*);
		return CallFunc<GetLocalPlayerFn>(this, 12)(this);
	}
	Matrix& WorldToScreenMatrix()
	{
		return find_vfunc < Matrix & (__thiscall*)(void*)>(this, 36)(this);
	}
	bool WorldToScreen(Vector& vOrigin, Vector& vScreen)
	{
		int width = 1360;
		int h = 768;

		Matrix worldToScreen = WorldToScreenMatrix();
		float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3];
		vScreen.z = 0;
		if (w > 0.01f)
		{
			float inverseW = 1 / w;
			vScreen.x = (width / 2) + (0.5 * ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * inverseW) * width + 0.5);
			vScreen.y = (h / 2) - (0.5 * ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * inverseW) * h + 0.5);
			return true;
		}
		return false;
	}
};

