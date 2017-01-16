//************************************************************************//
//	D3DClass.cpp
//	2016-11-07
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		インクルード
//=======================================================================//
#include "D3DClass.h"

//==============================================================================
//  関数名        CDirect3D	
//  説明          CDirect3Dクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CDirect3D::CDirect3D()
{
	//変数の初期化
	m_swapChain = 0;
	m_device = 0;
	m_deviceContext = 0;
	m_renderTargetView = 0;
	m_depthStencilBuffer = 0;
	m_depthStencilState = 0;
	m_depthStencilView = 0;
	m_rasterState = 0;
	m_depthDisabledStencilState = 0;
	m_alphaEnableBlendingState = 0;
	m_alphaDisableBlendingState = 0;
}

//==============================================================================
//  関数名        CDirect3D	
//  説明          CDirect3Dクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          CDirect3D& other			CDirect3Dのインスタンス
//	戻り値
//          なし
//==============================================================================
CDirect3D::CDirect3D(const CDirect3D& other)
{
	//空
}

//==============================================================================
//  関数名        ～CDirect3D	
//  説明          CDirect3Dクラスのデストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CDirect3D::~CDirect3D()
{
	//空
}

//==============================================================================
//  関数名		 Initialize	
//  説明			 グラフィック初期関数
//------------------------------------------------------------------------------
//	引数
//          int     screenWidth        画面の幅
//          int     screenHeight       画面の高さ
//          bool    vsync              true モニターのリフレッシュレートに合わせて画面を更新する
//                                     false できるだけ速く画面を更新する
//          HWND    hwnd               ウインドウハンドル
//          bool    fullscreen         true 全画面表示         false  ウインドウ表示
//          float   screenDepth        クリッピングの遠いところ
//          float   screenNear         クリッピングの近いところ
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CDirect3D::Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes, i, numerator, denominator;
	size_t stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Texture2D* backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	float fieldOfView, screenAspect;
	D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
	D3D11_BLEND_DESC blendStateDescription;

	//vsync設定
	m_vsync_enabled = vsync;

	//グラフィック インタフェース ファクトリを作成
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))
	{
		return false;
	}

	//グラフィック インタフェース アダプターを作成
	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
	{
		return false;
	}

	//アウトプット（モニター）に番号IDを付ける
	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
	{
		return false;
	}

	//DXGI_FORMAT_R8G8B8A8_UNORM の表示形式数を取得する
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result))
	{
		return false;
	}

	//表示形式とモニターの組み合わせを取得する
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		return false;
	}

	//表示形式をリスト化
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))
	{
		return false;
	}

	//指定された画面サイズによるリフレッシュレートを取得する
	numerator = 0;
	denominator = 1;

	for (i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)screenWidth)
		{
			if (displayModeList[i].Height == (unsigned int)screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}

		}
	}

	//ビデオカードの詳細を取得
	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		return false;
	}

	//ビデオカードメモリを取得（MB単位）
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	//ビデオカード名を取得
	error = wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128);
	if (error != 0)
	{
		return false;
	}

	//表示リストを解放
	delete[] displayModeList;
	displayModeList = 0;

	//アダプタアウトプットを解放
	adapterOutput->Release();
	adapterOutput = 0;

	//アダプタを解放
	adapter->Release();
	adapter = 0;

	//ファクトリを解放
	factory->Release();
	factory = 0;


	//スワップチェインの初期化
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//バックバッファのリフレッシュレートをセット
	if (m_vsync_enabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	if (fullscreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	//DirectX11にセット
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	//スワップチェイン、Direct3Dデバイス　と　Direct3Dデバイスコンテキスト　作成
	result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1,
		D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, nullptr, &m_deviceContext);
	if (FAILED(result))
	{
		return false;
	}

	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
	if (FAILED(result))
	{
		return false;
	}

	result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
	if (FAILED(result))
	{
		return false;
	}

	//バッファを解放
	backBufferPtr->Release();
	backBufferPtr = 0;

	//深度バッファ初期化
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	//深度バッファの設定
	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	//深度バッファ作成
	result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//ステンシルステートの初期化（３Ｄ用）
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	//ステンシルステート設定
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//ステンシルステート作成
	result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if (FAILED(result))
	{
		return false;
	}

	//デバイスコンテキストにセットする
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	//デプト　ステンシル　ビュー初期化
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	//デプト　ステンシル　ビュー設定
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	//デプト　ステンシル　ビュー作成
	result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
	if (FAILED(result))
	{
		return false;
	}

	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	//ラスターステート設定
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	//ラスターステート作成
	result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if (FAILED(result))
	{
		return false;
	}

	//ラスタステートをセット
	m_deviceContext->RSSetState(m_rasterState);

	//ビューポートを設定する
	m_viewport.Width = (float)screenWidth;
	m_viewport.Height = (float)screenHeight;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;

	//ビューポート作成
	m_deviceContext->RSSetViewports(1, &m_viewport);

	//プロジェクションマトリクス設定
	fieldOfView = (float)XM_PI / 4.0f;
	screenAspect = (float)screenWidth / (float)screenHeight;

	//プロジェクションマトリクス作成
	m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);

	//ワールドマトリクスを単位マトリクスにする
	m_worldMatrix = XMMatrixIdentity();

	//正投影マトリクスを作成
	m_orthoMatrix = XMMatrixOrthographicLH((float)screenWidth, (float)screenHeight, screenNear, screenDepth);

	//デプトステンシルステートの初期化（２Ｄ用）
	ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));

	//デプトステンシルステートの設定
	depthDisabledStencilDesc.DepthEnable = false;
	depthDisabledStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDisabledStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthDisabledStencilDesc.StencilEnable = true;
	depthDisabledStencilDesc.StencilReadMask = 0xFF;
	depthDisabledStencilDesc.StencilWriteMask = 0xFF;
	depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthDisabledStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthDisabledStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//デプトステンシルステートの作成
	result = m_device->CreateDepthStencilState(&depthDisabledStencilDesc, &m_depthDisabledStencilState);
	if (FAILED(result))
	{
		return false;
	}

	//ブレンドステート初期化
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));

	//ブレンドステート設定（アルファブレンド可）
	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	//blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	//blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	//ブレンドステート作成
	result = m_device->CreateBlendState(&blendStateDescription, &m_alphaEnableBlendingState);
	if (FAILED(result))
	{
		return false;
	}

	//ブレンドステート設定（アルファブレンド不可）
	blendStateDescription.RenderTarget[0].BlendEnable = FALSE;

	//ブレンドステート作成
	result = m_device->CreateBlendState(&blendStateDescription, &m_alphaDisableBlendingState);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

