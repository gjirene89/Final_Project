//************************************************************************//
//	SackBaseClass.cpp
//	2017-01-16
//	Irene Gersenowies
//************************************************************************//

//==============================================================================
//		�C���N���[�h
//==============================================================================
# include "SackBaseClass.h"
# include "SackStateBaseHeaders.h"
# include "Macros.h"
# include "HitBoxClass.h"
# include "HitSphereClass.h"
# include "ShaderManager.h"
# include "HitManager.h"
# include "MathUtility.h"
# include "StageClass.h"
//# include "CDirectxGraphics.h"
//# include "CStage.h"
//# include "CHit_Sphere.h"
//# include "CHit_Box.h"
//# include "Debug.h"
//# include "CPlayer.h"
//# include "mathutil.h"



//==============================================================================
//	�O���[�o���ϐ�
//==============================================================================
int CSackBase::m_noSack = 0;
CModel* CSackBase::m_body = nullptr;
CModel* CSackBase::m_hook = nullptr;

CTexture* CSackBase::m_colorTexture = nullptr;
CTexture* CSackBase::m_bumpTexture = nullptr;

//==============================================================================
//!	@fn		CSackBase
//!	@brief	�R�f�ׁ[�X�̃R���X�g���N�^
//!	@param	float posX		X���̈ʒu
//!	@param	float posY		Y���̈ʒu
//!	@retval	�Ȃ�
//! @note
//==============================================================================
CSackBase::CSackBase(float posX, float posY, GAMEOBJTYPE gObj) : CGameObjectBase(gObj)
{
	m_noId = ++m_noSack;
	m_animBody = nullptr;	

	//�ʒu�̏�����
	m_initPosition = { posX * BLOCK_SIZE, posY * BLOCK_SIZE + SACK_RADIUS, 0.0f };
	m_position = m_oldPosition = m_initPosition;

	m_rope = nullptr;
	m_orientation = { 0,0,0 };

	//�����蔻��
	m_hitCenter = new CHit_Box(SACK_RADIUS * 2.5, SACK_RADIUS * 2, SACK_RADIUS * 2, GAMEHIT_TYPE::HIT_SACK, this);
	m_hitLeft = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	m_hitRight = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	m_hitUp = new CHit_Box(SACK_RADIUS, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	m_hitDown = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	m_hitRightOut = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	m_hitLeftOut = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	m_hitUpOut = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
}

//==============================================================================
//!	@fn		�`CSackBase
//!	@brief	�R�f�x�[�X�̃f�X�g���N�^
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
CSackBase::~CSackBase()
{
	//if (rope != nullptr)	delete rope;

	//�����蔻��̃|�C���^���������
	if (m_hitCenter		!= nullptr)		delete m_hitCenter;
	if (m_hitRight		!= nullptr)		delete m_hitRight;
	if (m_hitLeft		!= nullptr)		delete m_hitLeft;
	if (m_hitDown		!= nullptr)		delete m_hitDown;
	if (m_hitUp			!= nullptr)		delete m_hitUp;
	if (m_hitRightOut	!= nullptr)		delete m_hitRightOut;
	if (m_hitLeftOut	!= nullptr)		delete m_hitLeftOut;
}

bool CSackBase::InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	bool result;

	//**************//
	// �@�R�f�̑́@�@	//
	//**************//
	m_body = new CModel[MODEL_MAX];
	if (!m_body)
	{
		return false;
	}

	result = m_body[MODEL_NORMAL].Initialize(device, "Resources/Model/Player/sack_normal.txt");
	if (!result)
	{
		return false;
	}

	result = m_body[MODEL_SQUASH].Initialize(device, "Resources/Model/Player/sack_squash.txt");
	if (!result)
	{
		return false;
	}

	result = m_body[MODEL_JUMP].Initialize(device, "Resources/Model/Player/sack_stretch_jump.txt");
	if (!result)
	{
		return false;
	}

	result = m_body[MODEL_MOVE_JUMP].Initialize(device, "Resources/Model/Player/sack_stretch_jump.txt");
	if (!result)
	{
		return false;
	}

	result = m_body[MODEL_MOVE_FALL].Initialize(device, "Resources/Model/Player/sack_stretch_land.txt");
	if (!result)
	{
		return false;
	}

	result = m_body[MODEL_DASH].Initialize(device, "Resources/Model/Player/sack_dash_stretch.txt");
	if (!result)
	{
		return false;
	}

	result = m_body[MODEL_IMPACT_FRONT].Initialize(device, "Resources/Model/Player/sack_squash_front.txt");
	if (!result)
	{
		return false;
	}

	result = m_body[MODEL_IMPACT_UP].Initialize(device, "Resources/Model/Player/sack_squash_up.txt");
	if (!result)
	{
		return false;
	}
	//*********************//
	// �@�A�j���t���̃��f��  //
	//*********************//
	m_animBody = new CModelAnimation;
	if (!m_animBody)
	{
		return false;
	}

	m_animBody->Initialize(device, &m_body[MODEL_NORMAL]);
	if (!result)
	{
		return false;
	}

	//****************//
	// �@�R�f�̃t�b�N	  //
	//****************//

	m_hook = new CModel;
	if (!m_hook)
	{
		return false;
	}

	result = m_hook->Initialize(device, "Resources/Model/hook.txt");
	if (!result)
	{
		return false;
	}

	//****************//
	//   �@�R�f�̕R    //
	//****************//

	if (m_rope)
	{
		result = m_rope->InitializeObject(device, deviceContext);
		if (!result)
		{
			return false;
		}
	}

	//****************//
	// �@�e�N�X�`��	  //
	//****************//

	m_colorTexture = new CTexture;
	if (!m_colorTexture)
	{
		return false;
	}

	result = m_colorTexture->Initialize(device, deviceContext, "Resources/Texture/sackColor.tga");
	if (!result)
	{
		return false;
	}

	m_bumpTexture = new CTexture;
	if (!m_bumpTexture)
	{
		return false;
	}

	result = m_bumpTexture->Initialize(device, deviceContext, "Resources/Texture/sackNormal.tga");
	if (!result)
	{
		return false;
	}
	return true;
}

