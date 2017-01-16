//************************************************************************//
//	D3DClass.h
//	2016-11-07
//	revisited 2016-11-25
//	Irene Gersenowies
//************************************************************************//

#ifndef __Direct3DCLASS_H__
#define __Direct3DCLASS_H__

//=======================================================================//
//	   �����N
//=======================================================================//
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

//=======================================================================//
//	�N���X��		CDirect3D
//=======================================================================//
class CDirect3D
{
public:
	CDirect3D(void);
	CDirect3D(const CDirect3D& other);
	~CDirect3D(void);

	bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear);
	void Shutdown(void);

	void BeginScene(float red, float green, float blue, float alpha);
	void EndScene(void);

	ID3D11Device* GetDevice(void);
	ID3D11DeviceContext* GetDeviceContext(void);

	void GetProjectionMatrix(XMMATRIX& projectionMatrix);
	void GetWorldMatrix(XMMATRIX& worldMatrix);
	void GetOrthoMatrix(XMMATRIX& orthoMatrix);

	void GetVideoCardInfo(char* cardName, int& memory);

	void TurnZBufferOn(void);
	void TurnZBufferOff(void);

	void TurnOnAlphaBlending(void);
	void TurnOffAlphaBlending(void);

	ID3D11DepthStencilView* GetDepthStencilView(void);
	void SetBackBufferRenderTarget(void);
	void ResetViewport(void);

private:
	bool m_vsync_enabled;

	int m_videoCardMemory;
	char m_videoCardDescription[128];

	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;

	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;

	D3D11_VIEWPORT m_viewport;

	ID3D11DepthStencilState* m_depthDisabledStencilState;
	ID3D11BlendState* m_alphaEnableBlendingState;
	ID3D11BlendState* m_alphaDisableBlendingState;
};


#endif // ! __D3DCLASS_H__

//******************************************************************************
//	End of file.
//******************************************************************************

