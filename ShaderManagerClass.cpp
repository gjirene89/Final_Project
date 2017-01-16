//************************************************************************//
//	ShaderManagerClass.h
//	2016-12-05
//	Irene Gersenowies
//************************************************************************//

#include "ShaderManagerClass.h"

//==============================================================================
//  �֐���        CShaderManager	
//  ����          CShaderManager�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CShaderManager::CShaderManager()
{
	m_ColorShader = 0;
	m_TextureShader = 0;

	/*
	m_BumpMapShader = 0;
	m_ClothShader = 0;
	m_SpecularShader = 0;
	m_ShadowShader = 0;
	m_DepthShader = 0;
	m_VerticalBlurShader = 0;
	m_HorizontalBlurShader = 0;
	m_SoftShadowShader = 0;
	*/
}

//==============================================================================
//  �֐���        CShaderManager	
//  ����          CShaderManager�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          CShaderManager& other			CShaderManager�̃C���X�^���X
//	�߂�l
//          �Ȃ�
//==============================================================================
CShaderManager::CShaderManager(const CShaderManager& other)
{
	//��
}

//==============================================================================
//  �֐���        �`CShaderManager	
//  ����          CShaderManager�N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CShaderManager::~CShaderManager()
{
	//��
}

//==============================================================================
//  �֐���        Initialize
//  ����          ShaderManager�̃V�F�[�_�[�����֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11Device*         device           �f�o�C�X�ւ̃|�C���^
//          HWND                  hwnd			   �E�C���h�E�n���h��
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CShaderManager::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;
	

	//----------------------------
	//�@�@Color�V�F�[�_�[����
	//----------------------------
	m_ColorShader = new CColorShader;
	if (!m_ColorShader)
	{
		return false;
	}

	result = m_ColorShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	//----------------------------
	//�@�@Texture�V�F�[�_�[����
	//----------------------------
	m_TextureShader = new CTextureShader;
	if (!m_TextureShader)
	{
		return false;
	}
	
	result = m_TextureShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}
/*
	//----------------------------
	//�@�@BumpMap�V�F�[�_�[����
	//----------------------------
	m_BumpMapShader = new CBumpMapShader;
	if (!m_BumpMapShader)
	{
		return false;
	}

	result = m_BumpMapShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not inititalize the bump map shader object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//�@�@Cloth�V�F�[�_�[����
	//----------------------------
	m_ClothShader = new CClothShader;
	if (!m_ClothShader)
	{
		return false;
	}

	result = m_ClothShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not inititalize the cloth shader object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//�@�@Cloth�V�F�[�_�[����
	//----------------------------
	m_SpecularShader = new CSpecularShader;
	if (!m_SpecularShader)
	{
		return false;
	}

	result = m_SpecularShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the specular shader object.", L"Error", MB_OK);
		return false;
	}
	
	//----------------------------
	//�@�@Shadow�V�F�[�_�[����
	//----------------------------
	m_ShadowShader = new CShadowShader;
	if (!m_ShadowShader)
	{
		return false;
	}

	result = m_ShadowShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shadow shader object.", L"Error", MB_OK);
		return false;
	}

	//----------------------------
	//�@�@DephtMap�V�F�[�_�[����
	//----------------------------
	m_DepthShader = new CDepthShader;
	if (!m_DepthShader)
	{
		return false;
	}

	result = m_DepthShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;

	}

	//----------------------------
	//�@�@VerticalBlur�V�F�[�_�[����
	//----------------------------
	m_VerticalBlurShader = new CVerticalBlurShader;
	if (!m_VerticalBlurShader)
	{
		return false;
	}

	result = m_VerticalBlurShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the vertical blur shader object.", L"Error", MB_OK);
		return false;

	}

	//----------------------------
	//�@�@HorizontalBlur�V�F�[�_�[����
	//----------------------------
	m_HorizontalBlurShader = new CHorizontalBlurShader;
	if (!m_HorizontalBlurShader)
	{
		return false;
	}

	result = m_HorizontalBlurShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Horizontal blur shader object.", L"Error", MB_OK);
		return false;

	}

	//----------------------------
	//�@�@SoftShadow�V�F�[�_�[����
	//----------------------------
	m_SoftShadowShader = new CSoftShadowShader;
	if (!m_SoftShadowShader)
	{
		return false;
	}

	result = m_SoftShadowShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Horizontal blur shader object.", L"Error", MB_OK);
		return false;

	}
	*/
	return true;
}

