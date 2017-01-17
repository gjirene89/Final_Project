//******************************************************************************
//	HitBaseClass.cpp
//  �����蔻��N���X�̃x�[�X
//	2017-01-16
//	Irene Gersenowies
//******************************************************************************

//==============================================================================
//		�C���N���[�h
//==============================================================================
# include "HitBaseClass.h"

//==============================================================================
//  �֐���       CHit_Base
//  ����			�����蔻��x�[�X�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CHit_Base::CHit_Base(void)
{
	m_type = HIT_NONE;
	m_entity = nullptr;
	m_isVisible = true;
	m_color = COLOR_NORMAL;
	m_isHit = false;

	return;
}

//==============================================================================
//  �֐���       CHit_Base
//  ����			�����蔻��x�[�X�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          GAMEHIT_TYPE	type	�Q�[���I�u�W�F�N�g�̎��
//	�߂�l
//          �Ȃ�
//==============================================================================
CHit_Base::CHit_Base(GAMEHIT_TYPE type)
{
	m_type = type;
	m_entity = nullptr;
	m_isVisible = true;
	m_color = COLOR_NORMAL;
	m_isHit = false;

	return;
}

//==============================================================================
//  �֐���       ~CHit_Base
//  ����			�����蔻��x�[�X�N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CHit_Base::~CHit_Base(void)
{
	m_entity = nullptr;

	return;
}

//==============================================================================
//  �֐���       Initialize
//  ����			�����蔻��̃I�u�W�F�N�g�̐F����������
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CHit_Base::Initialize(void)
{
	m_isHit = false;
	m_color = COLOR_NORMAL;

	return;
}

//==============================================================================
//  �֐���       UpdatePosition
//  ����			�ʒu���X�V����
//------------------------------------------------------------------------------
//	����
//          XMFLOAT3	position		�V�����ʒu���
//	�߂�l
//          �Ȃ�
//==============================================================================
void CHit_Base::UpdatePosition(XMFLOAT3 position)
{
	m_position = position;

	return;
}

//==============================================================================
//  �֐���        Hightlight
//  ����			�����蔻��̃I�u�W�F�N�g�̐F����������
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CHit_Base::Highlight()
{
	m_color = COLOR_HLIGHT;

	return;
}

//==============================================================================
//  �֐���       GetHitType
//  ����			�����蔻��̎�ނ�߂�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//			GAMEHIT_TYPE	�����蔻��̎��
//==============================================================================
GAMEHIT_TYPE CHit_Base::GetHitType(void)
{
	return m_type;
}

//==============================================================================
//  �֐���       GetPosition
//  ����			�ʒu����߂�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          XMFLOAT3	 �ʒu���
//==============================================================================
XMFLOAT3 CHit_Base::GetPosition(void)
{
	return m_position;
}

//==============================================================================
//  �֐���        GetEntity
//  ����          �A�����Ă���Q�[���I�u�W�F�N�g��߂�
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          CGameObjectBase* �@�@�Q�[���I�u�W�F�N�g�ւ̃|�C���^
//==============================================================================
CGameObjectBase* CHit_Base::GetEntity(void)
{
	return m_entity;
}

//******************************************************************************
//	End of file.
//******************************************************************************