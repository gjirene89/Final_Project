//************************************************************************//
//	D3DClass.cpp
//	2016-11-07
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
#include "D3DClass.h"

//==============================================================================
//  �֐���        CDirect3D	
//  ����          CDirect3D�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CDirect3D::CDirect3D()
{
	//�ϐ��̏�����
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
//  �֐���        CDirect3D	
//  ����          CDirect3D�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          CDirect3D& other			CDirect3D�̃C���X�^���X
//	�߂�l
//          �Ȃ�
//==============================================================================
CDirect3D::CDirect3D(const CDirect3D& other)
{
	//��
}

//==============================================================================
//  �֐���        �`CDirect3D	
//  ����          CDirect3D�N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CDirect3D::~CDirect3D()
{
	//��
}

//==============================================================================
//  �֐���		 Initialize	
//  ����			 �O���t�B�b�N�����֐�
//------------------------------------------------------------------------------
//	����
//          int     screenWidth        ��ʂ̕�
//          int     screenHeight       ��ʂ̍���
//          bool    vsync              true ���j�^�[�̃��t���b�V�����[�g�ɍ��킹�ĉ�ʂ��X�V����
//                                     false �ł��邾��������ʂ��X�V����
//          HWND    hwnd               �E�C���h�E�n���h��
//          bool    fullscreen         true �S��ʕ\��         false  �E�C���h�E�\��
//          float   screenDepth        �N���b�s���O�̉����Ƃ���
//          float   screenNear         �N���b�s���O�̋߂��Ƃ���
//	�߂�l
//			bool	true �����@�@�@false ���s
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

	//vsync�ݒ�
	m_vsync_enabled = vsync;

	//�O���t�B�b�N �C���^�t�F�[�X �t�@�N�g�����쐬
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))
	{
		return false;
	}

	//�O���t�B�b�N �C���^�t�F�[�X �A�_�v�^�[���쐬
	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
	{
		return false;
	}

	//�A�E�g�v�b�g�i���j�^�[�j�ɔԍ�ID��t����
	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
	{
		return false;
	}

	//DXGI_FORMAT_R8G8B8A8_UNORM �̕\���`�������擾����
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result))
	{
		return false;
	}

	//�\���`���ƃ��j�^�[�̑g�ݍ��킹���擾����
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		return false;
	}

	//�\���`�������X�g��
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))
	{
		return false;
	}

	//�w�肳�ꂽ��ʃT�C�Y�ɂ�郊�t���b�V�����[�g���擾����
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

	//�r�f�I�J�[�h�̏ڍׂ��擾
	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		return false;
	}

	//�r�f�I�J�[�h���������擾�iMB�P�ʁj
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	//�r�f�I�J�[�h�����擾
	error = wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128);
	if (error != 0)
	{
		return false;
	}

	//�\�����X�g�����
	delete[] displayModeList;
	displayModeList = 0;

	//�A�_�v�^�A�E�g�v�b�g�����
	adapterOutput->Release();
	adapterOutput = 0;

	//�A�_�v�^�����
	adapter->Release();
	adapter = 0;

	//�t�@�N�g�������
	factory->Release();
	factory = 0;


	//�X���b�v�`�F�C���̏�����
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//�o�b�N�o�b�t�@�̃��t���b�V�����[�g���Z�b�g
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

	//DirectX11�ɃZ�b�g
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	//�X���b�v�`�F�C���ADirect3D�f�o�C�X�@�Ɓ@Direct3D�f�o�C�X�R���e�L�X�g�@�쐬
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

	//�o�b�t�@�����
	backBufferPtr->Release();
	backBufferPtr = 0;

	//�[�x�o�b�t�@������
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	//�[�x�o�b�t�@�̐ݒ�
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

	//�[�x�o�b�t�@�쐬
	result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//�X�e���V���X�e�[�g�̏������i�R�c�p�j
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	//�X�e���V���X�e�[�g�ݒ�
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

	//�X�e���V���X�e�[�g�쐬
	result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if (FAILED(result))
	{
		return false;
	}

	//�f�o�C�X�R���e�L�X�g�ɃZ�b�g����
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	//�f�v�g�@�X�e���V���@�r���[������
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	//�f�v�g�@�X�e���V���@�r���[�ݒ�
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	//�f�v�g�@�X�e���V���@�r���[�쐬
	result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
	if (FAILED(result))
	{
		return false;
	}

	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	//���X�^�[�X�e�[�g�ݒ�
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

	//���X�^�[�X�e�[�g�쐬
	result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if (FAILED(result))
	{
		return false;
	}

	//���X�^�X�e�[�g���Z�b�g
	m_deviceContext->RSSetState(m_rasterState);

	//�r���[�|�[�g��ݒ肷��
	m_viewport.Width = (float)screenWidth;
	m_viewport.Height = (float)screenHeight;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;

	//�r���[�|�[�g�쐬
	m_deviceContext->RSSetViewports(1, &m_viewport);

	//�v���W�F�N�V�����}�g���N�X�ݒ�
	fieldOfView = (float)XM_PI / 4.0f;
	screenAspect = (float)screenWidth / (float)screenHeight;

	//�v���W�F�N�V�����}�g���N�X�쐬
	m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);

	//���[���h�}�g���N�X��P�ʃ}�g���N�X�ɂ���
	m_worldMatrix = XMMatrixIdentity();

	//�����e�}�g���N�X���쐬
	m_orthoMatrix = XMMatrixOrthographicLH((float)screenWidth, (float)screenHeight, screenNear, screenDepth);

	//�f�v�g�X�e���V���X�e�[�g�̏������i�Q�c�p�j
	ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));

	//�f�v�g�X�e���V���X�e�[�g�̐ݒ�
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

	//�f�v�g�X�e���V���X�e�[�g�̍쐬
	result = m_device->CreateDepthStencilState(&depthDisabledStencilDesc, &m_depthDisabledStencilState);
	if (FAILED(result))
	{
		return false;
	}

	//�u�����h�X�e�[�g������
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));

	//�u�����h�X�e�[�g�ݒ�i�A���t�@�u�����h�j
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

	//�u�����h�X�e�[�g�쐬
	result = m_device->CreateBlendState(&blendStateDescription, &m_alphaEnableBlendingState);
	if (FAILED(result))
	{
		return false;
	}

	//�u�����h�X�e�[�g�ݒ�i�A���t�@�u�����h�s�j
	blendStateDescription.RenderTarget[0].BlendEnable = FALSE;

	//�u�����h�X�e�[�g�쐬
	result = m_device->CreateBlendState(&blendStateDescription, &m_alphaDisableBlendingState);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

