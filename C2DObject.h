//*****************************************************************************
//!	@file	C2DObject.h
//!	@brief	2D�Q�[���I�u�W�F�N�g�N���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

#ifndef __GM31_2DOBJECT__
#define __GM31_2DOBJECT__

//-----------------------------------------------------------------------------
//	�w�b�_�|
//-----------------------------------------------------------------------------
#include "GameObjectBase.h"
#include "AnimationSupport.h"
#include "CDirectxGraphics.h"

//=============================================================================
//!	@class	C2DObject
//!	@brief	2D�Q�[���I�u�W�F�N�g�̃x�[�X
//=============================================================================
class C2DObject : public CGameObjectBase
{
protected:
	TLVERTEX2D	vertex[4];		//�l�p�`
	DWORD		color;			//�F
	POINT		center;			//�ʒu
	POINT		dimension;		//�傫��
	POINT		angle;			//�p�x
	ANIMEUV		animInfo;		//�A�j�����

public:
	C2DObject(float PosX, float PosY, float Width, float Height, D3DCOLOR color);				//�R���X�g���N�^
	~C2DObject();				//�f�X�g���N�^

	void Input(void);
	void Init(void);			//�������֐�
	void Action(void);			//�����֐�
	void Render(void);			//�`��֐�
	void PostAction(void);		//�㏈���֐�

	void CalcVertex(void);		//���_�̏����v�Z����֐�

	void SetSize(float fWidth, float fHeight);		//�傫�����Z�b�g����֐�
	void SetColor(D3DCOLOR color);					//�F���Z�b�g����֐�
	void SetCenter(float fPosX, float fPosY);		//�ʒu���Z�b�g����֐�


};


#endif