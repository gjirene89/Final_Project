//************************************************************************//
//	SackBaseClass.h
//	2017-01-16
//	Irene Gersenowies
//************************************************************************//

#ifndef __SACK_BASE_H__
#define __SACK_BASE_H__

//==============================================================================
//		�C���N���[�h
//==============================================================================
# include "GameObjectBase.h"
# include "SackStateBase.h"
# include "HitBaseClass.h"
//# include "CXFile.h"
//# include "CDebugFont.h"
//# include "HitManager.h"
//# include "Macros.h"
//# include "Debug.h"
//# include "CRope.h"
//# include "ModelManager.h"
//# include "TextureManager.h"


//==============================================================================
//	�N���X��		CSacksBase
//==============================================================================
class CSackBase : public CGameObjectBase
{ 
public:
	//�v���C���[�̌���
	enum SACK_DIR
	{
		SACK_DIR_LEFT,
		SACK_DIR_RIGHT,
		SACK_DIR_NONE
	};

	
	//�����蔻��
	CHit_Base	*hitCenter;						//���S
	CHit_Base	*hitLeft;						//��
	CHit_Base	*hitRight;						//�E
	CHit_Base	*hitUp;							//��
	CHit_Base	*hitDown;						//��
	CHit_Base	*hitRightOut;					//�E�i�W�����v�p�j
	CHit_Base	*hitLeftOut;					//���i�W�����v�p�j
	CHit_Base	*hitUpOut;						//��i�A���p�j
	
	CSackBase	*child_;				//���Ă���R�f


	CSackBase(float posX, float posY, GAMEOBJTYPE gObj);	//�R���X�g���N�^
	~CSackBase(void);							//�f�X�g���N�^

	virtual void Initalize(void);							//�������֐�
	virtual void Action(void);							//�����֐�
	//virtual void Input(void){};							//���͊֐�
	virtual void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);							//�`��֐�
	virtual void PostAction(void);						//�㏈���֐�
	
	virtual void MoveRight(void);						//�E�ֈړ�
	virtual void MoveLeft(void);						//���ֈړ�
	void Jump(void);							//�W�����v
	void Pull(void);							//����������
	void Chain(void);							//�A������
	void Slide(void);							//����ɂ��ׂČ�������
	virtual void Dash(void);					//�_�b�V��
	virtual void HitWall(void);					//�ǂƓ�����
	virtual void LeaveWall(void);				//�ǂ��痣���
	void CleanNumbers(void);					//�X�e�[�W�ɃX�i�b�v����

	void ResetPositionX(void);					//X�ʒu�̒l��Old�̒l�ɖ߂�
	void ResetPositionY(void);					//Y�ʒu�̒l��Old�̒l�ɖ߂�

	CSackBase* GetParent(void);					//�e��߂�
	XMFLOAT3 GetImpulse(void);				//�e�݂̒l��߂��֐�
	SACK_DIR GetStringDir(void);				//�R�̌�����Ԃ��֐�
	SACK_DIR GetLookingDir(void);				//�����Ă��������߂�
	SACK_DIR GetHookDir(void);					//�t�b�N�̌�����߂�
	float GetRopePullForce(void);					//�R�̈��������
	float GetRopePullAngle(void);
	SackStateBase* GetState(void);					//��Ԃ�߂�
	XMFLOAT3 GetHookPos(void);

	void AddImpulse(float impulseX, float impulseY);	//�e�݂̒l�𑝂₷�֐�
	void SetImpulseX(float impulseX);				//X���̒e�݂��Z�b�g����
	void SetImpulseY(float impulseX);				//Y���̒e�݂��Z�b�g����
	void SetState(SackStateBase::SACK_STATE stateName);		//��Ԃ��Z�b�g����

protected:

	static int noSack;
	int noId;
	char nameId[256];
	

	//CRope *rope;
	SackStateBase* state_;

	//�ʒu
	XMFLOAT3		initPosition;		//�����ʒu
	XMFLOAT3		position;			//���݈ʒu
	XMFLOAT3		oldPosition;		//�O�t���[���̈ʒu

	float			initAngle;			//���������Ă������
	XMFLOAT3		orientation;		//�����Ă���p�x

	XMFLOAT3		impulse;			//���݂̈ړ���
	XMFLOAT3		oldImpulse;			//�O�t���[���̈ړ���

	SACK_DIR		stringDir;			//�R�̌���
	SACK_DIR		looking;			//�����Ă������
	SACK_DIR		hookDir;			//�t�b�N�̌���
	CSackBase		*parent;			//�Ȃ����Ă���R�f

	void CreateMesh(void);				//���b�V���̐����֐�
	void UpdateDisplacement(void);		//�ʒu���X�V����
	void UpdateHit(void);				//�����蔻��̍X�V�֐�
	void ClearChain(void);

	virtual void RenderDebug(void);				//�f�o�b�O�\���֐�
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************