void CSackBase::Shutdown(void)
{
	if (m_colorTexture != nullptr)
	{
		m_colorTexture->Shutdown();
		delete m_colorTexture;
		m_colorTexture = nullptr;
	}

	if (m_bumpTexture != nullptr)
	{
		m_bumpTexture->Shutdown();
		delete m_bumpTexture;
		m_bumpTexture = nullptr;
	}

	for (int i = 0; i < MODEL_MAX; i++)
	{
		m_body[i].Shutdown();
	}
	delete[] m_body;
	m_body = nullptr;

	if (m_hook != nullptr)
	{
		m_hook->Shutdown();
		delete m_hook;
		m_hook = nullptr;
	}

	if (m_rope != nullptr)
	{
		m_rope->Shutdown();
		delete m_rope;
		m_rope = nullptr;
	}

	return;
}

//==============================================================================
//!	@fn		Initialize
//!	@brief	�R�f�̏������֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::Initialize(void)
{
	//�ʒu�̏�����
	m_position = m_oldPosition = m_initPosition;
	m_impulse = { 0, 0, 0 };

	switch (m_looking)
	{
	case SACK_DIR_LEFT:
		m_initAngle = -LOOK_ANGLE;
		break;

	case SACK_DIR_RIGHT:
		m_initAngle = LOOK_ANGLE;
		break;
	}


	m_orientation = { cos(m_initAngle), 0.0f, -sin(m_initAngle) };

	CalculateWorldMatrix(m_matrix, m_orientation.x, m_orientation.y, m_orientation.z);
	//m_matrix = XMMatrixRotationY(m_initAngle);
	//D3DXMatrixRotationY(&matrix, initAngle);

	UpdateDisplacement();
	//��Ԃ̏�����
	m_state = m_state->GetState(SackStateBase::SACK_NORMAL);
	//�e���k���ɂ���
	m_parent = nullptr;
	m_child = nullptr;
	
	m_animBody->SetCurrent(&m_body[MODEL_NORMAL]);

	if (m_rope != nullptr)	m_rope->Initialize(m_matrix);
}

