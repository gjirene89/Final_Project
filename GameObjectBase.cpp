//************************************************************************//
//	GameObjectBase.cpp
//	2017-01-14
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
#include "GameObjectBase.h"
#include "ShaderManager.h"

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

	m_position.x = 0;
	m_position.y = 0;
	m_position.z = 0;

	m_rotation.x = 0;
	m_rotation.y = 0;
	m_rotation.z = 0;

}

CGameObjectBase::CGameObjectBase(GAMEOBJTYPE objType)
{
	
	m_objType = objType;
	m_isHidden = false;
	m_pNextObj = nullptr;

	m_position.x = 0;
	m_position.y = 0;
	m_position.z = 0;

	m_rotation.x = 0;
	m_rotation.y = 0;
	m_rotation.z = 0;
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

void CGameObjectBase::Input(CInput* input)
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
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

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
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;

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
	x = m_position.x;
	y = m_position.y;
	z = m_position.z;

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
	x = m_rotation.x;
	y = m_rotation.y;
	z = m_rotation.z;

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
void CGameObjectBase::CalculateWorldMatrix(XMMATRIX& worldMatrix, float rotX, float rotY, float rotZ)
{
	float yaw, pitch, roll;
	XMMATRIX translationMatrix, rotationMatrix;

	//yaw (Y��), pitch (X��), roll (Z��) �����W�A���ɕϊ�����
	pitch = rotX * XM_PI / 180.0f;
	yaw = rotY * XM_PI / 180.0f;
	roll = rotZ * XM_PI / 180.0f;

	//yaw, pitch, roll�ŉ�]�s����쐬����
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	//�ړ��s��
	translationMatrix = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);

	//���[���h�s������߂�
	worldMatrix = rotationMatrix * translationMatrix;

	return;
}

void CGameObjectBase::CalculateWorldMatrix(XMMATRIX& worldMatrix, XMVECTOR quaternion)
{
	float yaw, pitch, roll;
	XMMATRIX translationMatrix, rotationMatrix;

	//yaw, pitch, roll�ŉ�]�s����쐬����
	rotationMatrix = XMMatrixRotationQuaternion(quaternion);

	//�ړ��s��
	translationMatrix = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);

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

XMFLOAT3 CGameObjectBase::GetRotX()
{
	XMFLOAT4X4 tempMat;

	XMStoreFloat4x4(&tempMat, m_matrix);

	return (XMFLOAT3(tempMat._11,tempMat._12 ,tempMat._13 ));
}

XMFLOAT3 CGameObjectBase::GetRotY()
{
	XMFLOAT4X4 tempMat;

	XMStoreFloat4x4(&tempMat, m_matrix);

	return (XMFLOAT3(tempMat._21, tempMat._22, tempMat._23));
}

XMFLOAT3 CGameObjectBase::GetRotZ()
{
	XMFLOAT4X4 tempMat;

	XMStoreFloat4x4(&tempMat, m_matrix);

	return (XMFLOAT3(tempMat._31, tempMat._32, tempMat._33));
}


XMFLOAT3 CGameObjectBase::GetWorldPos()
{
	XMFLOAT4X4 tempMat;

	XMStoreFloat4x4(&tempMat, m_matrix);

	return (XMFLOAT3(tempMat._41, tempMat._42, tempMat._43));
}

//******************************************************************************
//	End of file.
//******************************************************************************