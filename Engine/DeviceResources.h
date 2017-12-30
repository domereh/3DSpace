#pragma once

#include <Windows.h>
#include <d3d11_1.h>

class DeviceResources {
public:
	HRESULT InitDevice(HWND g_hWnd);	// Create Direct3D device and swap chain
	void CleanupDevice();				// Clean up the objects we've created
	void Present();
	ID3D11DeviceContext* GetDeviceContext();
	ID3D11Device* GetDevice();
	D3D_DRIVER_TYPE* GetDriver();
	ID3D11RenderTargetView * GetTargetView() { return g_pRenderTargetView; };
public:
	static constexpr int WIDHT = 800;
	static constexpr int HEIGHT = 600;
	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           g_pd3dDevice = nullptr;
	ID3D11Device1*          g_pd3dDevice1 = nullptr;
	ID3D11DeviceContext*    g_pImmediateContext = nullptr;
	ID3D11DeviceContext1*   g_pImmediateContext1 = nullptr;
	IDXGISwapChain*         g_pSwapChain = nullptr;
	IDXGISwapChain1*        g_pSwapChain1 = nullptr;
	ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
};
