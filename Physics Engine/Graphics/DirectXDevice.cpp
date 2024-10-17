#include "DirectXDevice.h"

#include <stdexcept>

//================================================================================================================
// Constructor / Destructor
// 
// - Creates DirectX, a Swap Chain (front / back-buffer - can extend to triple buffer) attach to given Window
//	 a Depth Buffer of Matching Size and Manager Classes for DirectX Resources such as Shaders and Textures.
//================================================================================================================
DirectXDevice::DirectXDevice(HWND window)
{
	HRESULT hr = S_OK; // Allows checking for failures when creating DirecrX Components (Factory, SwapChain, Backbuffer, etc.)

	// Get Window Size
	RECT rect;
	if (!GetClientRect(window, &rect))
		throw std::runtime_error("Error: Querying Window Size");
	
	mBackBufferWidth = rect.right - rect.left;
	mBackBufferHeight = rect.bottom - rect.top;

	// Create DXGI Factory - Allows Query of Graphics Hardware / Monitors before Initialising DirectX
	CComPtr<IDXGIFactory4> dxgiFactory;
	hr = CreateDXGIFactory2(0, __uuidof(IDXGIFactory4), (void**)(&dxgiFactory));


	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	// Flag adds Support fpr Surfaces with a Colour-Channel Ordering Different
	// from API default.

	UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(DEBUG) || defined(_DEBUG)
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Create Direct3D 11 API Device Object and Corresponding Context
	HRESULT hr = D3D11CreateDevice(
		nullptr,					// Specify nullptr to use Default Adapter
		D3D_DRIVER_TYPE_HARDWARE,	// Create Device using Hardware Graphics Driver
		0,							// Should be 0 unless driver is D3D_DRIIVER_TYPE_SOFTWARE
		deviceFlags,				// Set Debug Comptiblity Flags
		levels,						// List of Feature Levels Supported
		ARRAYSIZE(levels),			// Size of Above List
		D3D11_SDK_VERSION,			// Always set to D3D11_SDK_Version for Windows Store Apps
		&mD3DDevice,				// Returns Direct3D Device Create
		nullptr,					// Returns Feature Level of Device Created
		&mD3DContext				// Returns Device Immediate Context
	);

	if (FAILED(hr)) // Handles Device Interface Creation Failure
	{
		throw std::runtime_error("Error: Creating Direct3D Device and Context");
	}


	//====================================================================================
	// Create Swap Chain
	//====================================================================================
	// Create Swap-Chain (Back buffer / Front Buffer to Render to)
	// Set up for the window passed to this constructor
	//
	// Extention:
	// - Add Triple buffer for Post-Process Effects (Full Screen)
	// - WIll allow for Full Screen Effects (Bloom, COlour Grading, Motion Blur, etc.)
	//====================================================================================

	DXGI_SWAP_CHAIN_DESC1 scDesc = {};
	ZeroMemory(&scDesc, sizeof(DXGI_SWAP_CHAIN_DESC1));
	scDesc.Width = mBackBufferWidth;
	scDesc.Height = mBackBufferHeight;
	scDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.BufferCount = 2;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scDesc.SampleDesc.Count = 1;
	hr = dxgiFactory->CreateSwapChainForHwnd(mD3DDevice, window, &scDesc, nullptr, nullptr, &mSwapChain);

	// Get Back Buffer Texture from Swap Chain created - Needed for Next Step
	hr = mSwapChain->GetBuffer(0, __uuidof(mBackBufferTexture), (LPVOID*)&mBackBufferTexture);
	if (FAILED(hr))
		throw std::runtime_error("Error: Creating Swap Chain");

	//==============================================================================================
	// Create Render Target View
	//==============================================================================================
	// Create a "Render Target View" of the Back Buffer - We need this to Render to the Back Buffer
	//==============================================================================================

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	hr = mD3DDevice->CreateRenderTargetView(mBackBufferTexture, &rtvDesc, &mBackBufferRenderTarget);
	if (FAILED(hr))
		throw std::runtime_error("Error: Creaing Render Target View");

	//=============================================================
	// Create Depth Buffer
	//=============================================================
	// Create Depth Buffer to go along with Back Buffer
	// - First Create a Texture to Hold the Depth Buffer Values
	//=============================================================


}

// DirectX CleanUp
DirectXDevice::~DirectXDevice()
{
	if (mD3DContext)
		mD3DContext->ClearState();
}