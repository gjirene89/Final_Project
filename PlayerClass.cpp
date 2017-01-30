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
//# include "input.h"
# include "MathUtility.h"
//# include "Debug.h"
# include "Macros.h"
# include "HitManager.h"
# include "ShaderManager.h"

# include "PlayerClass.h"
# include "SackBaseClass.h"
# include "PlayerStateHeader.h"
# include "StageClass.h"
# include "HitSphereClass.h"
# include "SceneManager.h"
# include "SackStateBase.h"

//-----------------------------------------------------------------------------
//	�}�N���萔
//-----------------------------------------------------------------------------
# define ROT_SPEED	XM_PI/40.0f

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
	strcpy_s(m_nameId, "Player");

	//�N�I�A�^�j�I���̏�����
	m_quaternion = XMQuaternionIdentity();

	//�F�ݒ�
	//SetDiffuse({1.0f,0.0f,0.0f,1.0f});

	//���b�V������
	//CreateMesh();
	//LoadXFile("assets/xFiles/Player/sack.x");
	//mesh = ModelManager::GetModel(ModelManager::MODEL_PLAYER_NORMAL);
	//texture = TexManager::GetTexture(TexManager::TEX_PLAYER_COLOR);

	//�����蔻��
//	hitCenter	= new CHit_Sphere(PLAYER_RADIUS, GAMEHIT_TYPE::HIT_PLAYER, this);

	m_rope = new CRope(XMFLOAT3( 0, SACK_RADIUS, 2 ));
	m_hookDir = SACK_DIR_NONE;
	m_state = new PlayerState();
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
void CPlayer::Initialize(void)
{
	//D3DXQuaternionRotationMatrix(&quaternion, &matrix);

	m_looking = SACK_DIR_RIGHT;
	m_stringDir = SACK_DIR_LEFT;

	CSackBase::Initialize();
	
	m_quaternion = XMQuaternionRotationMatrix(m_matrix);
}

//==============================================================================
//!	@fn		Input
//!	@brief	�v���C���[�̓��͊֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CPlayer::Input(CInput* input)
{
	//���݂̏�Ԃ̓��͂��Ăяo��
	m_state->Input(input, this);
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
	m_animBody->InterpolateModels();

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
/*	if (HitManager::CheckHit(m_hitCenter, GAMEHIT_TYPE::HIT_GOAL))
		SceneManager::StageClear();
	*/
	CSackBase::PostAction();

}

//==============================================================================
//!	@fn		Render
//!	@brief	�R�f�̕`��֐�
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CPlayer::Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition, CLight* light)
{
	if (!m_body)
		return;

	CalculateWorldMatrix(m_matrix, m_quaternion);
	
	m_body->Render(deviceContext,m_animBody->GetVertexBuffer(deviceContext));
	//CShaderManager::getInstance().RenderTextureShader(deviceContext, m_body->GetIndexCount(), m_matrix, viewMatrix, projectionMatrix, m_colorTexture->GetTextureData());
	
	CShaderManager::getInstance().RenderSpecularShader(deviceContext, m_body->GetIndexCount(), 
		m_matrix, viewMatrix, projectionMatrix, 
		m_colorTexture->GetTextureData(),light->GetDirection(), light->GetAmbientColor(), light->GetDiffuseColor(),
		cameraPosition, light->GetSpecularColor(), light->GetSpecularPower());

	//m_hook->Render(deviceContext);
	//CShaderManager::getInstance().RenderSpecularShader(deviceContext, m_hook->GetIndexCount(), m_matrix, viewMatrix, projectionMatrix, XMFLOAT4(1.0f,1.0f,0.0f,1.0f));
	
	m_rope->Render(deviceContext,m_matrix,viewMatrix,projectionMatrix, cameraPosition, light);
	//if (m_rope != nullptr) m_rope->Render();
	//RenderDebug();

	/*
	if (CDebug::displayAxis && !CDebug::GetIsHidden())
	RenderAxis();
	*/
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
	m_looking = SACK_DIR_RIGHT;
	m_stringDir = SACK_DIR_LEFT;

	m_orientation = { cos(m_initAngle), 0.0f, -sin(m_initAngle) };

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
	m_looking = SACK_DIR_LEFT;
	m_stringDir = SACK_DIR_RIGHT;
	m_orientation = { cos(-m_initAngle), 0.0f, -sin(-m_initAngle) };

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
	switch (m_stringDir)
	{
	case SACK_DIR_LEFT:
		m_stringDir = SACK_DIR_RIGHT;
		break;

	case SACK_DIR_RIGHT:
		m_stringDir = SACK_DIR_LEFT;
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
	switch (m_looking)
	{
	case SACK_DIR_RIGHT:
		if (!HitManager::CheckStage(m_hitRight))
			m_impulse.x = DASH_FORCE;
		break;

	case SACK_DIR_LEFT:
		if (!HitManager::CheckStage(m_hitLeft))
			m_impulse.x = -DASH_FORCE;
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
void CPlayer::LeaveWall(void)
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
//!	@fn		UpdateRotation
//!	@brief�@��]�X�V
//!	@param	�Ȃ�
//!	@retval	�Ȃ�
//!	@note	
//==============================================================================
void CPlayer::UpdateRotation(void)
{
	XMVECTOR rotX, orientX, targetQt, mulQuat;
	float d, angleDiff;

	rotX = XMLoadFloat3(&GetRotX());
	orientX = XMLoadFloat3(&m_orientation);

	//�N�I�[�^�j�I�������߂�
	targetQt = RotationArc(rotX, orientX, d);
	
	//�p�x�����߂�
	angleDiff = acos(d);

	if (angleDiff == 0) return;
	targetQt = RotationArc(rotX, orientX, d);
	mulQuat = XMQuaternionMultiply(m_quaternion, targetQt);

	//���݂̊p�x��ړI�̊p�x�ɍ��킹�Ă���
	if (ROT_SPEED >= angleDiff)	
		m_quaternion = mulQuat;
	else
	{
		float t = ROT_SPEED / angleDiff;
		m_quaternion = XMQuaternionSlerp(m_quaternion, mulQuat, t);
	}
	
	//�N�I�[�^�j�I�����}�g���b�N�X�ɃZ�b�g
	//m_matrix = XMMatrixRotationQuaternion(m_quaternion);
	//D3DXMatrixRotationQuaternion(&matrix, &quaternion);
}

//******************************************************************************
//	End of file.
//******************************************************************************
