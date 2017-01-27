//******************************************************************************
//	BlockClass.h
//	2017-01-16
//	Irene Gersenowies
//******************************************************************************

#ifndef __CBLOCK_H__
#define __CBLOCK_H__

//==============================================================================
//		�C���N���[�h
//==============================================================================
//# include "C3DObject.h"
# include "GameObjectBase.h"
# include "Macros.h"
# include "ModelClass.h"
# include "TextureClass.h"

//==============================================================================
//	�}�N���萔
//==============================================================================


//==============================================================================
//	�N���X��		CBlock
//==============================================================================
class CBlock : public CGameObjectBase
{
public:

	//�u���b�N�F�̂h�c
	enum BLOCK_COLOR
	{
		BLOCK_NONE,
		BLOCK_GREEN,				//��
		BLOCK_RED,					//��
		BLOCK_INVISIBLE,			//�����Ȃ���

		BLOCK_COLOR_MAX				//�F�̍ő吔

	};

	CBlock(void) {};
	CBlock(const CBlock& other) {};
	CBlock(BLOCK_COLOR color);		//�R���X�g���N�^
	~CBlock(void);					//�f�X�g���N�^

	bool InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Shutdown();

	void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix); //�`��֐�
	
private:

	//BLOCK_COLOR m_color;
	XMFLOAT4 m_color;
	CModel* m_model;

	CTexture* m_colorTexture;
	CTexture* m_bumpTexture;

	void SetColor(BLOCK_COLOR color);	//�u���b�N�̐F��ς���֐�

};

#endif
//******************************************************************************
//	End of file.
//******************************************************************************