//==============================================================================
//!	@fn		Action
//!	@brief	�R�f�̏����֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::Action(void)
{
	//���̒l���R�s�[����
	m_oldPosition = m_position;
	m_oldImpulse = m_impulse;

	//���݂̏�Ԃ̏������Ăяo��
	m_state->Action(this);

	//�ړ�
	UpdateDisplacement();

	//�����蔻��f�[�^�X�V
	UpdateHit();
	
	if (m_rope != nullptr)
		m_rope->Action(m_matrix);
		
	if (m_child != nullptr)
		m_rope->LockEnd(m_child->GetHookPos());

}

//==============================================================================
//!	@fn		PostAction
//!	@brief	�R�f�̌㏈��
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::PostAction(void)
{
	if (m_rope != nullptr) m_rope->PostAction();
	m_state->PostAction(this);
}

//==============================================================================
//!	@fn		MoveRight
//!	@brief	�E�ֈړ�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::MoveRight(void)
{
	m_state = m_state->GetState(SackStateBase::SACK_MOVE);

	m_impulse.x = MOVE_FORCE;
	m_impulse.y = JUMP_FORCE;

	if (HitManager::CheckStage(m_hitRightOut))
	{
		m_impulse.y = CLIMB_FORCE;
		return;
	}

	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(m_hitRightOut, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr && tempObj != m_parent)
	{
		m_impulse.y = CLIMB_FORCE;
	}
}

//==============================================================================
//!	@fn		MoveLeft
//!	@brief	�E�ֈړ�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::MoveLeft(void)
{
	m_state = m_state->GetState(SackStateBase::SACK_MOVE);

	m_impulse.x = -MOVE_FORCE;
	m_impulse.y = JUMP_FORCE;

	if (HitManager::CheckStage(m_hitLeftOut))
	{
		m_impulse.y = CLIMB_FORCE;
		return;
	}

	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(m_hitLeftOut, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr && tempObj != m_parent)
	{
		m_impulse.y = CLIMB_FORCE;
	}

}

//==============================================================================
//!	@fn		Jump
//!	@brief	�W�����v
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::Jump(void)
{
	m_state = m_state->GetState(SackStateBase::SACK_JUMP);
	m_impulse.x = 0;
	m_impulse.y = CLIMB_FORCE;
}

//==============================================================================
//!	@fn		Pull
//!	@brief	�q�����Ă���ꍇ�A����������
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::Pull(void)
{
	if (m_parent == nullptr) return;

	float angle = CalculateAngle(m_position, m_parent->GetWorldPos());
	float force = GetRopePullForce();
	SackStateBase::SACK_STATE state = m_parent->GetState()->GetStateName();

	if (angle < -90.0f || angle > 110.0f)
	{
		ClearChain();
		return;
	}

	if (CalculateDistance(m_position, m_parent->GetWorldPos()) < ROPE_LENGHT)	return;

	switch (m_hookDir)
	{
	case SACK_DIR_RIGHT:
		break;

	case SACK_DIR_LEFT:
		if (state == SackStateBase::SACK_DASH)
		{
			SetState(SackStateBase::SACK_DASH);
			m_impulse.x = DASH_FORCE;
			return;
		}
		if (angle > 70.0f && angle < 100.f)	Jump();
		else MoveRight();
		break;
	}


	switch (state)
	{
	case SackStateBase::SACK_JUMP:
		if (CalculateDistance(m_position, m_parent->GetWorldPos()) > SACK_RADIUS * 3.0f)
		{
			if (angle > 50.0f && angle < 120.f)
				Jump();
			else
				MoveRight();
		}
		break;

	case SackStateBase::SACK_NORMAL:
	case SackStateBase::SACK_MOVE:
		if ((CalculateDistance(m_position, m_parent->GetWorldPos()) > SACK_RADIUS * 3.0f &&
			m_parent->GetImpulse().x > 0 && angle < 70.0f) ||
			(CalculateDistance(m_position, m_parent->GetWorldPos()) > SACK_RADIUS * 3.0f &&
				m_parent->GetImpulse().x > 0 && angle < 90.0f))
			MoveRight();
		break;

	case SackStateBase::SACK_DASH:
		if (force > 40.0f)
		{
			SetState(SackStateBase::SACK_DASH);
			m_impulse.x = DASH_FORCE;
		}
		break;
	}
}

