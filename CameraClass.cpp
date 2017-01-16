//************************************************************************//
//	CameraClass.cpp
//	2016-11-08
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//   �C���N���[�h
//=======================================================================//
#include "CameraClass.h"

//==============================================================================
//  �֐���        CCamera	
//  ����          CCamera�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CCamera::CCamera()
{
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_fPosZ = 0.0f;

	m_fRotX = 0.0f;
	m_fRotY = 0.0f;
	m_fRotZ = 0.0f;
}

//==============================================================================
//  �֐���        CCamera	
//  ����          CCamera�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          CCamera& other			CCamera�̃C���X�^���X
//	�߂�l
//          �Ȃ�
//==============================================================================
CCamera::CCamera(const CCamera& other)
{
	//��
}

//==============================================================================
//  �֐���        �`CCamera	
//  ����          CCamera�N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CCamera::~CCamera()
{
	//��
}

//==============================================================================
//  �֐���        SetPostion	
//  ����			  �J�����̈ʒu���Z�b�g����֐�
//------------------------------------------------------------------------------
//	����
//			float fPosX			X���ʒu
//			float fPosY			y���ʒu
//			float fPosZ			z���ʒu
//	�߂�l
//          �Ȃ�
//==============================================================================
void CCamera::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_fPosX = fPosX;
	m_fPosY = fPosY;
	m_fPosZ = fPosZ;

	return;
}

//==============================================================================
//  �֐���        SetRotation	
//  ����			  �J�����̉�]�x���Z�b�g����֐�
//------------------------------------------------------------------------------
//	����
//			float fRotX			X����]
//			float fRotY			y����]
//			float fRotZ			z����]
//	�߂�l
//          �Ȃ�
//==============================================================================
void CCamera::SetRotation(float fRotX, float fRotY, float fRotZ)
{
	m_fRotX = fRotX;
	m_fRotY = fRotY;
	m_fRotZ = fRotZ;

	return;
}

//==============================================================================
//  �֐���        GetPosition	
//  ����	          �J�����̈ʒu���Q�b�g����
//------------------------------------------------------------------------------
//	����
//			float& fPosX			X���ʒu
//			float& fPosY			y���ʒu
//			float& fPosZ			z���ʒu
//	�߂�l
//          �Ȃ�
//==============================================================================
void CCamera::GetPosition(float& fPosX, float& fPosY, float& fPosZ)
{
	fPosX = m_fPosX;
	fPosY = m_fPosY;
	fPosZ = m_fPosZ;

	return;
}

//==============================================================================
//  �֐���        GetPosition	
//  ����	          �J�����̈ʒu���Q�b�g����
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          XMFLOAT3       position          �J�����̈ʒu
//==============================================================================
XMFLOAT3 CCamera::GetPosition()
{
	return XMFLOAT3(m_fPosX, m_fPosY, m_fPosZ);
}

//==============================================================================
//  �֐���        GetRotation	
//  ����	          �J�����̉�]�x���Q�b�g����
//------------------------------------------------------------------------------
//	����
//			float& fRotX			X����]
//			float& fRotY			y����]
//			float& fRotZ			z����]
//	�߂�l
//          �Ȃ�
//==============================================================================
void CCamera::GetRotation(float& fRotX, float& fRotY, float& fRotZ)
{
	fRotX = m_fRotX;
	fRotY = m_fRotY;
	fRotZ = m_fRotZ;

	return;
}

//==============================================================================
//  �֐���        Render	
//  ����	         �J�����s����쐬����֐�
//------------------------------------------------------------------------------
//	����
//			�Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CCamera::Render()
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	//������̃x�N�g�����`����
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	//XMVECTOR�ւ̕ϊ�
	upVector = XMLoadFloat3(&up);

	//�J�����̈ʒu���x�N�g���ɃZ�b�g����
	position.x = m_fPosX;
	position.y = m_fPosY;
	position.z = m_fPosZ;

	//XMVECTOR�ւ̕ϊ�
	positionVector = XMLoadFloat3(&position);

	//�J�����̌����Ă���ʒu��ݒ肷��
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	//XMVECTOR�ւ̕ϊ�
	lookAtVector = XMLoadFloat3(&lookAt);

	//yaw (Y��), pitch (X��), roll (Z��) �����W�A���ɕϊ�����
	pitch = m_fRotX * XM_PI / 180.0f;
	yaw   = m_fRotY * XM_PI / 180.0f;
	roll  = m_fRotZ * XM_PI / 180.0f;

	//yaw, pitch, roll�ŉ�]�s����쐬����
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	//lookAt�x�N�g���Ə�����x�N�g������]����
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	//�J�������ړ�����
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	//view�s����쐬����
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}