//==============================================================================
//  関数名		 Shutdown	
//  説明			 Direct3Dオブジェクトの解放
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CDirect3D::Shutdown()
{
	if (m_swapChain)
	{
		m_swapChain->SetFullscreenState(false, nullptr);
	}

	if (m_alphaEnableBlendingState)
	{
		m_alphaEnableBlendingState->Release();
		m_alphaEnableBlendingState = 0;
	}

	if (m_alphaDisableBlendingState)
	{
		m_alphaDisableBlendingState->Release();
		m_alphaDisableBlendingState = 0;
	}

	if (m_rasterState)
	{
		m_rasterState->Release();
		m_rasterState = 0;
	}

	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = 0;
	}

	if (m_depthDisabledStencilState)
	{
		m_depthDisabledStencilState->Release();
		m_depthDisabledStencilState = 0;
	}

	if (m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = 0;		
	}

	if (m_depthStencilBuffer)
	{
		m_depthStencilBuffer->Release();
		m_depthStencilBuffer = 0;
	}

	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = 0;
	}

	if (m_deviceContext) 
	{
		m_deviceContext->Release();
		m_deviceContext = 0;
	}

	if (m_device)
	{
		m_device->Release();
		m_device = 0;
	}

	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = 0;
	}

	return;
}

//==============================================================================
//  関数名		 BeginScene	
//  説明			 描画開始の準備を整える関数
//------------------------------------------------------------------------------
//	引数	
//          バッファの色
//          float      red              赤
//          float      green            緑
//          float      blue				青
//          float      alpha            アルファ
//	戻り値
//          なし
//==============================================================================
void CDirect3D::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4];

	//バッファーの色を設定する
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	//バックバッファをクリアする
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

	//深度バッファをクリアする
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	return;
}

//==============================================================================
//  関数名		 EndScene	
//  説明			 描画終了の準備を整える関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CDirect3D::EndScene()
{
	//バックバッファを画面に出す
	if (m_vsync_enabled)
	{
		//リフレッシュレートをロックする
		m_swapChain->Present(1, 0);
	}
	else
	{
		//できるだけ速く更新する
		m_swapChain->Present(0, 0);
	}

	return;
}

