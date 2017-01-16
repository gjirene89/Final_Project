//*****************************************************************************
//!	@file	CPlayer.h
//!	@brief	�v���C���[�N���X
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�w�b�_�|
//-----------------------------------------------------------------------------
# include <stdio.h>
# include "input.h"
# include "mathutil.h"
# include "Debug.h"
# include "Macros.h"
# include "HitManager.h"

# include "CPlayer.h"
# include "CSackBase.h"
# include "PlayerStateHeader.h"
# include "CStage.h"
# include "CHit_Sphere.h"
# include "SceneManager.h"
# include "SackStateBase.h"

//-----------------------------------------------------------------------------
//	�}�N���萔
//-----------------------------------------------------------------------------
# define LOOK_ANGLE	(-75 * D3DX_PI / 180.0f)
# define ROT_SPEED	D3DX_PI/20.0f

//-----------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-----------------------------------------------------------------------------

//==============================================================================
//!	@fn		CPlayer
//!	@brief	�v���C���[�̃R���X�g���N�^
//!	@param	float posX		�ʒu�@x��
//!	@param	float posY		�ʒu�@y��
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
CPlayer::CPlayer(float posX, float posY) : CSackBase(posX, posY, GAMEOBJTYPE::GOBJ_PLAYER)
{
	strcpy_s(nameId, "Player");

	//�N�I�A�^�j�I���̏�����
	D3DXQuaternionIdentity(&quaternion);

	//�F�ݒ�
	SetDiffuse({1.0f,0.0f,0.0f,1.0f});

	//���b�V������
	//CreateMesh();
	//LoadXFile("assets/xFiles/Player/sack.x");
	mesh = ModelManager::GetModel(ModelManager::MODEL_PLAYER_NORMAL);
	texture = TexManager::GetTexture(TexManager::TEX_PLAYER_COLOR);

	//�����蔻��
//	hitCenter	= new CHit_Sphere(PLAYER_RADIUS, GAMEHIT_TYPE::HIT_PLAYER, this);

	rope = new CRope(D3DXVECTOR3( 0, SACK_RADIUS, 2 ));
	hookDir = SACK_DIR_NONE;
	state_ = new PlayerState();
}

//==============================================================================
//!	@fn		~CPlayer
//!	@brief	�v���C���[�̃f�X�g���N�^
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
CPlayer::~CPlayer(void)
{
	//���͋�
}

//==============================================================================
//!	@fn		Init
//!	@brief	�v���C���[�̏������֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CPlayer::Init(void)
{
	D3DXQuaternionRotationMatrix(&quaternion, &matrix);

	looking = SACK_DIR_RIGHT;
	stringDir = SACK_DIR_LEFT;

	CSackBase::Init();
}

//==============================================================================
//!	@fn		Input
//!	@brief	�v���C���[�̓��͊֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CPlayer::Input(void)
{
	//���݂̏�Ԃ̓��͂��Ăяo��
	state_->Input(this);
}

//==============================================================================
//!	@fn		Action
//!	@brief	�v���C���[�̏����֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CPlayer::Action(void)
{


	//�����Ă�������̍X�V
	UpdateRotation();

	CSackBase::Action();
}

//==============================================================================
//!	@fn		PostAction
//!	@brief	�v���C���[�̌㏈��
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CPlayer::PostAction(void)
{
	if (HitManager::CheckHit(hitCenter, GAMEHIT_TYPE::HIT_GOAL))
		SceneManager::StageClear();
	
	CSackBase::PostAction();

}

//==============================================================================
//!	@fn		MoveRight
//!	@brief	�E�ֈړ�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CPlayer::MoveRight(void)
{
	looking = SACK_DIR_RIGHT;
	stringDir = SACK_DIR_LEFT;
	orientation = { cos(LOOK_ANGLE), 0.0f, -sin(LOOK_ANGLE) };

	CSackBase::MoveRight();
		
}

//==============================================================================
//!	@fn		MoveLeft
//!	@brief	�E�ֈړ�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CPlayer::MoveLeft(void)
{
	looking = SACK_DIR_LEFT;
	stringDir = SACK_DIR_RIGHT;
	orientation = { cos(-LOOK_ANGLE), 0.0f, -sin(-LOOK_ANGLE) };

	CSackBase::MoveLeft();
}

//==============================================================================
//!	@fn		FlipString
//!	@brief	�R�̌������t�ɂ���
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CPlayer::FlipString(void)
{
	switch (stringDir)
	{
	case SACK_DIR_LEFT:
		stringDir = SACK_DIR_RIGHT;
		break;

	case SACK_DIR_RIGHT:
		stringDir = SACK_DIR_LEFT;
		break;
	}
}

//==============================================================================
//!	@fn		Dash
//!	@brief	�_�b�V���J�n�֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CPlayer::Dash(void)
{
	//�����ɍ��킹�ă_�b�V�����J�n����@�i�ƂȂ�ɕǂ�����ƁA�_�b�V�������s���Ȃ�
	switch (looking)
	{
	case SACK_DIR_RIGHT:
		if (!HitManager::CheckStage(hitRight))
			impulse.x = DASH_FORCE;
		break;

	case SACK_DIR_LEFT:
		if (!HitManager::CheckStage(hitLeft))
			impulse.x = -DASH_FORCE;
		break;
	}
}

//==============================================================================
//!	@fn		HitWall
//!	@brief	�ǂƓ�����Ƃ�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CPlayer::HitWall(void)
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
void CPlayer::LeaveWall(void)
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
//!	@fn		UpdateRotation
//!	@brief�@��]�X�V
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CPlayer::UpdateRotation(void)
{
	//�������ς���Ă��Ȃ��ꍇ�A�������Ȃ�
	if (GetRotX() == orientation)	return;

	//�N�I�[�^�j�I�������߂�
	float d = 0;
	D3DXQUATERNION targetQt = RotationArc(GetRotX(), orientation, d);

	//�p�x�����߂�
	float angleDiff = acos(d);

	//���݂̊p�x��ړI�̊p�x�ɍ��킹�Ă���
	if (ROT_SPEED >= angleDiff)		quaternion = quaternion * targetQt;
	else
	{
		float t = ROT_SPEED / angleDiff;
		D3DXQuaternionSlerp(&quaternion, &quaternion, &(quaternion * targetQt), t);
	}
	
	//�N�I�[�^�j�I�����}�g���b�N�X�ɃZ�b�g
	D3DXMatrixRotationQuaternion(&matrix, &quaternion);
}

//******************************************************************************
//	End of file.
//******************************************************************************