//==============================================================================
//!	@fn		Chain
//!	@brief	�R�f���q����֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::Chain(void)
{
	if (m_parent != nullptr)	return;

	CSackBase* sack = (CSackBase*)HitManager::CheckHit(m_hitUpOut, GAMEHIT_TYPE::HIT_SACK);

	if (sack == nullptr)	return;

	if (sack->GetStringDir() == m_hookDir && sack->m_child == nullptr)
	{
		m_parent = sack;
		m_parent->m_child = this;
	}
}

void CSackBase::ClearChain(void)
{
	if (m_stringDir == SACK_DIR_NONE)	return;

	m_parent->m_rope->ClearLock();
	m_parent->m_child = nullptr;
	m_parent = nullptr;
}

//==============================================================================
//!	@fn		Slide
//!	@brief	���̏�Ɋ���
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::Slide(void)
{
	if (m_impulse.x > FRICTION)
		m_impulse.x -= FRICTION;

	else if (m_impulse.x < -FRICTION)
		m_impulse.x += FRICTION;

	else m_impulse.x = 0;
}

//==============================================================================
//!	@fn		Dash
//!	@brief	�_�b�V���[�֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::Dash(void)
{
	//�E����Ԃ���������
	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(m_hitRight, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr)
	{
		if (tempObj->GetState()->GetStateName() == SackStateBase::SACK_DASH)
		{
			m_impulse.x = -DASH_FORCE;
			m_state = m_state->GetState(SackStateBase::SACK_DASH);
		}
		return;
	}

	//������Ԃ�����ꍇ
	tempObj = (CSackBase*)HitManager::CheckHit(m_hitLeft, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr)
	{
		if (tempObj->GetState()->GetStateName() == SackStateBase::SACK_DASH)
		{
			m_impulse.x = DASH_FORCE;
			m_state = m_state->GetState(SackStateBase::SACK_DASH);
		}
		return;
	}

}
//==============================================================================
//!	@fn		HitWall
//!	@brief	�ǂƓ�����Ƃ�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::HitWall(void)
{
	//�ǂɂ͂܂��Ă���ꍇ
	if (abs(m_impulse.x) < 1.0f)
		LeaveWall();
	else
	{
		switch (m_looking)
		{
		case SACK_DIR_LEFT:
			if (HitManager::CheckStage(m_hitLeft) || HitManager::CheckHit(m_hitLeft, GAMEHIT_TYPE::HIT_SACK))
			{
				ResetPositionX();
			}
			break;

		case SACK_DIR_RIGHT:
			if (HitManager::CheckStage(m_hitRight) || HitManager::CheckHit(m_hitRight, GAMEHIT_TYPE::HIT_SACK))
			{
				ResetPositionX();
			}
			break;
		}
	}
}

//==============================================================================
//!	@fn		LeaveWall
//!	@brief	�ǂɂ͂܂�����A�ǂ���o��
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::LeaveWall(void)
{
	if (HitManager::CheckStage(m_hitCenter) || HitManager::CheckHit(m_hitCenter, GAMEHIT_TYPE::HIT_SACK))
	{
		if (HitManager::CheckStage(m_hitRight) || HitManager::CheckHit(m_hitRight, GAMEHIT_TYPE::HIT_SACK))
			m_position.x -= 0.25f;
		else if (HitManager::CheckStage(m_hitLeft) || HitManager::CheckHit(m_hitLeft, GAMEHIT_TYPE::HIT_SACK))
			m_position.x += 0.25f;
	}
}


//==============================================================================
//!	@fn		CleanNumbers
//!	@brief	�ʒu���X�e�[�W�ɃX�i�b�v����֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::CleanNumbers(void)
{
	CStage::CleanNumbers(nullptr, &m_position.y);
	m_position.y += SACK_RADIUS;
}

//==============================================================================
//!	@fn		ResetPositionX
//!	@brief	X���̈ʒu�����̒l�ɖ߂�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::ResetPositionX(void)
{
	m_position.x = m_oldPosition.x;
}

