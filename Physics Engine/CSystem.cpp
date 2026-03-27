#include "CSystem.h"

bool CSystem::Initilize()
{

	
}

void CSystem::Initialize(int&, int&)
{
	// Initialize width and height of screen to zero before snedinf variables to function
	int windowWidth = 0;
	int windowHeight = 0;

	//GetDesktopResolution(windowWidth, windowHeight);

	// Initialize Windows API
	InitializeWindows(windowWidth, windowHeight);

	return true;
}