//==============================================================================
//  �֐���        Shutdown
//  ����          �V�F�[�_�[�̉�����Ăяo���֐�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CShaderManager::Shutdown()
{
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	/*
	if (m_SoftShadowShader)
	{
		m_SoftShadowShader->Shutdown();
		delete m_SoftShadowShader;
		m_SoftShadowShader = 0;
	}

	if (m_VerticalBlurShader)
	{
		m_VerticalBlurShader->Shutdown();
		delete m_VerticalBlurShader;
		m_VerticalBlurShader = 0;
	}

	if (m_HorizontalBlurShader)
	{
		m_HorizontalBlurShader->Shutdown();
		delete m_HorizontalBlurShader;
		m_HorizontalBlurShader = 0;
	}

	if (m_DepthShader)
	{
		m_DepthShader->Shutdown();
		delete m_DepthShader;
		m_DepthShader = 0;
	}

	if (m_ShadowShader)
	{
		m_ShadowShader->Shutdown();
		delete m_ShadowShader;
		m_ShadowShader = 0;
	}

	if (m_ClothShader)
	{
		m_ClothShader->Shutdown();
		delete m_ClothShader;
		m_ClothShader = 0;
	}
	
	if (m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}
	
	if (m_SpecularShader)
	{
		m_SpecularShader->Shutdown();
		delete m_SpecularShader;
		m_SpecularShader = 0;
	}

	*/
	return;
}


//==============================================================================
//  �֐���		 RenderColorShader	
//  ����			 �F�̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*        deviceContext        �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          int                         indexCount           �C���f�b�N�X �J�E���g
//          XMMATRIX                    worldMatrix          ���[���h �}�g���b�N�X
//          XMMATRIX                    viewMatrix           �r���[ �}�g���b�N�X
//          XMMATRIX                    projectionMatrix     �v���W�F�N�V���� �}�g���b�N�X
//          XMFLOAT4                    vertexColor          ���_�F
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CShaderManager::RenderColorShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT4 vertexColor)
{
	bool result;
	
	result = m_ColorShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, vertexColor);
	if (!result)
	{
		return false;
	}
	
	return true;
}