//==============================================================================
//  �֐���        GetViewMatrix	
//  ����	         View�s����Q�b�g����֐�
//------------------------------------------------------------------------------
//	����
//			XMMATRIX& viewMatrix		View�s��
//	�߂�l
//          �Ȃ�
//==============================================================================
void CCamera::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;

	return;
}

//==============================================================================
//  �֐���        RenderBaseViewMatrix
//  ����	         ���s���e�`��p��View�s��
//------------------------------------------------------------------------------
//	����
//			�Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CCamera::RenderBaseViewMatrix()
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float radians;
	XMMATRIX rotationMatrix;

	//������̃x�N�g�����`����
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	//XMVECTOR�ւ̕ϊ�
	upVector = XMLoadFloat3(&up);

	//�J�����̈ʒu���x�N�g���ɃZ�b�g����
	position.x = m_fPosX;
	position.y = m_fPosY;
	position.z = m_fPosZ;

	//XMVECTOR�ւ̕ϊ�
	positionVector = XMLoadFloat3(&position);

	//Calculate the rotation in radians
	radians = m_fRotY * XM_PI / 180.0f;

	//�J�����̌����Ă���ʒu��ݒ肷��
	lookAt.x = sinf(radians) + m_fPosX;
	lookAt.y = m_fPosY;
	lookAt.z = cosf(radians) + m_fPosZ;

	//XMVECTOR�ւ̕ϊ�
	lookAtVector = XMLoadFloat3(&lookAt);

	//view�s����쐬����
	m_baseViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}

//==============================================================================
//  �֐���       GetBaseViewMatrix	
//  ����	         ���s���e�`��p��View�s����Q�b�g����֐�
//------------------------------------------------------------------------------
//	����
//			XMMATRIX& viewMatrix		View�s��
//	�߂�l
//          �Ȃ�
//==============================================================================
void CCamera::GetBaseViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_baseViewMatrix;

	return;
}

//==============================================================================
//  �֐���       RenderReflectionMatrix	
//  ����	         ���˗p��View�s��𐶐�����֐�
//------------------------------------------------------------------------------
//	����
//			float height		����
//	�߂�l
//          �Ȃ�
//==============================================================================
void CCamera::RenderReflectionMatrix(float fHeight)
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	//������̃x�N�g�����`����
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	//XMVECTOR�ւ̕ϊ�
	upVector = XMLoadFloat3(&up);

	//�J�����̈ʒu���x�N�g���ɃZ�b�g����
	//���˂̏ꍇ�AY���̈ʒu�𔽓]����
	position.x =  m_fPosX;
	position.y = -m_fPosY + (fHeight * 2.0f);
	position.z =  m_fPosZ;

	//XMVECTOR�ւ̕ϊ�
	positionVector = XMLoadFloat3(&position);

	//�J�����̌����Ă���ʒu��ݒ肷��
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	//XMVECTOR�ւ̕ϊ�
	lookAtVector = XMLoadFloat3(&lookAt);

	//yaw (Y��), pitch (X��), roll (Z��) �����W�A���ɕϊ�����
	pitch = m_fRotX * XM_PI / 180.0f;
	yaw   = m_fRotY * XM_PI / 180.0f;
	roll  = m_fRotZ * XM_PI / 180.0f;

	//yaw, pitch, roll�ŉ�]�s����쐬����
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	//lookAt�x�N�g���Ə�����x�N�g������]����
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	//�J�������ړ�����
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	//���˗p�̃r���[�s����쐬����
	m_reflectionViewMatrix = XMMatrixLookAtLH(positionVector, upVector, lookAtVector);

	return;
}

//==============================================================================
//  �֐���       GetReflectionViewMatrix	
//  ����	        ���˗p��View�s����Q�b�g����֐�
//------------------------------------------------------------------------------
//	����
//			XMMATRIX& reflectionMatrix          ����View�s��
//	�߂�l
//          �Ȃ�
//==============================================================================
void CCamera::GetReflectionViewMatrix(XMMATRIX& reflectionMatrix)
{
	reflectionMatrix = m_reflectionViewMatrix;

	return;
}

//******************************************************************************
//	End of file.
//******************************************************************************