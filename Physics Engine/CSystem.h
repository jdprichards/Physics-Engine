#ifndef _CSYSTEM_H_INCLUDED_
#define _CSYSTEM_H_INCLUDED_

#include <windows.h>


class CSystem
{
public:
	CSystem();
	CSystem(const CSystem&);
	~CSystem();

	bool Initilize();
	bool ShutDown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	
private:
	bool Frame();
	void InitializeWindows();
	void ShutdownWindows();

private:
	LPCWSTR mApplicationName;
	HINSTANCE mHInstance;
	HWND mHWnd;

	//CInput* mInput;
	//CApplication* mApplication


};

// Global Variables and Forward Declared Functions

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//void UpdateWindowTitle(HWND hWnd, float frameTime);

bool gMouseControl = false;


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

#endif // !_CSYSTEM_H_INCLUDED_