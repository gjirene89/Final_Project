//*****************************************************************************
//!	@file	C2DObject.cpp
//!	@brief	2D�Q�[���I�u�W�F�N�g�N���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�|
//-----------------------------------------------------------------------------
#include	"C2DObject.h"
#include	"CDirectxGraphics.h"

//==============================================================================
//!	@fn		C2DObject
//!	@brief	2D�I�u�W�F�N�g�̃R���X�g���N�^
//!	@param	float    PosX		X���̈ʒu
//!	@param	float    PosY		Y���̈ʒu
//!	@param	float    Width		��
//!	@param	float    Height		����
//!	@param	D3DCOLOR Color		�F
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
C2DObject::C2DObject(float PosX, float PosY, float Width, float Height, D3DCOLOR color_) : CGameObjectBase(GAMEOBJTYPE::GOBJ_UI)
{
	//������
	center.x = PosX;
	center.y = PosY;
	dimension.x = Width;
	dimension.y = Height;
	color = color_;

	//UV�̏�����
	animInfo.f_uvLeft		= 0.0f;
	animInfo.f_uvRight		= 1.0f;
	animInfo.f_uvTop		= 0.0f;
	animInfo.f_uvBottom		= 1.0f;
}

//==============================================================================
//!	@fn		~C2DObject
//!	@brief	2D�I�u�W�F�N�g�̃f�X�g���N�^
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
C2DObject::~C2DObject(void)
{
	//���͋�
}

//==============================================================================
//!	@fn		Init
//!	@brief	2D�I�u�W�F�N�g�̏�����
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void C2DObject::Init(void)
{
	//���_�������߂�
	CalcVertex();
}

//==============================================================================
//!	@fn		Input
//!	@brief	2D�Q�[���I�u�W�F�N�̓��͊֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
void C2DObject::Input(void)
{
	//���͋�
}


//==============================================================================
//!	@fn		Render
//!	@brief	2D�I�u�W�F�N�g�̕`��
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void C2DObject::Render(void)
{
	//�B���Ă����Ԃ�������A�`�悵�Ȃ�
	if (isHidden)
		return;

	//�e�N�X�`��������
	CDirectXGraphics::GetDXDevice()->SetTexture(0, texture);

	CDirectXGraphics::GetDXDevice()->SetFVF(FVF_TLVERTEX2D);
	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//D3DCULL_CW,D3DCULL_CCW,D3DCULL_NONE determina que lado no va a ser renderizado

	//���C�g������
	CDirectXGraphics::GetDXDevice()->LightEnable(0, FALSE);
	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//�`�施��(���_�f�[�^�̓]��+�`��)
	CDirectXGraphics::GetDXDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(TLVERTEX2D));//�����@D3DPT_TRIANGLEFAN,1, �̂P�̂Ƃ�����Q�ɕς���
	
	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//���C�g��_����
	CDirectXGraphics::GetDXDevice()->LightEnable(0, TRUE);
	CDirectXGraphics::GetDXDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//==============================================================================
//!	@fn		Action
//!	@brief	2D�I�u�W�F�N�g�̏����֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void C2DObject::Action(void)
{
	//���͋�
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	2D�I�u�W�F�N�g�̌㏈���֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void C2DObject::PostAction(void)
{
	//���͋�
}

//==============================================================================
//!	@fn		CalcVertex
//!	@brief	���_��UV�������߂�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void C2DObject::CalcVertex(void)
{
	//���_�������߂�
	vertex[0].rhw = vertex[1].rhw = vertex[2].rhw = vertex[3].rhw = 1.0f;					//rhw��1.0�ɂ���  
	vertex[0].diffuse = vertex[1].diffuse = vertex[2].diffuse = vertex[3].diffuse = color;	//���_�J���[	

	vertex[0].x = vertex[1].x = center.x - dimension.x / 2.0f;
	vertex[2].x = vertex[3].x = center.x + dimension.x / 2.0f;

	vertex[1].y = vertex[2].y = center.y - dimension.y / 2.0f;
	vertex[0].y = vertex[3].y = center.y + dimension.y / 2.0f;

	vertex[0].z = vertex[1].z = vertex[2].z = vertex[3].z = 0.0f;

	//UV��ݒ肷��
	vertex[0].tu = vertex[1].tu = animInfo.f_uvLeft;
	vertex[2].tu = vertex[3].tu = animInfo.f_uvRight;

	vertex[0].tv = vertex[3].tv = animInfo.f_uvBottom;
	vertex[1].tv = vertex[2].tv = animInfo.f_uvTop;
}


//==============================================================================
//!	@fn		SetSize
//!	@brief	�T�C�Y���Z�b�g����
//!	@param	fWidth		��
//! @param  fHeight		����
//!	@retval	�Ȃ�
//==============================================================================
void C2DObject::SetSize(float fWidth, float fHeight)
{
	//x�̃T�C�Y
	dimension.x = fWidth;

	//y�̃T�C�Y
	dimension.y = fHeight;
}

//==============================================================================
//!	@fn		SetColor
//!	@brief	�F���Z�b�g����֐�
//!	@param	�|���̐F
//!	@retval	�Ȃ�
//==============================================================================
void C2DObject::SetColor(D3DCOLOR newColor)
{
	//�F���Z�b�g����
	color = newColor;
}

//==============================================================================
//!	@fn		SetCenter
//!	@brief	���S�_���Z�b�g
//!	@param	fPosX	X���W
//!	@param	fPosY	Y���W
//!	@param	fPosZ	Z���W
//!	@retval	�Ȃ�
//==============================================================================
void C2DObject::SetCenter(float fPosX, float fPosY)
{
	//�ʒu���Z�b�g����
	center.x = fPosX;
	center.y = fPosY;
}
//******************************************************************************
//	End of file.
//******************************************************************************