//==============================================================================
//  �֐���		 RenderTextureShader	
//  ����			 �e�N�X�`���̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*        deviceContext        �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          int                         indexCount           �C���f�b�N�X �J�E���g
//          XMMATRIX                    worldMatrix          ���[���h �}�g���b�N�X
//          XMMATRIX                    viewMatrix           �r���[ �}�g���b�N�X
//          XMMATRIX                    projectionMatrix     �v���W�F�N�V���� �}�g���b�N�X
//          ID3D11ShaderResourceView*   texture              �e�N�X�`��
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CShaderManager::RenderTextureShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	CTexture::TextureData textureData)
{
	bool result;
	
	result = m_TextureShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureData);
	if (!result)
	{
		return false;
	}
	
	return true;
}
/*
//==============================================================================
//  �֐���		 RenderBumpMapShader	
//  ����			 �o���v�}�b�v�̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*        deviceContext        �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          int                         indexCount           �C���f�b�N�X �J�E���g
//          XMMATRIX                    worldMatrix          ���[���h �}�g���b�N�X
//          XMMATRIX                    viewMatrix           �r���[ �}�g���b�N�X
//          XMMATRIX                    projectionMatrix     �v���W�F�N�V���� �}�g���b�N�X
//          ID3D11ShaderResourceView*   colorTexture         �e�N�X�`��
//          ID3D11ShaderResourceView*   normalTexture        �@���e�N�X�`��
//          XMFLOAT3                    lightDirection       ��������
//          XMFLOAT4                    diffuseColor         ���F
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CShaderManager::RenderBumpMapShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	CTexture::TextureData colorTexture, CTexture::TextureData normalTexture,
	XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor)
{
	bool result;
	
	result = m_BumpMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection, diffuseColor);
	if (!result)
	{
		return false;
	}
	
	return true;
}


//==============================================================================
//  �֐���		 RenderSpecularShader	
//  ����			 ���ʂ̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*       deviceContext		�f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          XMMATRIX                   worldMatrix          ���[���h�}�g���b�N�X
//          XMMATRIX                   viewMatrix           �r���[�}�g���b�N�X
//          XMMATRIX                   projectionMatrix     �v���W�F�N�V�����}�g���b�N�X
//          TextureData                textureData         �e�N�X�`��
//          XMFLOAT3                   lightDirection       ���̌���
//          XMFLOAT4                   ambientColor         ���F
//          XMFLOAT4                   diffuseColor         �g�U�F
//          XMFLOAT3                   cameraPosition       �J�����ʒu
//          XMFLOAT4                   specularColor        ���ʐF
//          float                      specularPower        ���ʗ�
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CShaderManager::RenderSpecularShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	CTexture::TextureData textureData,
	XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor,
	XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower)
{
	bool result;
	
	result = m_SpecularShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureData, lightDirection, ambientColor, diffuseColor, cameraPosition, specularColor, specularPower);
	if (!result)
	{
		return false;
	}
	
	return true;
}

//==============================================================================
//  �֐���        RenderClothShader	
//  ����	          Cloth�V�F�[�_�[�̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*        deviceContext        �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          int                         indexCount           �C���f�b�N�X �J�E���g
//          XMMATRIX                    worldMatrix          ���[���h �}�g���b�N�X
//          XMMATRIX                    viewMatrix           �r���[ �}�g���b�N�X
//          XMMATRIX                    projectionMatrix     �v���W�F�N�V���� �}�g���b�N�X
//          ID3D11ShaderResourceView*   colorTexture         �e�N�X�`��
//          ID3D11ShaderResourceView*   normalTexture        �@���e�N�X�`��
//          XMFLOAT3                    lightDirection       ��������
//          XMFLOAT4                    diffuseColor         ���F
//          XMFLOAT4                    ambientColor         ���F
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CShaderManager::RenderClothShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	CTexture::TextureData colorTexture, CTexture::TextureData normalTexture,
	XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor, XMFLOAT4 ambientColor,
	XMFLOAT3 cameraPosition)
{
	bool result;

	//Cloth�V�F�[�_�[�ŕ`�悷��
	result = m_ClothShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection, diffuseColor,ambientColor, cameraPosition);
	if (!result)
	{
		return false;
	}
}

//==============================================================================
//  �֐���		 RenderShadowShader	
//  ����			 �V���h�[�̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*       deviceContext		�f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          XMMATRIX                   worldMatrix          ���[���h�}�g���b�N�X
//          XMMATRIX                   viewMatrix           �r���[�}�g���b�N�X
//          XMMATRIX                   projectionMatrix     �v���W�F�N�V�����}�g���b�N�X
//          TextureData                textureData         �e�N�X�`��
//          XMFLOAT3                   lightDirection       ���̌���
//          XMFLOAT4                   ambientColor         ���F
//          XMFLOAT4                   diffuseColor         �g�U�F
//          XMFLOAT3                   cameraPosition       �J�����ʒu
//          XMFLOAT4                   specularColor        ���ʐF
//          float                      specularPower        ���ʗ�
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CShaderManager::RenderShadowShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	XMMATRIX lightViewMatrix, XMMATRIX lightProjectionMatrix,
	CTexture::TextureData colorTexture, ID3D11ShaderResourceView* depthMapTexture,
	XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor)
{
	bool result;

	result = m_ShadowShader->Render(deviceContext, indexCount, 
		worldMatrix, viewMatrix, projectionMatrix, 
		lightViewMatrix, lightProjectionMatrix,
		colorTexture, depthMapTexture, 
		lightDirection, ambientColor, diffuseColor);
	if (!result)
	{
		return false;
	}

	return true;
}


//==============================================================================
//  �֐���		 RenderDepthShader	
//  ����			 �F�̕`��֐�
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*        deviceContext        �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          int                         indexCount           �C���f�b�N�X �J�E���g
//          XMMATRIX                    worldMatrix          ���[���h �}�g���b�N�X
//          XMMATRIX                    viewMatrix           �r���[ �}�g���b�N�X
//          XMMATRIX                    projectionMatrix     �v���W�F�N�V���� �}�g���b�N�X
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CShaderManager::RenderDepthShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	bool result;

	result = m_DepthShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	return true;
}

//==============================================================================
//  �֐���		 RenderVerticalBlurShader	
//  ����			 ���ڂ���
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*        deviceContext        �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          int                         indexCount           �C���f�b�N�X �J�E���g
//          XMMATRIX                    worldMatrix          ���[���h �}�g���b�N�X
//          XMMATRIX                    viewMatrix           �r���[ �}�g���b�N�X
//          XMMATRIX                    projectionMatrix     �v���W�F�N�V���� �}�g���b�N�X
//          ID3D11ShaderResourceView*   texture              �e�N�X�`��
//          float                       screenHeight		 �e�N�X�`���T�C�Y
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CShaderManager::RenderVerticalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, float screenHeight)
{
	bool result;

	result = m_VerticalBlurShader->Render(deviceContext, indexCount, 
		worldMatrix, viewMatrix, projectionMatrix, texture, screenHeight);
	if (!result)
	{
		return false;
	}

	return true;

}

//==============================================================================
//  �֐���		 RenderHorizontalBlurShader	
//  ����			�c�ڂ���
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*        deviceContext        �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          int                         indexCount           �C���f�b�N�X �J�E���g
//          XMMATRIX                    worldMatrix          ���[���h �}�g���b�N�X
//          XMMATRIX                    viewMatrix           �r���[ �}�g���b�N�X
//          XMMATRIX                    projectionMatrix     �v���W�F�N�V���� �}�g���b�N�X
//          ID3D11ShaderResourceView*   texture              �e�N�X�`��
//          float                       screenHeight		 �e�N�X�`���T�C�Y
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CShaderManager::RenderHorizontalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView* texture, float screenWidth)
{
	bool result;

	result = m_HorizontalBlurShader->Render(deviceContext, indexCount,
		worldMatrix, viewMatrix, projectionMatrix, texture, screenWidth);
	if (!result)
	{
		return false;
	}

	return true;

}


//==============================================================================
//  �֐���		 RenderHorizontalBlurShader	
//  ����			�c�ڂ���
//------------------------------------------------------------------------------
//	����
//          ID3D11DeviceContext*        deviceContext        �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//          int                         indexCount           �C���f�b�N�X �J�E���g
//          XMMATRIX                    worldMatrix          ���[���h �}�g���b�N�X
//          XMMATRIX                    viewMatrix           �r���[ �}�g���b�N�X
//          XMMATRIX                    projectionMatrix     �v���W�F�N�V���� �}�g���b�N�X
//          ID3D11ShaderResourceView*   texture              �e�N�X�`��
//          float                       screenHeight		 �e�N�X�`���T�C�Y
//	�߂�l
//			bool	true �����@�@�@false ���s
//==============================================================================
bool CShaderManager::RenderSoftShadowShader(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
	CTexture::TextureData colorTexture, ID3D11ShaderResourceView* shadowTexture,
	XMFLOAT3 lightPosition, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor)
{
	bool result;

	result = m_SoftShadowShader->Render(deviceContext, indexCount,
		worldMatrix, viewMatrix, projectionMatrix, colorTexture, shadowTexture,
		lightPosition, ambientColor, diffuseColor);
	if (!result)
	{
		return false;
	}

	return true;
}
*/

//******************************************************************************
//	End of file.
//******************************************************************************