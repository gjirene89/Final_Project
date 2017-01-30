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
# include "ModelClass.h"
# include "RopeClass.h"
# include "TextureClass.h"
# include "ModelAnimationClass.h"

//# include "CXFile.h"
//# include "CDebugFont.h"
//# include "HitManager.h"
//# include "Macros.h"
//# include "Debug.h"
//# include "ModelManager.h"
//# include "TextureManager.h"

//==============================================================================
//	�}�N���萔
//==============================================================================
# define LOOK_ANGLE	(-30.0f * XM_PI / 180.0f)

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

	//�R�f�̃��f����
	enum SACK_MODELS {
		MODEL_NORMAL,
		MODEL_SQUASH,
		MODEL_JUMP,
		MODEL_MOVE_JUMP,
		MODEL_MOVE_FALL,
		MODEL_DASH,
		MODEL_IMPACT_FRONT,
		MODEL_IMPACT_UP,

		MODEL_MAX
	};

	//�����蔻��
	CHit_Base	*m_hitCenter;						//���S
	CHit_Base	*m_hitLeft;						//��
	CHit_Base	*m_hitRight;						//�E
	CHit_Base	*m_hitUp;							//��
	CHit_Base	*m_hitDown;						//��
	CHit_Base	*m_hitRightOut;					//�E�i�W�����v�p�j
	CHit_Base	*m_hitLeftOut;					//���i�W�����v�p�j
	CHit_Base	*m_hitUpOut;						//��i�A���p�j

	CSackBase	*m_child;				//���Ă���R�f


	~CSackBase(void);							//�f�X�g���N�^

	virtual void Initialize(void);							//�������֐�
	virtual void Action(void);							//�����֐�
	virtual void Input(CInput* input){};							//���͊֐�
	virtual void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition, CLight* light)=0;							//�`��֐�
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
	void StartAnimation(SACK_MODELS modelName, int nFrames);

protected:

	static int     m_noSack;

	static CModel* m_body;
	static CModel* m_hook;
	
	CModelAnimation* m_animBody;


	static CTexture* m_colorTexture;
	static CTexture* m_bumpTexture;

	int            m_noId;
	char           m_nameId[256];


	CRope*		   m_rope;
	SackStateBase* m_state;

	//�ʒu
	XMFLOAT3		m_initPosition;		//�����ʒu
	XMFLOAT3		m_oldPosition;		//�O�t���[���̈ʒu

	float			m_initAngle;		//���������Ă������
	XMFLOAT3		m_orientation;		//�����Ă���p�x

	XMFLOAT3		m_impulse;			//���݂̈ړ���
	XMFLOAT3		m_oldImpulse;			//�O�t���[���̈ړ���

	SACK_DIR		m_stringDir;			//�R�̌���
	SACK_DIR		m_looking;			//�����Ă������
	SACK_DIR		m_hookDir;			//�t�b�N�̌���
	CSackBase*      m_parent;			//�Ȃ����Ă���R�f

	int				m_frames;

	SACK_MODELS		m_currModel;
	SACK_MODELS		m_nextModel;

protected:
	CSackBase(float posX, float posY, GAMEOBJTYPE gObj);	//�R���X�g���N�^
	bool InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Shutdown(void);

	void UpdateDisplacement(void);		//�ʒu���X�V����
	void UpdateHit(void);				//�����蔻��̍X�V�֐�
	void ClearChain(void);

	virtual void RenderDebug(void);				//�f�o�b�O�\���֐�
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************