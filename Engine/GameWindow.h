#pragma once

#include "DeviceResources.h"
#include "Renderer.h"
#include "Keyboard.h"

template <class DERIVED_TYPE>
class BaseWindow
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		DERIVED_TYPE *pThis = NULL;

		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->g_hWnd = hwnd;
		}
		else
		{
			pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}
		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	BaseWindow() : g_hWnd(NULL) { }

	BOOL Create(
		HINSTANCE hInstance,
		int nCmdShow,
		PCWSTR lpWindowName,
		DWORD dwStyle,
		DWORD dwExStyle = 0,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		HWND hWndParent = 0,
		HMENU hMenu = 0
	)
	{
		// Register the window class.
		WNDCLASSEX wcex;

		wcex.lpfnWndProc = DERIVED_TYPE::WindowProc;
		wcex.hInstance = hInstance;
		wcex.lpszClassName = (LPCSTR) ClassName();
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hIcon = 0; // LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.hIconSm = 0; // LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
		RegisterClassEx(&wcex);

		// Create window
		g_hInst = hInstance;

		RECT rc = { 0, 0, DeviceResources::WIDHT, DeviceResources::HEIGHT };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);


		g_hWnd = CreateWindow((LPCSTR) ClassName(), (LPCSTR)L"Direct3D 11 Tutorial 1: Direct3D 11 Basics", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, this
		);


		return (g_hWnd ? TRUE : FALSE);
	}



	HWND Window() const { return g_hWnd; }

protected:

	virtual PCWSTR  ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	HWND		g_hWnd;
	HINSTANCE	g_hInst = nullptr;
};

class GameWindow : public BaseWindow<GameWindow> {
public:
//	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	PCWSTR  ClassName() const { return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
	HRESULT Run(DeviceResources* deviceResources, Renderer* renderer);
private:
	void UpdateModel(Renderer* renderer);
	void ComposeFrame(Renderer* renderer);
	/********************************/
	/*  User Functions              */
	/********************************/
public:
	Keyboard kbd;
	/********************************/
	/*  User Variables              */
	/********************************/
	float rotationX = 0;
	float rotationY = 0;
	float howFar = -15.0;
};
