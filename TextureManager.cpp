//*****************************************************************************
//!	@file	TextureManager.cpp
//!	@brief	�e�N�X�`���[�Ǘ��N���X�̊֐��Q
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�|
//-----------------------------------------------------------------------------
# include "TextureManager.h"
# include "CDirectxGraphics.h"
# include <string>

//-----------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 TexManager::texture[TexManager::TEX_MAX];

//==============================================================================
//!	@fn		TexManager
//!	@brief	�e�N�X�`���Ǘ��N���X�̃R���X�g���N�^
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
TexManager::TexManager()
{
	//�|�C���^������������
	for (int texNo = 0; texNo < TEX_MAX; texNo++)
	{
		texture[texNo] = nullptr;
	}

	//�e�N�X�`��������͂���
	LPCSTR tempTex[TEX_MAX];
	tempTex[TEX_TITLE]				= "assets/textures/title.jpg"; 
	tempTex[TEX_GAMEOVER]			= "assets/textures/gameOver.jpg";
	tempTex[TEX_GAMECLEAR]			= "assets/textures/gameClear.jpg";
	tempTex[TEX_BACKGROUND]			= "assets/textures/clothBase.jpg";
	tempTex[TEX_CLOUD_0]			= "assets/textures/cloud0.tga";
	tempTex[TEX_CLOUD_1]			= "assets/textures/cloud1.tga";
	tempTex[TEX_SUN]				= "assets/textures/sun.tga";
	tempTex[TEX_PLAYER_COLOR]		= "assets/textures/PlayerColor.tga";
	tempTex[TEX_PLAYER_BUMP]		= "assets/textures/PlayerBump.png";
	tempTex[TEX_SACK_COLOR_BLUE]	= "assets/textures/SackColorBlue.tga";
	tempTex[TEX_SACK_COLOR_PURPLE]	= "assets/textures/SackColorPurple.tga";
	tempTex[TEX_SACK_COLOR_GREEN]	= "assets/textures/SackColorGreen.tga";

	//�N���X�̕ϐ��ɃR�s�[����
	memcpy(texName, tempTex, sizeof(LPCSTR)*TEX_MAX);
	
}

//==============================================================================
//!	@fn		~TexManager
//!	@brief	�e�N�X�`���Ǘ��N���X�̃f�X�g���N�^
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
TexManager::~TexManager()
{
	//�e�N�X�`���̏����������
	for (int texNo = 0; texNo < TEX_MAX; texNo++)
	{
		if (texture[texNo] != nullptr)
		{
			texture[texNo]->Release();
			texture[texNo] = nullptr;
		}
	}
}

//==============================================================================
//!	@fn		Init
//!	@brief	�e�N�X�`���Ǘ��N���X�̏����֐�
//!	@param	HWND	�E�C���h�[�n���h��
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
bool TexManager::Init(HWND hwnd)
{
	//�e�N�X�`�������[�h����
	for (int texNo = 0; texNo < TEX_MAX; texNo++)
	{
		//������Ȃ��ꍇ�A�G���[���b�Z�[�W���o��
		if (FAILED(D3DXCreateTextureFromFile(CDirectXGraphics::GetDXDevice(), texName[texNo], &texture[texNo])))
		{
			char error[128];
			strcpy_s(error, (char *)texName[texNo]);
			strcat_s(error, " was not found!");
			MessageBox(hwnd, error, "ERROR!!", MB_OK);
			return false;
		}

	}
	return true;
}

//==============================================================================
//!	@fn		GetTexture
//!	@brief	�e�N�X�`���̃|�C���^��߂��֐�
//!	@param	�Ȃ�
//!	@retval	LPDIRECT3DTEXTURE�@�@�e�N�X�`���|�C���^
//!	@note	
//==============================================================================
LPDIRECT3DTEXTURE9 TexManager::GetTexture(TEX_ID texId)
{
	return texture[texId];
}
//******************************************************************************
//	End of file.
//******************************************************************************
