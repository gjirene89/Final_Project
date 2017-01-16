//************************************************************************//
//	graphicsClass.cpp
//	2016-11-02
//	Irene Gersenowies
//************************************************************************//
#include "graphicsClass.h"

//==============================================================================
//  �֐���        CGraphics	
//  ����          CGraphics�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CGraphics::CGraphics()
{
	m_Direct3D = 0;
	m_Camera = 0;
	m_SunLight = 0;
	
	m_TextFps = 0;
	m_TextCPU = 0;
	
	//----------------------
	//    ���f��
	//----------------------

	m_Block = 0;
	//m_Sack = 0;
	m_Player = 0;
	m_Hook = 0;
	m_Wall = 0;

	m_ShaderManager = 0;

	m_RenderTexture = 0;
	m_BlackWhiteRenderTexture = 0;
	m_DownSampleTexture = 0;
	m_UpSampleTexture = 0;
	m_HorizontalBlurTexture = 0;
	m_VerticalBlurTexture = 0;
	m_SmallWindow = 0;
	m_FullScreenWindow = 0;
}

//==============================================================================
//  �֐���        CGraphics	
//  ����          CGraphics�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          CGraphics& other			CGraphics�̃C���X�^���X
//	�߂�l
//          �Ȃ�
//==============================================================================
CGraphics::CGraphics(const CGraphics& other)
{
	//��
}

//==============================================================================
//  �֐���        �`CGraphics	
//  ����          CGraphics�N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CGraphics::~CGraphics()
{
	//��
}

