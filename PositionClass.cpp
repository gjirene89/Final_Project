//************************************************************************//
//	PositionClass.cpp
//	2016-11-23
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
#include "PositionClass.h"

//==============================================================================
//  �֐���        CPosition	
//  ����          CPosition�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CPosition::CPosition()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_frameTime = 0.0f;

	m_forwardSpeed = 0.0f;
	m_backwardSpeed = 0.0f;
	m_upwardSpeed = 0.0f;
	m_downwardSpeed = 0.0f;
	m_leftTurnSpeed = 0.0f;
	m_rightTurnSpeed = 0.0f;
	m_lookUpSpeed = 0.0f;
	m_lookDownSpeed = 0.0f;
	m_rightwardSpeed = 0.0f;
	m_leftwardSpeed = 0.0f;
}

//==============================================================================
//  �֐���        CPosition	
//  ����          CPosition�N���X�̃R���X�g���N�^
//------------------------------------------------------------------------------
//	����
//          CPosition& other			CPosition�̃C���X�^���X
//	�߂�l
//          �Ȃ�
//==============================================================================
CPosition::CPosition(const CPosition& other)
{
	//��
}

//==============================================================================
//  �֐���        �`CPosition	
//  ����          CPosition�N���X�̃f�X�g���N�^
//------------------------------------------------------------------------------
//	����
//          �Ȃ�
//	�߂�l
//          �Ȃ�
//==============================================================================
CPosition::~CPosition()
{
	//��
}

//==============================================================================
//  �֐���        SetPosition
//  ����          �ʒu���Z�b�g����
//------------------------------------------------------------------------------
//	����
//          float         x           �ʒu�iX���j
//          float         y           �ʒu�iY���j
//          float         z           �ʒu�iZ���j
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;

	return;
}

//==============================================================================
//  �֐���        SetRotation
//  ����          ��]�x���Z�b�g����
//------------------------------------------------------------------------------
//	����
//          float         x           ��]�x�iX���j
//          float         y           ��]�x�iY���j
//          float         z           ��]�x�iZ���j
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;

	return;
}

//==============================================================================
//  �֐���        GetPosition
//  ����          �ʒu���Q�b�g����
//------------------------------------------------------------------------------
//	����
//          float&         x           �ʒu�iX���j
//          float&         y           �ʒu�iY���j
//          float&         z           �ʒu�iZ���j
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;

	return;
}

//==============================================================================
//  �֐���        GetRotation
//  ����          ��]�x���Q�b�g����
//------------------------------------------------------------------------------
//	����
//          float&         x           ��]�x�iX���j
//          float&         y           ��]�x�iY���j
//          float&         z           ��]�x�iZ���j
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;

	return;
}

//==============================================================================
//  �֐���        SetFrameTime
//  ����          1�t���[���̎��Ԃ�ݒ肷��
//------------------------------------------------------------------------------
//	����
//          float         time         �P�t���[���̕b��
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}

