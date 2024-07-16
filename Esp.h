#pragma once
#include "CBaseEntity.h"
#include "Interfaces.h"
#include "d3d.h"
#include <string>
#include <sstream>


class ESP
{
public:
	ESP()
	{

	};
	ESP(Interfaces* interfaces, LPDIRECT3DDEVICE9 p_pDevice)
	{
		I = interfaces;
		p_pDevice = p_pDevice;
		localPlayer = reinterpret_cast<CBaseEntity*>(I->entityList->GetClientEntity(I->engine->GetLocalPlayer()));
	}
	CBaseEntity* localPlayer;
	Interfaces* I;
	void Draw(LPDIRECT3DDEVICE9 p_pDevice)
	{
		for (int i = 1; i < 64; i++)
		{
			CBaseEntity* player = reinterpret_cast<CBaseEntity*>(I->entityList->GetClientEntity(i));
			if (!player)
				continue;
			if (!player->IsPlayer())
				continue;
			if (player == localPlayer)
				continue;
			if (player->GetTeam() == localPlayer->GetTeam())
				continue;
			if (!player->IsAlive())
				continue;
			if (player->IsDormant())
				continue;
			Vector pos(0, 0, 0);
			Vector pPos = player->GetPos();
			if (!I->engine->WorldToScreen(player->GetPos(), pos))
				continue;		
			d3dHelper::DrawOutlineRect(p_pDevice, pos.x - 20, pos.y - 150, 40, 80, D3DCOLOR_ARGB(125, 255, 255, 255));
			//I->debugOverlay->AddBoxOverlay(player->GetPos(), Vector(-20, -20, 0), Vector(20, 20, 60), QAngle(0, 0, 0), 200, 0, 0, 5, 0.1);
		}
	}
};