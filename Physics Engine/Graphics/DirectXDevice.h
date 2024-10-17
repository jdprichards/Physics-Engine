//==============================================================================================
// DirectXDevice.h : Class Encapsulating DirectX Methods and Varaibles
// Handles DirectX Setup / Shutdown and provides Manager Classes to work with DirectX objects
//==============================================================================================

#ifndef _DIRECTX_DEVICE_H_
#define _DIRECTX_DEVICE_H_

#define NOMINMAX // Use NOMINMAX to stop Microsoft Headers from Defining "min" and "max" which break some other Libraries

#include <d3d11.h>
#include <dxgi1_4.h>
#include <atlbase.h> // For CComPtr

#include <memory>

class DirectXDevice
{
public:
	//================================================================================================================
	// Constructor / Destructor
	// 
	// - Creates DirectX, a Swap Chain (front / back-buffer - can extend to triple buffer) attach to given Window
	// a Depth Buffer of Matching Size and Manager Classes for DirectX Resources such as Shaders and Textures.
	//================================================================================================================
	DirectXDevice(HWND window);

	// DirectX CleanUp
	~DirectXDevice();
	
public:
	//==============
	// Data Access
	//==============s

	ID3D11Device* Device() { return mD3DDevice; }
	ID3D11DeviceContext* Context() { return mD3DContext; }

private:
	//================
	// Private Data
	//================

	// Current Viewport Dimensions (Not Supporting "render scale"  Will be Size of Window and BackBuffer)
	int mBackBufferHeight;
	int mBackBufferWidth;

	// Main DirectX (D3D) Variables
	CComPtr<ID3D11Device> mD3DDevice;
	CComPtr<ID3D11DeviceContext> mD3DContext;

	// Back Buffer (Where we render to) and Swap chain (Handles how Back Buffer is presented to Screen)
	CComPtr<ID3D11Texture2D> mBackBufferTexture;
	CComPtr<ID3D11RenderTargetView> mBackBufferRenderTarget;
	CComPtr<IDXGISwapChain1> mSwapChain;
};

#endif // !_DIRECTX_DEVICE_H_
