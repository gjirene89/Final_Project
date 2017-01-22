//*****************************************************************************
//!	@file	HitManager.h
//!	@brief	�����蔻��p
//!	@note	
//!	@author�@�C���l�@�w���Z�m�E�C�X�@�n�\
//*****************************************************************************

#ifndef __HIT_MANAGER__
#define __HIT_MANAGER__

//-----------------------------------------------------------------------------
//	�w�b�_�|
//-----------------------------------------------------------------------------
//# include "BoundingSphere.h"
# include "GameObjectBase.h"
//# include "C3DObject.h"
# include "HitBaseClass.h"

//-----------------------------------------------------------------------------
//	�}�N����
//-----------------------------------------------------------------------------
# define	MAX_HIT_CNT		1000			//�ő�̂����蔻��̌���

//=============================================================================
//!	@class	HitManager
//!	@brief	�����蔻��̊Ǘ��N���X
//=============================================================================
class HitManager
{
public:
	HitManager(void);
	~HitManager(void);

	void Init(void);
	void Reset(void);
	void Render(void);

	static void AddHit(CHit_Base *newObj);
	static CGameObjectBase* CheckHit(CHit_Base *pHit, GAMEHIT_TYPE objType);
	static bool CheckStage(CHit_Base *pHit);

private:

	bool	isVisible;						//�����蔻���`�悷�邩�ǂ���

	static int	nHitCnt;						//�����蔻��̔z��ɓ����Ă���Q�[���I�u�W�F�N�g�̐�
	static CHit_Base *hitList[MAX_HIT_CNT];	//�����蔻��̔z��

	void RenderDebug(void);

	
};


#endif