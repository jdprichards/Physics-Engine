//=============================================================
// Physics Engine.cpp : The Entry Point for the application
//=============================================================


#include <windows.h>
#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>

#include <string>
#include <memory>

#include "../Maths/Matrix4x4.h"

// Global Variables and Forward Declared Functions

void GetDesktopResolution(int& horizontal, int& vertical);
HWND InitWindow(HINSTANCE hInstance, int nCmdShow, int windowWidth, int windowHeight);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//void UpdateWindowTitle(HWND hWnd, float frameTime);

bool gMouseControl = false;

// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}


//========================================
// Entry Function for Windows Application
//========================================

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	[[maybe_unused]] _In_opt_ HINSTANCE hPrevInstance,
	[[maybe_unused]] _In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	int windowWidth;
	int windowHeight;

	GetDesktopResolution(windowWidth, windowHeight);

	HWND hWnd = InitWindow(hInstance, nCmdShow, windowWidth, windowHeight);

	if (hWnd == NULL)
	{
		MessageBoxA(hWnd, "Failure Creating Window", NULL, MB_OK);
		return 0;
	}

	MSG msg = {};



	while (msg.message != WM_QUIT) // As long as window is open loop
	{
		// Check for and deal with window messages (INPUT, WINDOW RESIZING, MINIMISING, etc.)
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// Deel with messages
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Whe no messages are left to procees then render and update scene
		else
		{
			// Update and Present Scene
		}
	}

	// Output any memory leaks to Visual Studio after app ends
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG | _CRTDBG_LEAK_CHECK_DF));


	return (int)msg.wParam;
}

//====================================
// Create Window to Display Scene
// - Returns false on failure
//====================================
HWND InitWindow(HINSTANCE hInstance, int nCmdShow, int windowWidth, int windowHeight)
{
	SHSTOCKICONINFO stockIcon;
	stockIcon.cbSize = sizeof(stockIcon);

	if (SHGetStockIconInfo(SIID_APPLICATION, SHGSI_ICON, &stockIcon) != S_OK)
		return NULL;

	// Register Window Class. Defines various UI featrues of the window for the engine
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc; // Function to deal with Window Messages
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0; SIID_APPLICATION;
	wcex.hInstance = hInstance;
	wcex.hIcon = stockIcon.hIcon; // Which Icon to use for the Window
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // What Cursor to Use
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"Physics Engine";
	wcex.hIconSm = stockIcon.hIcon;

	if (!RegisterClassEx(&wcex))
		return NULL;

	// Select Type of Window to Start in
	DWORD windowStyle = (WS_OVERLAPPEDWINDOW | !WS_THICKFRAME | WS_MAXIMIZE); // Standard Window
	
	// Calculate Overall Dimensions of the Window. Will Render inside of the Window
	// Overall Window will be Larger (Boarders, Title Bar, Etc.)
	RECT rc = { 0,0, windowWidth, windowHeight };
	AdjustWindowRect(&rc, windowStyle, FALSE);

	// Create Window, Second Parameter is the Text in the Title Bar
	HWND hWnd = CreateWindow(
		L"Physics Engine", L"Physics Engine", windowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
		nullptr, nullptr, hInstance, nullptr);
	
	if (hWnd != NULL)
	{
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
	}
	
	return hWnd;
}

//==========================================================================
// Deal with Messages from Windows
// There are Many Possible Messages, such as Keyboard or Mouse Inputs, 
// Resizing or Minimising Windows, etc.
// Only deal with Messages we're intrested in - Add as Project Evolves
//==========================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT: // Message to ensure Window Content is Dispalyed
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY: // A Message to deal with Window Closing
	{
		PostQuitMessage(0);
		break;
	}

	// The WM_KEYXXXX Messages Report Key Input to our Window
	// ADD WHEN INPUT.H/CPP IS WRITTEN
	
	// Using Raw Input for Mouse Movement so we can still get Mouse Movement even after after Mouse Cursor hits Edge of Screen
	// ADD WHEN INPUT.H/CPP IS WRITTEN

	// Any Messages NOT Handled are Passed back to Windows Default Handling
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}