//==============================================================================
//  �֐���		 Shutdown	
//  ����			 Direct3D�I�u�W�F�N�g�̉��
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
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
//  �֐���		 BeginScene	
//  ����			 �`��J�n�̏����𐮂���֐�
//------------------------------------------------------------------------------
//	����	
//          �o�b�t�@�̐F
//          float      red              ��
//          float      green            ��
//          float      blue				��
//          float      alpha            �A���t�@
//	�߂�l
//          �Ȃ�
//==============================================================================
void CDirect3D::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4];

	//�o�b�t�@�[�̐F��ݒ肷��
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	//�o�b�N�o�b�t�@���N���A����
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

	//�[�x�o�b�t�@���N���A����
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	return;
}

//==============================================================================
//  �֐���		 EndScene	
//  ����			 �`��I���̏����𐮂���֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CDirect3D::EndScene()
{
	//�o�b�N�o�b�t�@����ʂɏo��
	if (m_vsync_enabled)
	{
		//���t���b�V�����[�g�����b�N����
		m_swapChain->Present(1, 0);
	}
	else
	{
		//�ł��邾�������X�V����
		m_swapChain->Present(0, 0);
	}

	return;
}

//==============================================================================
//  �֐���		 GetDevice	
//  ����			 Device3D��߂��֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          ID3D11Device*    device�ւ̃|�C���^
//==============================================================================
ID3D11Device* CDirect3D::GetDevice()
{
	return m_device;
}

//==============================================================================
//  �֐���		 GetDeviceContext	
//  ����			 Device3D�R���e�L�X�g��߂��֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          ID3D11DeviceContext*    deviceContext�ւ̃|�C���^
//==============================================================================
ID3D11DeviceContext* CDirect3D::GetDeviceContext()
{
	return m_deviceContext;
}

