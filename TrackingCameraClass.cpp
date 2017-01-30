//************************************************************************//
//	TrackingCameraClass.cpp
//	2017-01-30
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//   �C���N���[�h
//=======================================================================//
#include "TrackingCameraClass.h"
#include "MathUtility.h"

//=======================================================================//
//   �}�N���萔
//=======================================================================//
# define CAMERA_THRESHOLD (10.0f)

//==============================================================================
//  �֐���        CTrackingCamera	
//  ����          �ǐՃJ�����N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CTrackingCamera::CTrackingCamera() : CCamera()
{
	m_velocity = { 0.0f, 0.0f, 0.0f };

	m_Target = nullptr;
}

//==============================================================================
//  �֐���        CTrackingCamera	
//  ����          �ǐՃJ�����N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          CTrackingCamera& other			CTrackingCamera�̃C���X�^���X
//	�߂�l
//          �Ȃ�
//==============================================================================
CTrackingCamera::CTrackingCamera(const CTrackingCamera& other)
{
	//��
}

//==============================================================================
//  �֐���        �`CTrackingCamera	
//  ����          �ǐՃJ�����N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CTrackingCamera::~CTrackingCamera()
{
	m_Target = nullptr;
}

void CTrackingCamera::Initialize()
{
	if (!m_Target) return;

	XMFLOAT3 targetPos;
	targetPos = m_Target->GetWorldPos();

	m_velocity = { 0.0f, 0.0f, 0.0f };

	m_fPosX = m_targetX = targetPos.x;
	m_fPosY = m_targetY = targetPos.y;
	m_targetZ = m_fPosZ;
	
}

//==============================================================================
//  �֐���        Action
//  ����			�ǐՃJ�����̏����֐�
//------------------------------------------------------------------------------
//	����
//			�Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
void CTrackingCamera::Action()
{
	if (!m_Target)	return;

	UpdateTargetPosition();

	m_fPosX = m_targetX;
	//UpdateCameraPosition();
}

void CTrackingCamera::UpdateTargetPosition()
{
	XMFLOAT3 targetPos;

	targetPos = m_Target->GetWorldPos();

	m_targetX = targetPos.x;
	m_targetY = targetPos.y;
	m_targetZ = targetPos.z;

}

void CTrackingCamera::UpdateCameraPosition()
{
	float dist, k;
	XMFLOAT3 force, orientation;

	k = 1.0f;

	dist = CalculateDistance({ m_fPosX, m_fPosY, 0.0f }, { m_targetX, m_targetY, 0.0f }, orientation);
	dist -= CAMERA_THRESHOLD;

	if (dist > 0.0f)
	{
  		force.x = -k * dist * orientation.x;
		force.y = -k * dist * orientation.y;
		force.z = -k * dist * orientation.z;
		
		//���x�𑫂�
		m_velocity.x += force.x / 60.0f;
		m_velocity.y += force.y / 60.0f;
		m_velocity.z += force.z / 60.0f;
		
		//�������~�܂�
		if (m_velocity.x < 0.01 && m_velocity.x > -0.01f)
			m_velocity.x = 0;
		
		if (m_velocity.y < 0.01 && m_velocity.y > -0.01f)
			m_velocity.y = 0;
		
		if (m_velocity.z < 0.01 && m_velocity.z > -0.01f)
			m_velocity.z = 0;
		
		m_fPosX += m_velocity.x;
		m_fPosY += m_velocity.y;
	//	m_fPosZ += m_velocity.z;

	}
	else
	{
		m_velocity.x -= 0.1f;
		m_velocity.y -= 0.1f;
		m_velocity.z -= 0.1f;

		if (m_velocity.x < 0.01 && m_velocity.x > -0.01f)
			m_velocity.x = 0;

		if (m_velocity.y < 0.01 && m_velocity.y > -0.01f)
			m_velocity.y = 0;

		if (m_velocity.z < 0.01 && m_velocity.z > -0.01f)
			m_velocity.z = 0;
	}
}

//==============================================================================
//  �֐���       SetTarget
//  ����			�ǐՃJ�����̃^�[�Q�b�g���Z�b�g
//------------------------------------------------------------------------------
//	����
//			CGameObjectBase*		�^�[�Q�b�g�̃|�C���^
//	�߂�l
//          �Ȃ�
//==============================================================================
void CTrackingCamera::SetTarget(CGameObjectBase* target)
{
	m_Target = target;
}