//==============================================================================
//!	@fn		ResetPositionY
//!	@brief	Y���̈ʒu�����̒l�ɖ߂�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::ResetPositionY(void)
{
	m_position.y = m_oldPosition.y;
}

//==============================================================================
//!	@fn		GetParent
//!	@brief	�e��߂�
//!	@param	�Ȃ�
//!	@retval	C3DObject*  �e�ւ̃|�C���^
//==============================================================================
CSackBase* CSackBase::GetParent(void)
{
	return m_parent;
}

//==============================================================================
//!	@fn		GetImpulse
//!	@brief	�e�݂�߂��֐�
//!	@param	�Ȃ�
//!	@retval	D3DXVECTOR3	oldImpulse		�I�u�W�F�N�g�̒e��
//==============================================================================
XMFLOAT3 CSackBase::GetImpulse(void)
{
	return m_oldImpulse;
}

//==============================================================================
//!	@fn		GetRopePullForce
//!	@brief	�����������
//!	@param	�Ȃ�
//!	@retval	float	��
//==============================================================================
float CSackBase::GetRopePullForce(void)
{
	if (m_parent == nullptr)
		return 0;
	return m_parent->m_rope->GetPullForce();
	//return 0;
}

//==============================================================================
//!	@fn		GetRopePullAngle
//!	@brief	��������ꂽ�p�x
//!	@param	�Ȃ�
//!	@retval	float	�p�x�i���W�A���j
//==============================================================================
float CSackBase::GetRopePullAngle(void)
{
	if (m_parent == nullptr)
		return 0;

	return m_parent->m_rope->GetPullAngle();
	//return 0;
}

//==============================================================================
//!	@fn		GetStringDir
//!	@brief	�R�̌�����Ԃ��֐�
//!	@param	�Ȃ�
//!	@retval	SACK_DIR		�R�̌���
//!	@note	
//==============================================================================
CSackBase::SACK_DIR CSackBase::GetStringDir(void)
{
	return m_stringDir;
}

//==============================================================================
//!	@fn		GetLookingDir
//!	@brief	�����Ă��������Ԃ��֐�
//!	@param	�Ȃ�
//!	@retval	SACK_DIR		�����Ă������
//!	@note	
//==============================================================================
CSackBase::SACK_DIR CSackBase::GetLookingDir(void)
{
	return m_looking;
}

//==============================================================================
//!	@fn		GetHookDir
//!	@brief	�t�b�N�̌�����Ԃ��֐�
//!	@param	�Ȃ�
//!	@retval	SACK_DIR		�t�b�N�̌���
//!	@note	
//==============================================================================
CSackBase::SACK_DIR CSackBase::GetHookDir(void)
{
	return m_hookDir;
}
//==============================================================================
//!	@fn		AddImpulse
//!	@brief	�e�݂𑝂₷�֐�
//!	@param	float impulseX		x���̒e��
//!	@param	float impulseY		y���̒e��
//!	@retval	�Ȃ�
//==============================================================================
void CSackBase::AddImpulse(float impulseX, float impulseY)
{
	m_impulse.x += impulseX;
	m_impulse.y += impulseY;
}

//==============================================================================
//!	@fn		SetImpulseX
//!	@brief	X���̈ړ��͂�ݒ肷��
//!	@param	float impulseX		x���̗�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::SetImpulseX(float impulseX)
{
	m_impulse.x = impulseX;
}

//==============================================================================
//!	@fn		SetImpulseY
//!	@brief	Y���̈ړ��͂�ݒ肷��
//!	@param	float impulseY		y���̗�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::SetImpulseY(float impulseY)
{
	m_impulse.y = impulseY;
}

//==============================================================================
//!	@fn		SetState
//!	@brief	��Ԃ�ݒ肷��
//!	@param	PlayerState* state		��Ԃւ̃|�C���^
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::SetState(SackStateBase::SACK_STATE stateName)
{
	m_state = m_state->GetState(stateName);

	//�J�n�֐����Ăяo��
	m_state->Enter(this);
}

