 #include "GameWindow.h"
/*
HRESULT GameWindow::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GameWindow::StaticWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0; // LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = (LPCSTR)L"TutorialWindowClass";
	wcex.hIconSm = 0; // LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	g_hInst = hInstance;
	RECT rc = { 0, 0, DeviceResources::WIDHT, DeviceResources::HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow((LPCSTR)L"TutorialWindowClass", (LPCSTR)L"Direct3D 11 Tutorial 1: Direct3D 11 Basics",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!g_hWnd)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}
*/

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------


LRESULT GameWindow::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);
		EndPaint(g_hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		// Note that this tutorial does not handle resizing (WM_SIZE) requests,
		// so we created the window without the resize border.

		// ************ KEYBOARD MESSAGES ************ //
	case WM_KEYDOWN:
		if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled()) // no thank you on the autorepeat
		{
			kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	case WM_KEYUP:
		kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		kbd.OnChar(static_cast<unsigned char>(wParam));
		break;
		// ************ END KEYBOARD MESSAGES ************ //

	default:
		return DefWindowProc(g_hWnd, message, wParam, lParam);
	}

	return 0;
}


HRESULT GameWindow::Run(DeviceResources * deviceResources, Renderer * renderer)
{
	HRESULT hr = S_OK;

	if (!IsWindowVisible(g_hWnd))
		ShowWindow(g_hWnd, SW_SHOW);

	// The render loop is controlled here.
	bool bGotMsg;
	MSG  msg;
	msg.message = WM_NULL;
	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		// Process window events.
		// Use PeekMessage() so we can use idle time to render the scene. 
		bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);

		if (bGotMsg)
		{
			// Translate and dispatch the message
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

			renderer->Render();			// Render frames during idle time (when no messages are waiting).

			UpdateModel(renderer);
			ComposeFrame(renderer);

			deviceResources->Present();	// Present the frame to the screen.
		}
	}

	return hr;
}

void GameWindow::UpdateModel(Renderer* renderer)
{
	if (kbd.KeyIsPressed('D')) {
		rotationY += 0.001;
	}
	if (kbd.KeyIsPressed('A')) {
		rotationY -= 0.001;
	}
	if (kbd.KeyIsPressed('W')) {
		rotationX += 0.001;
	}
	if (kbd.KeyIsPressed('S')) {
		rotationX -= 0.001;
	}
	renderer->SpinCube(rotationX, rotationY);

	if (kbd.KeyIsPressed('I')) {
		howFar -= 0.001;
	}
	if (kbd.KeyIsPressed('K')) {
		howFar += 0.001;
	}

}

void GameWindow::ComposeFrame(Renderer* renderer)
{
	renderer->DrawCube(howFar);
}
