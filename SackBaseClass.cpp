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
# include "ShaderManagerClass.h"
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
int CSackBase::noSack = 0;

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
	noId = ++noSack;

	//�F�ݒ�
	//InitMaterial();

	//�ʒu�̏�����
	initPosition = { posX * BLOCK_SIZE, posY * BLOCK_SIZE + SACK_RADIUS, 0.0f };
	position = oldPosition = initPosition;

	//rope = nullptr;
	orientation = { 0,0,0 };

	//�����蔻��
	hitCenter = new CHit_Box(SACK_RADIUS * 2.5, SACK_RADIUS * 2, SACK_RADIUS * 2, GAMEHIT_TYPE::HIT_SACK, this);
	hitLeft = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	hitRight = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	hitUp = new CHit_Box(SACK_RADIUS, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	hitDown = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	hitRightOut = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	hitLeftOut = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
	hitUpOut = new CHit_Box(2, 2, 2, GAMEHIT_TYPE::HIT_SUPPORT, this);
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
	if (hitCenter != nullptr)		delete hitCenter;
	if (hitRight != nullptr)		delete hitRight;
	if (hitLeft != nullptr)		delete hitLeft;
	if (hitDown != nullptr)		delete hitDown;
	if (hitUp != nullptr)		delete hitUp;
	if (hitRightOut != nullptr)		delete hitRightOut;
	if (hitLeftOut != nullptr)		delete hitLeftOut;
}

//==============================================================================
//!	@fn		Init
//!	@brief	�R�f�̏������֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::Initialize(void)
{
	//�ʒu�̏�����
	position = oldPosition = initPosition;
	impulse = { 0, 0, 0 };

	m_matrix = XMMatrixRotationY(initAngle);
	//D3DXMatrixRotationY(&matrix, initAngle);

	XMFLOAT4X4 tempMatrix;

	XMStoreFloat4x4(&tempMatrix, m_matrix);

	//�����Ă������
	orientation.x = tempMatrix._11;
	orientation.y = tempMatrix._12;
	orientation.z = tempMatrix._13;

	UpdateDisplacement();
	//��Ԃ̏�����
	state_ = state_->GetState(SackStateBase::SACK_NORMAL);
	//�e���k���ɂ���
	parent = nullptr;
	child_ = nullptr;

//	if (rope != nullptr)	rope->Init(matrix);
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
	oldPosition = position;
	oldImpulse = impulse;

	//���݂̏�Ԃ̏������Ăяo��
	state_->Action(this);

	//�ړ�
	UpdateDisplacement();

	//�����蔻��f�[�^�X�V
	UpdateHit();
	/*
	if (rope != nullptr)
		rope->Action(matrix);
		
	if (child_ != nullptr)
		rope->LockEnd(child_->GetHookPos());
*/
}