//==============================================================================
//!	@fn		UpdateDisplacement
//!	@brief�@�ړ��X�V
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::UpdateDisplacement(void)
{
	//�t���[���̃X�s�[�h�𗎂Ƃ�
	m_position.y += m_impulse.y / 15.0f;
	m_position.x += m_impulse.x / 15.0f;
}


//==============================================================================
//!	@fn		UpdateHit
//!	@brief	�����蔻��̐ݒ�֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
void CSackBase::UpdateHit(void)
{
	m_hitCenter->UpdatePosition(m_position);
	m_hitLeft->UpdatePosition(    { m_position.x - SACK_RADIUS,     m_position.y,                   m_position.z });
	m_hitRight->UpdatePosition(   { m_position.x + SACK_RADIUS,     m_position.y,                   m_position.z });
	m_hitUp->UpdatePosition(      { m_position.x,                   m_position.y + SACK_RADIUS,     m_position.z });
	m_hitDown->UpdatePosition(    { m_position.x,                   m_position.y - SACK_RADIUS,     m_position.z });
	m_hitRightOut->UpdatePosition({ m_position.x + SACK_RADIUS * 2, m_position.y,                   m_position.z });
	m_hitLeftOut->UpdatePosition( { m_position.x - SACK_RADIUS * 2, m_position.y,                   m_position.z });
	m_hitUpOut->UpdatePosition(   { m_position.x,                   m_position.y + SACK_RADIUS * 2, m_position.z });

	HitManager::AddHit(m_hitCenter);
	HitManager::AddHit(m_hitRight);
	HitManager::AddHit(m_hitLeft);
	HitManager::AddHit(m_hitUp);
	HitManager::AddHit(m_hitDown);
	HitManager::AddHit(m_hitRightOut);
	HitManager::AddHit(m_hitLeftOut);
	HitManager::AddHit(m_hitUpOut);

}

//==============================================================================
//!	@fn		RenderDebug
//!	@brief	�f�o�b�O����`�悷��֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::RenderDebug(void)
{
	/*
	if (CDebug::GetIsHidden() || !CDebug::displayStats)	return;

	int posX = 300 * (noId - 1);
	int posY = 0;

	char text[256];

	CDebug::GetFont()->DrawTextA(posX, posY, nameId);

	CDebug::GetFont()->DrawTextA(posX, posY + 30, state_->RenderDebug());

	sprintf_s(text, "Position X : %f", position.x);
	CDebug::GetFont()->DrawTextA(posX, posY + 60, text);

	sprintf_s(text, "Position Y : %f", position.y);
	CDebug::GetFont()->DrawTextA(posX, posY + 90, text);

	if (parent != nullptr)
	{
		CDebug::GetFont()->DrawTextA(posX, posY + 120, "isChained : true");
		sprintf_s(text, "PullForce : %f", GetRopePullForce());
		CDebug::GetFont()->DrawTextA(posX, posY + 150, text);
		sprintf_s(text, "PullAngle(deg) : %.0f", CalculateAngle(position, parent->GetWorldPos()));
		CDebug::GetFont()->DrawTextA(posX, posY + 180, text);
	}
	else
		CDebug::GetFont()->DrawTextA(posX, posY + 120, "isChained : false");
		*/
}

SackStateBase* CSackBase::GetState(void)
{
	return m_state;
}

XMFLOAT3 CSackBase::GetHookPos(void)
{
	XMMATRIX  hookMatrix, transMatrix, rotMatrix;
	XMFLOAT4X4 hookMatTemp;

	hookMatrix = XMMatrixTranslation(0, SACK_RADIUS, 7);
	transMatrix = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	rotMatrix = XMMatrixRotationY(m_initAngle);

	hookMatrix = hookMatrix * rotMatrix * transMatrix;

	XMStoreFloat4x4(&hookMatTemp, hookMatrix);

	return{ hookMatTemp._41, hookMatTemp._42, hookMatTemp._43 };
}


void CSackBase::StartAnimation(SACK_MODELS modelName, int nFrames)
{
	m_animBody->SetTarget(&m_body[modelName], nFrames);
}
//******************************************************************************
//	End of file.
//******************************************************************************
