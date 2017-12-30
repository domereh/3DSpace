#pragma once

#include <d3d11_1.h>
#include <directxcolors.h>
#include <d3dcompiler.h>

#include "DeviceResources.h"

using namespace DirectX;


class Renderer {
public:
	Renderer::Renderer(DeviceResources* deviceResources);
	//--------------------------------------------------------------------------------------
	// Render the frame
	//--------------------------------------------------------------------------------------
	void Render();
	void CreateDeviceDependentResources();
	void SpinCube(float rotationX, float rotationY);
	void DrawCube(float howFar);
private:
	HRESULT CreateShaders();
	//--------------------------------------------------------------------------------------
	// Helper for compiling shaders with D3DCompile
	//
	// With VS 11, we could load up prebuilt .cso files instead...
	//--------------------------------------------------------------------------------------
	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	void CreateCube();
	//-----------------------------------------------------------------------------
	// Pointer to device resource manager
	//-----------------------------------------------------------------------------
	DeviceResources* m_deviceResources;
	//--------------------------------------------------------------------------------------
	// Structures
	//--------------------------------------------------------------------------------------
	struct SimpleVertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT4 Color;
	};
	struct ConstantBuffer
	{
		XMMATRIX mWorld;
		XMMATRIX mView;
		XMMATRIX mProjection;
	};
public:
	ID3D11VertexShader*     g_pVertexShader = nullptr;
	ID3D11PixelShader*      g_pPixelShader = nullptr;
	ID3D11InputLayout*      g_pVertexLayout = nullptr;
	ID3D11Buffer*           g_pVertexBuffer = nullptr;
	ID3D11Buffer*           g_pIndexBuffer = nullptr;
	ID3D11Buffer*           g_pConstantBuffer = nullptr;
	XMMATRIX                g_World;
	XMMATRIX                g_View;
	XMMATRIX                g_Projection;
};
