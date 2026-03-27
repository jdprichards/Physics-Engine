//=============================================================
// Physics Engine.cpp : The Entry Point for the application
//=============================================================

#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>

#include <string>
#include <memory>

#include "Matrix4x4.h"

#include "CSystem.h"



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
	
	CSystem* System;
	bool result;

	// Create System
	System = new CSystem;

	// Initlaise System
	result = System->Initialize();
	if (result)
		System->Run();

	// Shutdown System and release System object
	System->Shutdown();
	delete System;
	System = 0;

	// Output any memory leaks to Visual Studio after app ends
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG | _CRTDBG_LEAK_CHECK_DF));


	return 0;
}