//==============================================================================
//  �֐���        MoveForwards
//  ����          �O�ړ�
//------------------------------------------------------------------------------
//	����
//          bool         keydown         �L�[��������Ă��邩�ǂ���
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::MoveForwards(bool keydown)
{
	float radians;

	//�L�[�������ꂽ��A�X�s�[�h������
	if (keydown)
	{
		m_forwardSpeed += m_frameTime * 0.001f;

		if (m_forwardSpeed > (m_frameTime * 0.03f))
		{
			m_forwardSpeed = m_frameTime * 0.03f;
		}
	}
	//������Ă�����΁A�X�s�[�h������
	else
	{
		m_forwardSpeed -= m_frameTime * 0.0007f;

		if (m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}

	radians = m_rotationY * 0.0174532925f;

	//�ʒu�X�V
	m_positionX += sinf(radians) * m_forwardSpeed;
	m_positionZ += cosf(radians) * m_forwardSpeed;

	return;
}

//==============================================================================
//  �֐���        MoveBackwards
//  ����          ���ړ�
//------------------------------------------------------------------------------
//	����
//          bool         keydown         �L�[��������Ă��邩�ǂ���
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::MoveBackwards(bool keydown)
{
	float radians;

	//�L�[�������ꂽ��A�X�s�[�h������
	if (keydown)
	{
		m_backwardSpeed += m_frameTime * 0.001f;

		if (m_backwardSpeed > (m_frameTime * 0.03f))
		{
			m_backwardSpeed = m_frameTime * 0.03f;
		}
	}
	//������Ă�����΁A�X�s�[�h������
	else
	{
		m_backwardSpeed -= m_frameTime * 0.0007f;

		if (m_backwardSpeed < 0.0f)
		{
			m_backwardSpeed = 0.0f;
		}
	}

	radians = m_rotationY * 0.0174532925f;

	//�ʒu�X�V
	m_positionX -= sinf(radians) * m_backwardSpeed;
	m_positionZ -= cosf(radians) * m_backwardSpeed;

	return;
}

//==============================================================================
//  �֐���        MoveUpwards
//  ����          ��ړ�
//------------------------------------------------------------------------------
//	����
//          bool         keydown         �L�[��������Ă��邩�ǂ���
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::MoveUpwards(bool keydown)
{
	//�L�[�������ꂽ��A�X�s�[�h������
	if (keydown)
	{
		m_upwardSpeed += m_frameTime * 0.003f;

		if (m_upwardSpeed > (m_frameTime * 0.03f))
		{
			m_upwardSpeed = m_frameTime * 0.03f;
		}
	}
	//������Ă�����΁A�X�s�[�h������
	else
	{
		m_upwardSpeed -= m_frameTime * 0.002f;

		if (m_upwardSpeed < 0.0f)
		{
			m_upwardSpeed = 0.0f;
		}
	}

	//�ʒu�X�V
	m_positionY += m_upwardSpeed;

	return;
}

//==============================================================================
//  �֐���        MoveDownwards
//  ����          ���ړ�
//------------------------------------------------------------------------------
//	����
//          bool         keydown         �L�[��������Ă��邩�ǂ���
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::MoveDownwards(bool keydown)
{
	//�L�[�������ꂽ��A�X�s�[�h������
	if (keydown)
	{
		m_downwardSpeed += m_frameTime * 0.003f;

		if (m_downwardSpeed > (m_frameTime * 0.03f))
		{
			m_downwardSpeed = m_frameTime * 0.03f;
		}
	}
	//������Ă�����΁A�X�s�[�h������
	else
	{
		m_downwardSpeed -= m_frameTime * 0.002f;

		if (m_downwardSpeed < 0.0f)
		{
			m_downwardSpeed = 0.0f;
		}
	}

	//�ʒu�X�V
	m_positionY -= m_downwardSpeed;

	return;
}

//==============================================================================
//  �֐���        MoveLeftwards
//  ����          ���ړ�
//------------------------------------------------------------------------------
//	����
//          bool         keydown         �L�[��������Ă��邩�ǂ���
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::MoveLeftwards(bool keydown)
{
	float radians;

	//�L�[�������ꂽ��A�X�s�[�h������
	if (keydown)
	{
		m_leftwardSpeed += m_frameTime * 0.003f;

		if (m_leftwardSpeed > (m_frameTime * 0.03f))
		{
			m_leftwardSpeed = m_frameTime * 0.03f;
		}
	}
	//������Ă�����΁A�X�s�[�h������
	else
	{
		m_leftwardSpeed -= m_frameTime * 0.002f;

		if (m_leftwardSpeed < 0.0f)
		{
			m_leftwardSpeed = 0.0f;
		}
	}

	radians = m_rotationY * 0.0174532925f;
	//�ʒu�X�V
	m_positionX -= cosf(radians) * m_leftwardSpeed;
	m_positionZ -= sinf(radians) * m_leftwardSpeed;


	return;
}

//==============================================================================
//  �֐���        MoveRightwards
//  ����          �E�ړ�
//------------------------------------------------------------------------------
//	����
//          bool         keydown         �L�[��������Ă��邩�ǂ���
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::MoveRightwards(bool keydown)
{
	float radians;

	//�L�[�������ꂽ��A�X�s�[�h������
	if (keydown)
	{
		m_rightwardSpeed += m_frameTime * 0.003f;

		if (m_rightwardSpeed > (m_frameTime * 0.03f))
		{
			m_rightwardSpeed = m_frameTime * 0.03f;
		}
	}
	//������Ă�����΁A�X�s�[�h������
	else
	{
		m_rightwardSpeed -= m_frameTime * 0.002f;

		if (m_rightwardSpeed < 0.0f)
		{
			m_rightwardSpeed = 0.0f;
		}
	}

	radians = m_rotationY * 0.0174532925f;
	//�ʒu�X�V
	m_positionX += cosf(radians) * m_rightwardSpeed;
	m_positionZ += sinf(radians) * m_rightwardSpeed;

	return;
}

//==============================================================================
//  �֐���        TurnLeft
//  ����          ����]
//------------------------------------------------------------------------------
//	����
//          bool         keydown         �L�[��������Ă��邩�ǂ���
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::TurnLeft(bool keydown)
{
	//�L�[�������ꂽ��A��]�X�s�[�h������
	if (keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.01f;
		if (m_leftTurnSpeed > (m_frameTime * 0.15f))
		{
			m_leftTurnSpeed = m_frameTime * 0.15f;

		}
	}
	//������Ă�����΁A��]�X�s�[�h������
	else
	{
		m_leftTurnSpeed -= m_frameTime * 0.005f;

		if (m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	//��]�X�V
	m_rotationY -= m_leftTurnSpeed;
	if (m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}

	return;
}

//==============================================================================
//  �֐���        TurnRight
//  ����          �E��]
//------------------------------------------------------------------------------
//	����
//          bool         keydown         �L�[��������Ă��邩�ǂ���
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::TurnRight(bool keydown)
{
	//�L�[�������ꂽ��A��]�X�s�[�h������
	if (keydown)
	{
		m_rightTurnSpeed += m_frameTime * 0.01f;
		if (m_rightTurnSpeed > (m_frameTime * 0.15f))
		{
			m_rightTurnSpeed = m_frameTime * 0.15f;

		}
	}
	//������Ă�����΁A��]�X�s�[�h������
	else
	{
		m_rightTurnSpeed -= m_frameTime * 0.005f;

		if (m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	//��]�X�V
	m_rotationY += m_rightTurnSpeed;
	if (m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}

	return;

}

//==============================================================================
//  �֐���        TurnUp
//  ����          ���]
//------------------------------------------------------------------------------
//	����
//          bool         keydown         �L�[��������Ă��邩�ǂ���
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::TurnUp(bool keydown)
{
	//�L�[�������ꂽ��A��]�X�s�[�h������
	if (keydown)
	{
		m_lookUpSpeed += m_frameTime * 0.01f;
		if (m_lookUpSpeed > (m_frameTime * 0.15f))
		{
			m_lookUpSpeed = m_frameTime * 0.15f;

		}
	}
	//������Ă�����΁A��]�X�s�[�h������
	else
	{
		m_lookUpSpeed -= m_frameTime * 0.005f;

		if (m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	//��]�X�V
	m_rotationX -= m_lookUpSpeed;
	if (m_rotationX > 90.0f)
	{
		m_rotationX = 90.0f;
	}

	return;
}

//==============================================================================
//  �֐���        TurnDown
//  ����          ����]
//------------------------------------------------------------------------------
//	����
//          bool         keydown         �L�[��������Ă��邩�ǂ���
//	�߂�l
//          �Ȃ�
//==============================================================================
void CPosition::TurnDown(bool keydown)
{
	//�L�[�������ꂽ��A��]�X�s�[�h������
	if (keydown)
	{
		m_lookDownSpeed += m_frameTime * 0.01f;
		if (m_lookDownSpeed > (m_frameTime * 0.15f))
		{
			m_lookDownSpeed = m_frameTime * 0.15f;

		}
	}
	//������Ă�����΁A��]�X�s�[�h������
	else
	{
		m_lookDownSpeed -= m_frameTime * 0.005f;

		if (m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}

	//��]�X�V
	m_rotationX += m_lookDownSpeed;
	if (m_rotationX < -90.0f)
	{
		m_rotationX = -90.0f;
	}

	return;
}

//******************************************************************************
//	End of file.
//******************************************************************************