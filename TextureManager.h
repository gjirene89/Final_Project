//*****************************************************************************
//!	@file	TextureManager.h
//!	@brief	�e�N�X�`���Ǘ��֐�
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

# ifndef __GM31_TEX_MANAGER__
# define __GM31_TEX_MANAGER__

//-----------------------------------------------------------------------------
//	�w�b�_�|
//-----------------------------------------------------------------------------
#include	<d3d9.h>
#include	<d3dx9.h>

//=============================================================================
//!	@class	TexManager
//!	@brief	�e�N�X�`���Ǘ��N���X
//=============================================================================
class TexManager
{
public:

	//�e�N�X�`����ID
	enum TEX_ID
	{
		TEX_TITLE,				//�^�C�g���̉��
		TEX_GAMEOVER,			//�Q�[���I�[�o�[�̉��
		TEX_GAMECLEAR,			//�Q�[���N���A�̉��
		TEX_BACKGROUND,			//�w�i�x�[�X
		TEX_CLOUD_0,			//�_�o�[�V�����P
		TEX_CLOUD_1,			//�_�o�[�V�����Q
		TEX_SUN,				//���z
		TEX_PLAYER_COLOR,		//�v���C���[�̐F
		TEX_PLAYER_BUMP,		//�o���v�}�b�v
		TEX_SACK_COLOR_BLUE,	
		TEX_SACK_COLOR_PURPLE,
		TEX_SACK_COLOR_GREEN,

		TEX_MAX					//�e�N�X�`���̍ő吔
	};

	~TexManager(void);				//�f�X�g���N�^
	
	bool Init(HWND hwnd);		//�������֐�
	static LPDIRECT3DTEXTURE9 GetTexture(TEX_ID texId);	//�e�N�X�`�����̎擾�֐�

private:

	TexManager(void);				//�R���X�g���N�^

	static LPDIRECT3DTEXTURE9 texture[TEX_MAX];			//�e�N�X�`���z��
	LPCSTR texName[TEX_MAX];							//�e�N�X�`���̃t�@�C�����z��
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************