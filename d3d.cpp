#include "d3d.h"
#include "d3dx9.h"
#include "Esp.h"
// Handle to the CS:GO window
HWND hwnd = nullptr;

LPDIRECT3DDEVICE9 d3dDevice = NULL;
struct Vertex
{
    float x, y, z, rhw;
    DWORD color;
};
#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
d3dHelper::d3dHelper() {
    EnumWindows(enumGetProcessWindow, GetCurrentProcessId());
    if (!hwnd) {
        MessageBox(0, L"[D3D] HWND Not Found", L":(", 0);
        return;
    }
    if (!this->getD3D9Device()) {
        MessageBox(0, L"[D3D] D3D9 Device Error", L":(", 0);
        return;
    }
}

Interfaces* I;

ESP esp;
bool messaged = false;
void APIENTRY d3dHelper::endSceneHook(LPDIRECT3DDEVICE9 p_pDevice) {
    p_pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);
    if (!d3dDevice) {
        d3dDevice = p_pDevice;
    }
    if (!I) {
        I = new Interfaces();
        esp = ESP(I, p_pDevice);
	}
    if (!messaged) {
        std::stringstream ss;
        ss << std::hex << I->engine;
		MessageBoxA(0, ss.str().c_str(), ":)", 0);
		messaged = true;
	}
    esp.Draw(p_pDevice);
     
    Matrix m = I->engine->WorldToScreenMatrix();
    d3dHelper::DrawOutlineRect(p_pDevice, 20, 20, 40, 40, D3DCOLOR_ARGB(125, 255, 255, 255));
    //d3dHelper::drawRectangle(p_pDevice, 100, 100, 100, 100, D3DCOLOR_ARGB(255, 255, 0, 0));

    //p_pDevice->Clear(1, &r, D3DCLEAR_TARGET, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255), 0);

    //OnlyFont->DrawTextA(NULL, buffer, -1, &DummyRectangle, DT_LEFT | DT_NOCLIP, D3DXCOLOR(255, 0, 0, 255));
    //OnlyFont->Release();
    // call original function using the trampoline

    trampEndScene(d3dDevice);
}   
void d3dHelper::drawRectangle(LPDIRECT3DDEVICE9 p_pDevice, int x, int y, int h, int w, D3DCOLOR color) {
	D3DRECT rect = { x, y, x + w, y + h };
	p_pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}
void d3dHelper::DrawOutlineRect(LPDIRECT3DDEVICE9 pDevice, float x, float y, float width, float height, D3DCOLOR color)
{
    // Define vertices for the rectangle (clockwise order)
    Vertex vertices[] =
    {
        { (float)x, (float)y, 0.0f, 1.0f, color },
        { (float)x + (float)width, (float)y, 0.0f, 1.0f, color },
        { (float)x + (float)width, y + (float)height, 0.0f, 1.0f, color },
        { (float)x, (float)y + (float)height, 0.0f, 1.0f, color },
        { (float)x, (float)y, 0.0f, 1.0f, (float)color } // Closing the loop
    };
    pDevice->SetVertexShader(NULL);
    pDevice->SetPixelShader(NULL);
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    pDevice->SetTexture(0, NULL);
    pDevice->SetFVF(D3DFVF_VERTEX);
    pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, vertices, sizeof(Vertex));
    //pDevice->Present(0, 0, 0, 0);

}
// https://guidedhacking.com/threads/get-direct3d9-and-direct3d11-devices-dummy-device-method.11867/
// create the dummy d3d device and copy the object contents in order to obtain the 
// addresses of function that are about to be hooked
bool d3dHelper::getD3D9Device()
{

    if (!hwnd || !this->d3d9DeviceTable) {
        return false;
    }

    IDirect3D9* d3dSys = Direct3DCreate9(D3D_SDK_VERSION);

    if (!d3dSys) {
        return false;
    }

    IDirect3DDevice9* dummyDev = NULL;

    // options to create dummy device
    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.Windowed = false;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hwnd;

    HRESULT dummyDeviceCreated = d3dSys->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &dummyDev);

    if (dummyDeviceCreated != S_OK)
    {
        // may fail in windowed fullscreen mode, trying again with windowed mode
        d3dpp.Windowed = !d3dpp.Windowed;

        dummyDeviceCreated = d3dSys->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &dummyDev);

        if (dummyDeviceCreated != S_OK)
        {
            d3dSys->Release();
            return false;
        }
    }

    memcpy(this->d3d9DeviceTable, *reinterpret_cast<void***>(dummyDev), sizeof(this->d3d9DeviceTable));
    
    dummyDev->Release();
    d3dSys->Release();
    return true;
}

// https://stackoverflow.com/questions/11711417/get-hwnd-by-process-id-c
// https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms633498(v=vs.85)
// "To continue enumeration, the callback function must return TRUE; to stop enumeration, it must return FALSE."
BOOL CALLBACK d3dHelper::enumGetProcessWindow(HWND _hwnd, LPARAM lParam)
{
    DWORD lpdwProcessId;
    GetWindowThreadProcessId(_hwnd, &lpdwProcessId);
    if (lpdwProcessId == lParam)
    {
        hwnd = _hwnd;
        return FALSE;
    }

    return TRUE;
}