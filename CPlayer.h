//*****************************************************************************
//!	@file	CPlayer.h
//!	@brief	�v���C���[�̃w�b�_�̏W�܂�
//!	@note	
//!	@author	�C���l�@�w���Z�m�E�C�X
//*****************************************************************************

#ifndef __GM31_CPLAYER__
#define __GM31_CPLAYER__

//-----------------------------------------------------------------------------
//	�w�b�_�[
//-----------------------------------------------------------------------------
# include "CSackBase.h"
# include "CHit_Base.h"
# include "CRope.h"

//=============================================================================
//!	@class	CPlayer
//!	@brief �v���C���[
//=============================================================================
class CPlayer : public CSackBase
{
public:	
	
	CPlayer(float posX, float posY);			//�R���X�g���N�^
	~CPlayer(void);								//�f�X�g���N�^
	
	void Init		(void);						//�������֐�
	void Input		(void);						//���͊֐�
	void Action		(void);						//�����֐�
	void PostAction	(void);						//�㏈���֐�

	void MoveRight	(void);						//�E�ֈړ�
	void MoveLeft	(void);						//���ֈړ�
	void FlipString	(void);						//�R��U���
	void Dash		(void);						//�_�b�V��
	void HitWall	(void);						//�ǂƂԂ�����
	void LeaveWall	(void);						//�ǂ��痣���

private:

	D3DXQUATERNION	quaternion;			//�N�I�[�^�j�I��

	void UpdateRotation		(void);		//��]�̍X�V
};

#endif // !__GM31_CPLAYER__

//******************************************************************************
//	End of file.
//******************************************************************************