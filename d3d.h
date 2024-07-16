#ifndef D3D_H
#define D3D_H

#include "d3d.h"
#include "d3dx9.h"
#include "trampolines.h"
#include <cstdarg>
#include "Interfaces.h"
class d3dHelper {
public:
    d3dHelper();
    bool getD3D9Device();
    // The vTable entries of the D3D9 dummy device
    char* d3d9DeviceTable[119];

    static void drawRectangle(LPDIRECT3DDEVICE9 p_pDevice, int x, int y, int h, int w, D3DCOLOR color);
    static void DrawOutlineRect(LPDIRECT3DDEVICE9 pDevice, float x, float y, float width, float height, D3DCOLOR color);
    static void APIENTRY endSceneHook(LPDIRECT3DDEVICE9 pDevice);

    // Helpers
private:
    static BOOL CALLBACK enumGetProcessWindow(HWND _hwnd, LPARAM lParam);
};

#endif