//==============================================================================
//  �֐���		 GetProjectionMatrix	
//  ����			 �v���W�F�N�V�����}�g���N�X��߂��֐�
//------------------------------------------------------------------------------
//	����
//          XMMATRIX&      �v���W�F�N�V�����}�g���N�X�ւ̃|�C���^
//	�߂�l
//          �Ȃ�
//==============================================================================
void CDirect3D::GetProjectionMatrix(XMMATRIX& projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;

	return;
}

//==============================================================================
//  �֐���		 GetWorldMatrix	
//  ����			 ���[���h�}�g���N�X��߂��֐�
//------------------------------------------------------------------------------
//	����
//          XMMATRIX&     ���[���h�}�g���N�X�ւ̃|�C���^
//	�߂�l
//          �Ȃ�
//==============================================================================
void CDirect3D::GetWorldMatrix(XMMATRIX& worldMatrix)
{
	worldMatrix = m_worldMatrix;

	return;
}

//==============================================================================
//  �֐���		 GetOrthoMatrix	
//  ����			 �����e�}�g���N�X��߂��֐�
//------------------------------------------------------------------------------
//	����
//          XMMATRIX&     �����e�}�g���N�X�ւ̃|�C���^
//	�߂�l
//          �Ȃ�
//==============================================================================
void CDirect3D::GetOrthoMatrix(XMMATRIX& orthoMatrix)
{
	orthoMatrix = m_orthoMatrix;

	return;
}

//==============================================================================
//  �֐���		 GetVideoCardInfo	
//  ����			 �r�f�I�J�[�h�̏���߂��֐�
//------------------------------------------------------------------------------
//	����
//          char*   cardName        �J�[�h��
//          int&    memory          �������� (�l�a)
//	�߂�l
//          �Ȃ�
//==============================================================================
void CDirect3D::GetVideoCardInfo(char* cardName, int& memory)
{
	strcpy_s(cardName, 128, m_videoCardDescription);
	memory = m_videoCardMemory;
	return;
}

//==============================================================================
//  �֐���		 TurnZBufferOn	
//  ����			 Z�o�b�t�@��ON�ɂ���֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CDirect3D::TurnZBufferOn()
{
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	return;
}

//==============================================================================
//  �֐���		 TurnZBufferOn	
//  ����			 Z�o�b�t�@��OFF�ɂ���֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CDirect3D::TurnZBufferOff()
{
	m_deviceContext->OMSetDepthStencilState(m_depthDisabledStencilState, 1);
	
	return;
}

//==============================================================================
//  �֐���		 TurnOnAlphaBlending	
//  ����			 �A���t�@�u�����h��ON�ɂ���
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CDirect3D::TurnOnAlphaBlending()
{
	float blendFactor[4];

	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	//�A���t�@�u�����h��ON�ɂ���
	m_deviceContext->OMSetBlendState(m_alphaEnableBlendingState, blendFactor, 0xffffffff);
	return;
}

//==============================================================================
//  �֐���		 TurnOffAlphaBlending	
//  ����			 �A���t�@�u�����h��OFF�ɂ���
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CDirect3D::TurnOffAlphaBlending()
{
	float blendFactor[4];

	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	//�A���t�@�u�����h��OFF�ɂ���
	m_deviceContext->OMSetBlendState(m_alphaDisableBlendingState, blendFactor, 0xffffffff);
	return;
}

//==============================================================================
//  �֐���		 GetDepthStencilView	
//  ����			 �f�v�X�@�X�e���V���@�r���[��߂��֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          ID3D11DepthStencilView��      �f�v�X�X�@�e���V���@�r���[�ւ̃|�C���^
//==============================================================================
ID3D11DepthStencilView* CDirect3D::GetDepthStencilView()
{
	return m_depthStencilView;
}

//==============================================================================
//  �֐���		 SetBackBufferRenderTarget	
//  ����			 �o�b�N�o�b�t�@�ɕ`�悷��ݒ���s���֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CDirect3D::SetBackBufferRenderTarget()
{
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	return;
}

//==============================================================================
//  �֐���		 ResetViewport	
//  ����			 �r���[�|�[�g�����Z�b�g����
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CDirect3D::ResetViewport()
{
	m_deviceContext->RSSetViewports(1, &m_viewport);

	return;
}

//******************************************************************************
//	End of file.
//******************************************************************************