//==============================================================================
//  �֐���		 Initialize	
//  ����			 CGraphics�̏����֐�
//------------------------------------------------------------------------------
//	����
//			int     screenWidth     ��ʂ̕�
//          int     screenHeight    ��ʂ̍���
//          HWND    hwnd			�E�C���h�E �n���h��
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CGraphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	XMMATRIX baseViewMatrix;
	float downSampleWidth, downSampleHeight;

	//----------------------------
	//�@�@Direct3D�I�u�W�F�N�g����
	//----------------------------
	m_Direct3D = new CDirect3D;
	if (!m_Direct3D)
	{
		return false;
	}

	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//�@�@Camera�@�I�u�W�F�N�g�@����
	//----------------------------
	m_Camera = new CCamera;
	if (!m_Camera)
	{
		return false;
	}

	m_Camera->SetPosition(0.0f, 10.0f, -40.0f);
	m_Camera->RenderBaseViewMatrix();
	m_Camera->GetBaseViewMatrix(baseViewMatrix);

	//----------------------------
	//�@�@���C�g����
	//----------------------------
	m_SunLight = new CLight;
	if (!m_SunLight)
	{
		return false;
	}

	m_SunLight->SetAmbientColor(0.26f, 0.24f, 0.30f, 1.0f);
	m_SunLight->SetDiffuseColor(1.0f, 0.99f, 0.79f, 1.0f);
	m_SunLight->SetDirection(-0.25f, -1.0f, 0.5f);
	m_SunLight->SetPosition(500.0f, 500.0f, -50.0f);
	m_SunLight->SetLookAt(0.0f, 0.0f, 0.0f);
	m_SunLight->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_SunLight->SetSpecularPower(30.0f);
	m_SunLight->GenerateOrthoMatrix(20.0f, 20.0f, SHADOW_MAP_DEPTH, SHADOW_MAP_NEAR);
	
	//----------------------------
	//�@�@FPS������I�u�W�F�N�g�@����
	//----------------------------
	m_TextFps = new CText;
	if (!m_TextFps)
	{
		return false;
	}

	result = m_TextFps->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the FPS Text object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//�@�@CPU������I�u�W�F�N�g�@����
	//----------------------------
	m_TextCPU = new CText;
	if (!m_TextCPU)
	{
		return false;
	}

	result = m_TextCPU->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the CPU Text object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//�@�@�V�F�[�_�[�Ǘ��I�u�W�F�N�g����
	//----------------------------
	m_ShaderManager = new CShaderManager;
	if (!m_ShaderManager)
	{
		return false;
	}

	result = m_ShaderManager->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Shader Manager object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//�@�u���b�N���f������
	//----------------------------
	m_Block = new CModel;
	if (!m_Block)
	{
		return false;
	}
	
	result = m_Block->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Model/block.txt");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize block model.", L"Error", MB_OK);
		return false;
	}
	m_Block->SetPosition(-25.0f, -9.0f, 0.0f);
	m_Block->LoadColorMap(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Texture/blockColorB.tga");
	m_Block->LoadBumpMap(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Texture/blockNormal.tga");

	//----------------------------
	//�@�R�f�̃��f��
	//----------------------------
	
	m_Player = new CPlayer;
	if (!m_Player)
	{
		return false;
	}

	result = m_Player->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize player object.", L"Error", MB_OK);
		return false;
	}

	m_Player->SetPosition(0.0f, 0.0f, 0.0f);
	m_Player->SetRotation(0.0f, -40.0f, 0.0f);
	m_Player->LoadColorMap(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Texture/playerColorB.tga");
	m_Player->LoadBumpMap(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Texture/playerNormalB.tga");


	/*
	m_Sack = new CModel;
	if (!m_Sack)
	{
		return false;
	}

	result = m_Sack->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Model/sack.txt");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize sack model.", L"Error", MB_OK);
		return false;
	}
	m_Sack->SetPosition(0.0f, 0.0f, 0.0f);
	m_Sack->SetRotation(0.0f, -40.0f, 0.0f);
	m_Sack->LoadColorMap(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Texture/playerColorB.tga");
	m_Sack->LoadBumpMap(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Texture/playerNormalB.tga");
	*/

	//----------------------------
	//�@�t�b�N�̃��f��
	//----------------------------
	/*
	m_Hook = new CModel;
	if (!m_Hook)
	{
		return false;
	}

	result = m_Hook->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Model/hook.txt");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize hook model.", L"Error", MB_OK);
		return false;
	}
	m_Hook->LoadColorMap(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Texture/hookColor.tga");
	m_Hook->LoadBumpMap(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Texture/hookColor.tga");
	m_Hook->SetPosition(0.0f, 0.0f, 0.0f);
	m_Hook->SetRotation(0.0f, -40.0f, 0.0f);
	*/
	//----------------------------
	//�@	�ǂ̃��f��
	//----------------------------
	m_Wall = new CModel;
	if (!m_Wall)
	{
		return false;
	}

	result = m_Wall->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Model/wall.txt");
	m_Wall->LoadColorMap(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Texture/wallColor.tga",5,5);
	m_Wall->LoadBumpMap(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../20161206_ShaderTest/assets/Texture/wallNormal.tga", 5, 5);
	m_Wall->SetPosition(10.0f, 0.0f, 10.0f);
	
	//----------------------------
	//	�����_�[�p�̃e�N�X�`��
	//----------------------------
	m_RenderTexture = new CRenderTexture;
	if (!m_RenderTexture)
	{
		return false;
	}

	result = m_RenderTexture->Initialize(m_Direct3D->GetDevice(), SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT, SHADOW_MAP_DEPTH, SHADOW_MAP_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize render texture object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//	�����̉e	�p�̃e�N�X�`��
	//----------------------------

	m_BlackWhiteRenderTexture = new CRenderTexture;
	if (!m_BlackWhiteRenderTexture)
	{
		return false;
	}

	result = m_BlackWhiteRenderTexture->Initialize(m_Direct3D->GetDevice(), SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT, SHADOW_MAP_DEPTH, SHADOW_MAP_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize black and white texture object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//	�����̉�ʃT�C�Y�̃e�N�X�`�� (�ڂ����p�j
	//----------------------------
	downSampleWidth = SHADOW_MAP_WIDTH / 2.0f;
	downSampleHeight = SHADOW_MAP_HEIGHT / 2.0f;

	m_DownSampleTexture = new CRenderTexture;
	if (!m_DownSampleTexture)
	{
		return false;
	}

	result = m_DownSampleTexture->Initialize(m_Direct3D->GetDevice(), downSampleWidth, downSampleHeight, 100.0f, 1.0f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize down sample texture object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//	�����̉�ʃT�C�Y�̃E�C���h�E
	//----------------------------

	m_SmallWindow = new COrthoWindow;
	if (!m_SmallWindow)
	{
		return false;
	}

	result = m_SmallWindow->Initialize(m_Direct3D->GetDevice(), downSampleWidth, downSampleHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize ortho window object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//	�c�ڂ����p�̃e�N�X�`��
	//----------------------------

	m_VerticalBlurTexture = new CRenderTexture;
	if (!m_VerticalBlurTexture)
	{
		return false;
	}

	result = m_VerticalBlurTexture->Initialize(m_Direct3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, 0.1f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize vertical blur texture object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//	���ڂ����p�̃e�N�X�`��
	//----------------------------

	m_HorizontalBlurTexture = new CRenderTexture;
	if (!m_HorizontalBlurTexture)
	{
		return false;
	}

	result = m_HorizontalBlurTexture->Initialize(m_Direct3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, 0.1f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize horizontal blur texture object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//	��ʃT�C�Y�̃e�N�X�`�� (�ڂ����p�j
	//----------------------------
	m_UpSampleTexture = new CRenderTexture;
	if (!m_UpSampleTexture)
	{
		return false;
	}

	result = m_UpSampleTexture->Initialize(m_Direct3D->GetDevice(), SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT, SCREEN_DEPTH, 0.1f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize down sample texture object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//	�S��ʗp�̃e�N�X�`��
	//----------------------------

	m_FullScreenWindow = new COrthoWindow;
	if (!m_FullScreenWindow)
	{
		return false;
	}

	result = m_FullScreenWindow->Initialize(m_Direct3D->GetDevice(), SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize ortho window object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

//==============================================================================
//  �֐���		 Shutdown	
//  ����			 �O���t�B�b�N �I�u�W�F�N�g���������֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CGraphics::Shutdown()
{
	//----------------------------
	//�@�����e�E�C���h�E���
	//----------------------------
	if (m_SmallWindow)
	{
		m_SmallWindow->Shutdown();
		delete m_SmallWindow;
		m_SmallWindow = 0;
	}

	if (m_FullScreenWindow)
	{
		m_FullScreenWindow->Shutdown();
		delete m_FullScreenWindow;
		m_FullScreenWindow = 0;
	}

	//----------------------------
	//�@�e�N�X�`�����
	//----------------------------

	if (m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	if (m_BlackWhiteRenderTexture)
	{
		m_BlackWhiteRenderTexture->Shutdown();
		delete m_BlackWhiteRenderTexture;
		m_BlackWhiteRenderTexture = 0;
	}

	if (m_DownSampleTexture)
	{
		m_DownSampleTexture->Shutdown();
		delete m_DownSampleTexture;
		m_DownSampleTexture = 0;
	}

	if (m_UpSampleTexture)
	{
		m_UpSampleTexture->Shutdown();
		delete m_UpSampleTexture;
		m_UpSampleTexture = 0;
	}

	if (m_HorizontalBlurTexture)
	{
		m_HorizontalBlurTexture->Shutdown();
		delete m_HorizontalBlurTexture;
		m_HorizontalBlurTexture = 0;
	}

	if (m_VerticalBlurTexture)
	{
		m_VerticalBlurTexture->Shutdown();
		delete m_VerticalBlurTexture;
		m_VerticalBlurTexture = 0;
	}

	//----------------------------
	//�@���f�����
	//----------------------------

	if (m_Block)
	{
		m_Block->Shutdown();
		delete m_Block;
		m_Block = 0;
	}

	if (m_Player)
	{
		m_Player->Shutdown();
		delete m_Player;
		m_Player = 0;
	}

	if (m_Hook)
	{
		m_Hook->Shutdown();
		delete m_Hook;
		m_Hook = 0;
	}

	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	if (m_TextCPU)
	{
		m_TextCPU->Shutdown();
		delete m_TextCPU;
		m_TextCPU = 0;
	}
	
	if (m_TextFps)
	{
		m_TextFps->Shutdown();
		delete m_TextFps;
		m_TextFps = 0;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
}

//==============================================================================
//  �֐���		 Frame	
//  ����			 �O���t�B�b�N �I�u�W�F�N�g�̖��t���[���X�V�֐�
//------------------------------------------------------------------------------
//	����
//          int     FPS           �b���Ƃ̃t���[����
//          int     CPU           CPU���p��
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CGraphics::Frame(int FPS, int CPU, float posX, float posY, float posZ)
{
	bool result;
	
	m_Camera->SetPosition(posX, posY+10, posZ - 80.0f);
	m_Player->Frame(m_Direct3D->GetDeviceContext());
	result = m_TextFps->SetFps(FPS, m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_TextCPU->SetCpu(CPU, m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = RenderSceneToTexture();
	if (!result)
	{
		return false;
	}

	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}

//==============================================================================
//  �֐���		 Render	
//  ����			 �O���t�B�b�N �I�u�W�F�N�g�̕`��֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CGraphics::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	XMMATRIX lightViewMatrix, lightOrthoMatrix;
	bool result;
	float posX, posY, posZ;

	//�o�b�t�@���N���A����
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0);

	//�J�����̃}�g���b�N�X����
	m_Camera->Render();

	//�}�g���b�N�X���擾
	m_SunLight->GenerateViewMatrix();

	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	m_SunLight->GetViewMatrix(lightViewMatrix);
	m_SunLight->GetOrthoMatrix(lightOrthoMatrix);

	//----------------------------
	//�@2D �`��
	//----------------------------
	m_Direct3D->TurnZBufferOff();
	m_Direct3D->TurnOnAlphaBlending();

	result = m_TextFps->Render(m_Direct3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	result = m_TextCPU->Render(m_Direct3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	m_Direct3D->TurnOffAlphaBlending();
	m_Direct3D->TurnZBufferOn();

	//----------------------------
	//�@3D �`�� 
	//----------------------------

	//��
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Wall->GetPosition(posX, posY, posZ);
	worldMatrix *= XMMatrixTranslation(posX, posY, posZ);


	m_Wall->Render(m_Direct3D->GetDeviceContext());
	//result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Block->GetIndexCount(),
	//	worldMatrix, viewMatrix, projectionMatrix, m_Wall->GetColorTexture());

	result = m_ShaderManager->RenderClothShader(m_Direct3D->GetDeviceContext(), m_Wall->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_Wall->GetColorTexture(), m_Wall->GetBumpTexture(),
		m_SunLight->GetDirection(), m_SunLight->GetDiffuseColor(), m_SunLight->GetAmbientColor(), m_Camera->GetPosition());



	//�@�u���b�N
	for (int i = 0; i < 10; i++)
	{
		m_Direct3D->GetWorldMatrix(worldMatrix);
		m_Block->GetPosition(posX, posY, posZ);
		worldMatrix *= XMMatrixTranslation(posX + 10.0f*i, posY, posZ);


		m_Block->Render(m_Direct3D->GetDeviceContext());
		result = m_ShaderManager->RenderShadowShader(m_Direct3D->GetDeviceContext(), m_Block->GetIndexCount(),
			worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightOrthoMatrix, m_Block->GetColorTexture(),
			m_RenderTexture->GetShaderResourceView(), m_SunLight->GetDirection(), m_SunLight->GetAmbientColor(), m_SunLight->GetDiffuseColor());

		//result = m_ShaderManager->RenderClothShader(m_Direct3D->GetDeviceContext(), m_Block->GetIndexCount(),
		//	worldMatrix, viewMatrix, projectionMatrix, m_Block->GetColorTexture(), m_Block->GetBumpTexture(),
		//	m_SunLight->GetDirection(), m_SunLight->GetDiffuseColor(), m_SunLight->GetAmbientColor(), m_Camera->GetPosition());
		/*result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Block->GetIndexCount(),
			worldMatrix, viewMatrix, projectionMatrix, m_Block->GetColorTexture());*/
		if (!result)
		{
			return false;
		}
	}

	//�@�v���C���[
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Player->CalculateWorldMatrix(worldMatrix);

	m_Player->Render(m_Direct3D->GetDeviceContext());
	//result = m_ShaderManager->RenderShadowShader(m_Direct3D->GetDeviceContext(), m_Sack->GetIndexCount(),
	//	worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightOrthoMatrix, m_Sack->GetColorTexture(),
	//	m_RenderTexture->GetShaderResourceView(), m_SunLight->GetDirection(), m_SunLight->GetAmbientColor(), m_SunLight->GetDiffuseColor());

	result = m_ShaderManager->RenderClothShader(m_Direct3D->GetDeviceContext(), m_Player->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_Player->GetColorTexture(), m_Player->GetBumpTexture(),
		m_SunLight->GetDirection(), m_SunLight->GetDiffuseColor(), m_SunLight->GetAmbientColor(), m_Camera->GetPosition());
	/*result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), m_Block->GetIndexCount(),
	worldMatrix, viewMatrix, projectionMatrix, m_Block->GetColorTexture());*/
	if (!result)
	{
		return false;
	}

	//�@�t�b�N
	/*
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Hook->CalculateWorldMatrix(worldMatrix);

	m_Hook->Render(m_Direct3D->GetDeviceContext());
	//result = m_ShaderManager->RenderShadowShader(m_Direct3D->GetDeviceContext(), m_Hook->GetIndexCount(),
	//	worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightOrthoMatrix, m_Hook->GetColorTexture(),
	//	m_RenderTexture->GetShaderResourceView(), m_SunLight->GetDirection(), m_SunLight->GetAmbientColor(), m_SunLight->GetDiffuseColor());

	result = m_ShaderManager->RenderSpecularShader(m_Direct3D->GetDeviceContext(), m_Hook->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_Hook->GetColorTexture(), 
		m_SunLight->GetDirection(),m_SunLight->GetAmbientColor(), m_SunLight->GetDiffuseColor(),
		m_Camera->GetPosition(), m_SunLight->GetSpecularColor(), m_SunLight->GetSpecularPower());
	if (!result)
	{
		return false;
	}
	*/
	//----------------------------
	//�@�@�`��I��
	//----------------------------
	m_Direct3D->EndScene();

	return true;
}

//==============================================================================
//  �֐���		 RenderToTexture
//  ����			 �e�N�X�`���ɕ`�悷��֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CGraphics::RenderSceneToTexture()
{
	XMMATRIX worldMatrix, lightViewMatrix, lightOrthoMatrix;
	bool result;
	float posX, posY, posZ;

	m_RenderTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());
	m_RenderTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	m_SunLight->GenerateViewMatrix();

	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_SunLight->GetViewMatrix(lightViewMatrix);
	m_SunLight->GetOrthoMatrix(lightOrthoMatrix);

	//----------------------------
	//�@3D �`�� 
	//----------------------------

	//�@�u���b�N
	for (int i = 0; i < 10; i++)
	{
		m_Direct3D->GetWorldMatrix(worldMatrix);
		m_Block->GetPosition(posX, posY, posZ);
		worldMatrix *= XMMatrixTranslation(posX + 10.0f*i, posY, posZ);


		m_Block->Render(m_Direct3D->GetDeviceContext());
		result = m_ShaderManager->RenderDepthShader(m_Direct3D->GetDeviceContext(), m_Block->GetIndexCount(),
			worldMatrix, lightViewMatrix, lightOrthoMatrix);
		if (!result)
		{
			return false;
		}
	}

	//�@�v���C���[
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Player->CalculateWorldMatrix(worldMatrix);

	m_Player->Render(m_Direct3D->GetDeviceContext());
	//result = m_ShaderManager->RenderShadowShader(m_Direct3D->GetDeviceContext(), m_Sack->GetIndexCount(),
	//	worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightOrthoMatrix, m_Sack->GetColorTexture(),
	//	m_RenderTexture->GetShaderResourceView(), m_SunLight->GetDirection(), m_SunLight->GetAmbientColor(), m_SunLight->GetDiffuseColor());
	result = m_ShaderManager->RenderDepthShader(m_Direct3D->GetDeviceContext(), m_Player->GetIndexCount(),
		worldMatrix, lightViewMatrix, lightOrthoMatrix);
	if (!result)
	{
		return false;
	}

	//�@�t�b�N
	/*
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Hook->CalculateWorldMatrix(worldMatrix);

	m_Hook->Render(m_Direct3D->GetDeviceContext());
	result = m_ShaderManager->RenderDepthShader(m_Direct3D->GetDeviceContext(), m_Hook->GetIndexCount(),
		worldMatrix, lightViewMatrix, lightOrthoMatrix);
	if (!result)
	{
		return false;
	}
	*/
	m_Direct3D->SetBackBufferRenderTarget();
	m_Direct3D->ResetViewport();

	return true;
}

