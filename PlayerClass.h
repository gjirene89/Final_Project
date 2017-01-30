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
# include "SackBaseClass.h"
# include "HitBaseClass.h"
//# include "CRope.h"

//=============================================================================
//!	@class	CPlayer
//!	@brief �v���C���[
//=============================================================================
class CPlayer : public CSackBase
{
public:	
	
	CPlayer(float posX, float posY);			//�R���X�g���N�^
	~CPlayer(void);								//�f�X�g���N�^
	
	void Initialize	(void);						//�������֐�
	void Input		(CInput* input);						//���͊֐�
	void Action		(void);						//�����֐�
	void Render		(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition, CLight* light);
	void PostAction	(void);						//�㏈���֐�

	void MoveRight	(void);						//�E�ֈړ�
	void MoveLeft	(void);						//���ֈړ�
	void FlipString	(void);						//�R��U���
	void Dash		(void);						//�_�b�V��
	void HitWall	(void);						//�ǂƂԂ�����
	void LeaveWall	(void);						//�ǂ��痣���

private:

	XMVECTOR		m_quaternion;			//�N�I�[�^�j�I��

	void UpdateRotation		(void);		//��]�̍X�V
};

#endif // !__GM31_CPLAYER__

//******************************************************************************
//	End of file.
//******************************************************************************