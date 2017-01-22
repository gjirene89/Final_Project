//************************************************************************//
//	GameObjectBase.cpp
//	2017-01-14
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
#include "GameObjectBase.h"
#include "ShaderManagerClass.h"

//==============================================================================
//  �֐���        CGameObjectBase	
//  ����          CGameObjectBase�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CGameObjectBase::CGameObjectBase()
{
	m_objType = GOBJ_NONE;
	m_isHidden = false;
	m_pNextObj = nullptr;

	m_positionX = 0;
	m_positionY = 0;
	m_positionZ = 0;

	m_rotationX = 0;
	m_rotationY = 0;
	m_rotationZ = 0;

}

CGameObjectBase::CGameObjectBase(GAMEOBJTYPE objType)
{
	
	m_objType = objType;
	m_isHidden = false;
	m_pNextObj = nullptr;

	m_positionX = 0;
	m_positionY = 0;
	m_positionZ = 0;

	m_rotationX = 0;
	m_rotationY = 0;
	m_rotationZ = 0;
}

//==============================================================================
//  �֐���        CGameObjectBase	
//  ����          CGameObjectBase�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          CGameObjectBase& other			CGameObjectBase�̃C���X�^���X
//	�߂�l
//          �Ȃ�
//==============================================================================
CGameObjectBase::CGameObjectBase(const CGameObjectBase& other)
{
	//��
}

//==============================================================================
//  �֐���        �`CGameObjectBase	
//  ����          CGameObjectBase�N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CGameObjectBase::~CGameObjectBase()
{
	//��
}


void CGameObjectBase::Initialize()
{
	return;
}

void CGameObjectBase::Input()
{
	//���͋�
}

void CGameObjectBase::Action()
{

}

void CGameObjectBase::PostAction()
{

}


//==============================================================================
//  �֐���        SetPosition
//  ����          ���f���̈ʒu���Z�b�g����֐�
//------------------------------------------------------------------------------
//	����
//          float      x            X��
//          float      y            Y��
//          float      z            Z��
//	�߂�l
//          �Ȃ�
//==============================================================================
void CGameObjectBase::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;

	return;
}

//==============================================================================
//  �֐���        SetRotation
//  ����          ���f���̉�]���Z�b�g����֐�
//------------------------------------------------------------------------------
//	����
//          float      x            X��
//          float      y            Y��
//          float      z            Z��
//	�߂�l
//          �Ȃ�
//==============================================================================
void CGameObjectBase::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;

	return;
}


//==============================================================================
//  �֐���        GetPosition
//  ����          ���f���̈ʒu��߂��֐�
//------------------------------------------------------------------------------
//	����
//          float&      x            X��
//          float&      y            Y��
//          float&      z            Z��
//	�߂�l
//          �Ȃ�
//==============================================================================
void CGameObjectBase::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;

	return;
}

//==============================================================================
//  �֐���        GetRotation
//  ����          ���f���̈ʒu��߂��֐�
//------------------------------------------------------------------------------
//	����
//          float&      x            X����]
//          float&      y            Y����]
//          float&      z            Z����]
//	�߂�l
//          �Ȃ�
//==============================================================================
void CGameObjectBase::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;

	return;
}

//==============================================================================
//  �֐���        CalculateWorldMatrix
//  ����          ���[���h�z����v�Z����֐�
//------------------------------------------------------------------------------
//	����
//          float&      x            X����]
//          float&      y            Y����]
//          float&      z            Z����]
//	�߂�l
//          �Ȃ�
//==============================================================================
void CGameObjectBase::CalculateWorldMatrix(XMMATRIX& worldMatrix)
{
	float yaw, pitch, roll;
	XMMATRIX translationMatrix, rotationMatrix;

	//yaw (Y��), pitch (X��), roll (Z��) �����W�A���ɕϊ�����
	pitch = m_rotationX * XM_PI / 180.0f;
	yaw = m_rotationY * XM_PI / 180.0f;
	roll = m_rotationZ * XM_PI / 180.0f;

	//yaw, pitch, roll�ŉ�]�s����쐬����
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	//�ړ��s��
	translationMatrix = XMMatrixTranslation(m_positionX, m_positionY, m_positionZ);

	//���[���h�s������߂�
	worldMatrix = rotationMatrix * translationMatrix;

	return;
}
//*****************************************************************************
//		�擾�֐��Q
//*****************************************************************************

//==============================================================================
//!	@fn		SetNextObj
//!	@brief	���̃Q�[���I�u�W�F�N�g�̃|�C���^���Z�b�g����
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
void CGameObjectBase::SetNextObj(CGameObjectBase* nextObj)
{
	//���̃I�u�W�F�N�g�̃|�C���^���Z�b�g����
	m_pNextObj = nextObj;
}


//==============================================================================
//!	@fn		GetNextObj
//!	@brief	���̃Q�[���I�u�W�F�N�g�̃|�C���^��߂��֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
CGameObjectBase* CGameObjectBase::GetNextObj(void)
{
	//���̃I�u�W�F�N�g�̃|�C���^��߂�
	return m_pNextObj;
}



//******************************************************************************
//	End of file.
//******************************************************************************