//==============================================================================
//  関数名		 GetDevice	
//  説明			 Device3Dを戻す関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          ID3D11Device*    deviceへのポインタ
//==============================================================================
ID3D11Device* CDirect3D::GetDevice()
{
	return m_device;
}

//==============================================================================
//  関数名		 GetDeviceContext	
//  説明			 Device3Dコンテキストを戻す関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          ID3D11DeviceContext*    deviceContextへのポインタ
//==============================================================================
ID3D11DeviceContext* CDirect3D::GetDeviceContext()
{
	return m_deviceContext;
}

//==============================================================================
//  関数名		 GetProjectionMatrix	
//  説明			 プロジェクションマトリクスを戻す関数
//------------------------------------------------------------------------------
//	引数
//          XMMATRIX&      プロジェクションマトリクスへのポインタ
//	戻り値
//          なし
//==============================================================================
void CDirect3D::GetProjectionMatrix(XMMATRIX& projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;

	return;
}

//==============================================================================
//  関数名		 GetWorldMatrix	
//  説明			 ワールドマトリクスを戻す関数
//------------------------------------------------------------------------------
//	引数
//          XMMATRIX&     ワールドマトリクスへのポインタ
//	戻り値
//          なし
//==============================================================================
void CDirect3D::GetWorldMatrix(XMMATRIX& worldMatrix)
{
	worldMatrix = m_worldMatrix;

	return;
}

//==============================================================================
//  関数名		 GetOrthoMatrix	
//  説明			 正投影マトリクスを戻す関数
//------------------------------------------------------------------------------
//	引数
//          XMMATRIX&     正投影マトリクスへのポインタ
//	戻り値
//          なし
//==============================================================================
void CDirect3D::GetOrthoMatrix(XMMATRIX& orthoMatrix)
{
	orthoMatrix = m_orthoMatrix;

	return;
}

//==============================================================================
//  関数名		 GetVideoCardInfo	
//  説明			 ビデオカードの情報を戻す関数
//------------------------------------------------------------------------------
//	引数
//          char*   cardName        カード名
//          int&    memory          メモリ量 (ＭＢ)
//	戻り値
//          なし
//==============================================================================
void CDirect3D::GetVideoCardInfo(char* cardName, int& memory)
{
	strcpy_s(cardName, 128, m_videoCardDescription);
	memory = m_videoCardMemory;
	return;
}

//==============================================================================
//  関数名		 TurnZBufferOn	
//  説明			 ZバッファをONにする関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CDirect3D::TurnZBufferOn()
{
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	return;
}

//==============================================================================
//  関数名		 TurnZBufferOn	
//  説明			 ZバッファをOFFにする関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CDirect3D::TurnZBufferOff()
{
	m_deviceContext->OMSetDepthStencilState(m_depthDisabledStencilState, 1);
	
	return;
}

//==============================================================================
//  関数名		 TurnOnAlphaBlending	
//  説明			 アルファブレンドをONにする
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CDirect3D::TurnOnAlphaBlending()
{
	float blendFactor[4];

	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	//アルファブレンドをONにする
	m_deviceContext->OMSetBlendState(m_alphaEnableBlendingState, blendFactor, 0xffffffff);
	return;
}

//==============================================================================
//  関数名		 TurnOffAlphaBlending	
//  説明			 アルファブレンドをOFFにする
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CDirect3D::TurnOffAlphaBlending()
{
	float blendFactor[4];

	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	//アルファブレンドをOFFにする
	m_deviceContext->OMSetBlendState(m_alphaDisableBlendingState, blendFactor, 0xffffffff);
	return;
}

//==============================================================================
//  関数名		 GetDepthStencilView	
//  説明			 デプス　ステンシル　ビューを戻す関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          ID3D11DepthStencilView＊      デプスス　テンシル　ビューへのポインタ
//==============================================================================
ID3D11DepthStencilView* CDirect3D::GetDepthStencilView()
{
	return m_depthStencilView;
}

//==============================================================================
//  関数名		 SetBackBufferRenderTarget	
//  説明			 バックバッファに描画する設定を行う関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CDirect3D::SetBackBufferRenderTarget()
{
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	return;
}

//==============================================================================
//  関数名		 ResetViewport	
//  説明			 ビューポートをリセットする
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CDirect3D::ResetViewport()
{
	m_deviceContext->RSSetViewports(1, &m_viewport);

	return;
}

//******************************************************************************
//	End of file.
//******************************************************************************