//==============================================================================
//!	@fn		Render
//!	@brief	�R�f�̕`��֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	if (!m_model)
		return;

	CalculateWorldMatrix(worldMatrix);
	m_model->Render(deviceContext);

	CShaderManager::getInstance().RenderTextureShader(deviceContext, m_model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_model->GetColorTexture());

	//if (rope != nullptr) rope->Render();

	//RenderDebug();


	//C3DObject::Render();

	/*
	if (CDebug::displayAxis && !CDebug::GetIsHidden())
		RenderAxis();
		*/
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
	//if (rope != nullptr) rope->PostAction();
	state_->PostAction(this);
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
	state_ = state_->GetState(SackStateBase::SACK_MOVE);

	impulse.x = MOVE_FORCE;
	impulse.y = JUMP_FORCE;

	if (HitManager::CheckStage(hitRightOut))
	{
		impulse.y = CLIMB_FORCE;
		return;
	}

	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(hitRightOut, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr && tempObj != parent)
	{
		impulse.y = CLIMB_FORCE;
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
	state_ = state_->GetState(SackStateBase::SACK_MOVE);

	impulse.x = -MOVE_FORCE;
	impulse.y = JUMP_FORCE;

	if (HitManager::CheckStage(hitLeftOut))
	{
		impulse.y = CLIMB_FORCE;
		return;
	}

	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(hitLeftOut, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr && tempObj != parent)
	{
		impulse.y = CLIMB_FORCE;
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
	state_ = state_->GetState(SackStateBase::SACK_JUMP);
	impulse.x = 0;
	impulse.y = CLIMB_FORCE;
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
	if (parent == nullptr) return;

	float angle = CalculateAngle(position, parent->GetWorldPos());
	float force = GetRopePullForce();
	SackStateBase::SACK_STATE state = parent->GetState()->GetStateName();

	if (angle < -90.0f || angle > 110.0f)
	{
		ClearChain();
		return;
	}

	//if (CalculateDistance(position, parent->GetWorldPos()) < ROPE_LENGHT)	return;

	//switch (hookDir)
	//{
	//case SACK_DIR_RIGHT:
	//	break;

	//case SACK_DIR_LEFT:
	//	if (state == SackStateBase::SACK_DASH)
	//	{
	//		SetState(SackStateBase::SACK_DASH);
	//		impulse.x = DASH_FORCE;
	//		return;
	//	}
	//	if (angle > 70.0f && angle < 100.f)	Jump();
	//	else MoveRight();
	//	break;
	//}


	switch (state)
	{
	case SackStateBase::SACK_JUMP:
		if (CalculateDistance(position, parent->GetWorldPos()) > SACK_RADIUS * 3.0f)
		{
			if (angle > 50.0f && angle < 120.f)
				Jump();
			else
				MoveRight();
		}
		break;

	case SackStateBase::SACK_NORMAL:
	case SackStateBase::SACK_MOVE:
		if ((CalculateDistance(position, parent->GetWorldPos()) > SACK_RADIUS * 3.0f &&
			parent->GetImpulse().x > 0 && angle < 70.0f) ||
			(CalculateDistance(position, parent->GetWorldPos()) > SACK_RADIUS * 3.0f &&
				parent->GetImpulse().x > 0 && angle < 90.0f))
			MoveRight();
		break;

	case SackStateBase::SACK_DASH:
		if (force > 40.0f)
		{
			SetState(SackStateBase::SACK_DASH);
			impulse.x = DASH_FORCE;
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
	if (parent != nullptr)	return;

	CSackBase* sack = (CSackBase*)HitManager::CheckHit(hitUpOut, GAMEHIT_TYPE::HIT_SACK);

	if (sack == nullptr)	return;

	if (sack->GetStringDir() == hookDir && sack->child_ == nullptr)
	{
		parent = sack;
		parent->child_ = this;
	}
}

void CSackBase::ClearChain(void)
{
	if (stringDir == SACK_DIR_NONE)	return;

	//parent->rope->ClearLock();
	parent->child_ = nullptr;
	parent = nullptr;
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
	if (impulse.x > FRICTION)
		impulse.x -= FRICTION;

	else if (impulse.x < -FRICTION)
		impulse.x += FRICTION;

	else impulse.x = 0;
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
	CSackBase* tempObj = (CSackBase*)HitManager::CheckHit(hitRight, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr)
	{
		if (tempObj->GetState()->GetStateName() == SackStateBase::SACK_DASH)
		{
			impulse.x = -DASH_FORCE;
			state_ = state_->GetState(SackStateBase::SACK_DASH);
		}
		return;
	}

	//������Ԃ�����ꍇ
	tempObj = (CSackBase*)HitManager::CheckHit(hitLeft, GAMEHIT_TYPE::HIT_SACK);
	if (tempObj != nullptr)
	{
		if (tempObj->GetState()->GetStateName() == SackStateBase::SACK_DASH)
		{
			impulse.x = DASH_FORCE;
			state_ = state_->GetState(SackStateBase::SACK_DASH);
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
	if (abs(impulse.x) < 1.0f)
		LeaveWall();
	else
	{
		switch (looking)
		{
		case SACK_DIR_LEFT:
			if (HitManager::CheckStage(hitLeft) || HitManager::CheckHit(hitLeft, GAMEHIT_TYPE::HIT_SACK))
			{
				ResetPositionX();
			}
			break;

		case SACK_DIR_RIGHT:
			if (HitManager::CheckStage(hitRight) || HitManager::CheckHit(hitRight, GAMEHIT_TYPE::HIT_SACK))
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
	if (HitManager::CheckStage(hitCenter) || HitManager::CheckHit(hitCenter, GAMEHIT_TYPE::HIT_SACK))
	{
		if (HitManager::CheckStage(hitRight) || HitManager::CheckHit(hitRight, GAMEHIT_TYPE::HIT_SACK))
			position.x -= 0.25f;
		else if (HitManager::CheckStage(hitLeft) || HitManager::CheckHit(hitLeft, GAMEHIT_TYPE::HIT_SACK))
			position.x += 0.25f;
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
	CStage::CleanNumbers(nullptr, &position.y);
	position.y += SACK_RADIUS;
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
	position.x = oldPosition.x;
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
	position.y = oldPosition.y;
}

//==============================================================================
//!	@fn		GetParent
//!	@brief	�e��߂�
//!	@param	�Ȃ�
//!	@retval	C3DObject*  �e�ւ̃|�C���^
//==============================================================================
CSackBase* CSackBase::GetParent(void)
{
	return parent;
}

//==============================================================================
//!	@fn		GetImpulse
//!	@brief	�e�݂�߂��֐�
//!	@param	�Ȃ�
//!	@retval	D3DXVECTOR3	oldImpulse		�I�u�W�F�N�g�̒e��
//==============================================================================
XMFLOAT3 CSackBase::GetImpulse(void)
{
	return oldImpulse;
}

//==============================================================================
//!	@fn		GetRopePullForce
//!	@brief	�����������
//!	@param	�Ȃ�
//!	@retval	float	��
//==============================================================================
float CSackBase::GetRopePullForce(void)
{
	if (parent == nullptr)
		return 0;
	//return parent->rope->GetPullForce();
	return 0;
}

//==============================================================================
//!	@fn		GetRopePullAngle
//!	@brief	��������ꂽ�p�x
//!	@param	�Ȃ�
//!	@retval	float	�p�x�i���W�A���j
//==============================================================================
float CSackBase::GetRopePullAngle(void)
{
	if (parent == nullptr)
		return 0;

	//return parent->rope->GetPullAngle();
	return 0;
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
	return stringDir;
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
	return looking;
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
	return hookDir;
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
	impulse.x += impulseX;
	impulse.y += impulseY;
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
	impulse.x = impulseX;
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
	impulse.y = impulseY;
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
	state_ = state_->GetState(stateName);

	//�J�n�֐����Ăяo��
	state_->Enter(this);
}

//==============================================================================
//!	@fn		CreateMesh
//!	@brief�@�R�f�̃��b�V�������֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CSackBase::CreateMesh(void)
{
	//���̃��b�V���̍쐬
	//D3DXCreateBox(CDirectXGraphics::GetDXDevice(), SACK_RADIUS * 2, SACK_RADIUS * 2, SACK_RADIUS * 2, &mesh, nullptr);
	//D3DXCreateSphere(CDirectXGraphics::GetDXDevice(), SACK_RADIUS, 20, 20, &mesh, nullptr);

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
	position.y += impulse.y / 15.0f;
	position.x += impulse.x / 15.0f;

	//�}�g���b�N�X�̍X�V
	m_positionX = position.x;
	m_positionY = position.y;
	m_positionZ = position.z;

}


//==============================================================================
//!	@fn		UpdateHit
//!	@brief	�����蔻��̐ݒ�֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//==============================================================================
void CSackBase::UpdateHit(void)
{
	hitCenter->UpdatePosition(position);
	hitLeft->UpdatePosition({ position.x - SACK_RADIUS, position.y, position.z });
	hitRight->UpdatePosition({ position.x + SACK_RADIUS, position.y, position.z });
	hitUp->UpdatePosition({ position.x, position.y + SACK_RADIUS, position.z });
	hitDown->UpdatePosition({ position.x, position.y - SACK_RADIUS, position.z });
	hitRightOut->UpdatePosition({ position.x + SACK_RADIUS * 2, position.y, position.z });
	hitLeftOut->UpdatePosition({ position.x - SACK_RADIUS * 2, position.y, position.z });
	hitUpOut->UpdatePosition({ position.x, position.y + SACK_RADIUS * 2, position.z });

	HitManager::AddHit(hitCenter);
	HitManager::AddHit(hitRight);
	HitManager::AddHit(hitLeft);
	HitManager::AddHit(hitUp);
	HitManager::AddHit(hitDown);
	HitManager::AddHit(hitRightOut);
	HitManager::AddHit(hitLeftOut);
	HitManager::AddHit(hitUpOut);

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
	return state_;
}

XMFLOAT3 CSackBase::GetHookPos(void)
{
	XMMATRIX  hookMatrix, transMatrix, rotMatrix;
	XMFLOAT4X4 hookMatTemp;

	hookMatrix = XMMatrixTranslation(0, SACK_RADIUS, 7);
	transMatrix = XMMatrixTranslation(position.x, position.y, position.z);
	rotMatrix = XMMatrixRotationY(initAngle);

	hookMatrix = hookMatrix * rotMatrix * transMatrix;

	XMStoreFloat4x4(&hookMatTemp, hookMatrix);

	return{ hookMatTemp._41, hookMatTemp._42, hookMatTemp._43 };
}
//******************************************************************************
//	End of file.
//******************************************************************************
