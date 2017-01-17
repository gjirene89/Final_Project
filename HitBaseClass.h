//************************************************************************//
//	HitBaseClass.cpp
//  �����蔻��N���X�̃x�[�X
//	2017-01-16
//	Irene Gersenowies
//************************************************************************//

#ifndef __HIT_BASE_H__
#define __HIT_BASE_H__

//==============================================================================
//		�C���N���[�h
//==============================================================================
#include "GameObjectBase.h"

//==============================================================================
//	�}�N���萔
//==============================================================================
# define MAX_HIT            1000

# define COLOR_HLIGHT		{10.0f, 10.0f, 0.0f, 0.3f}
# define COLOR_NORMAL		{1.0f, 1.0f, 1.0f, 0.3f}

enum GAMEHIT_TYPE
{
	HIT_NONE,
	HIT_SUPPORT,			//�����蔻��
	HIT_PLAYER,				//�v���C���[
	HIT_SACK,
	HIT_GOAL,				//�S�[��
	HIT_BEAD,

	HIT_MAX									//�I�u�W�F�N�g�̎�ނ̍ő吔
};

//==============================================================================
//	�N���X��		CSacksBase
//==============================================================================
class CHit_Base
{
protected:
	CGameObjectBase*			m_entity;				//�Q�[���I�u�W�F�N�g
	GAMEHIT_TYPE				m_type;					//�I�u�W�F�N�g�̎��
	XMFLOAT3					m_position;				//�ʒu
	bool						m_isVisible;			//�`�悷�邩�ǂ����t���O
	bool						m_isHit;				//�������Ă��邩�ǂ���
	D3DCOLORVALUE				m_color;				//�F


public:
	CHit_Base(void);
	CHit_Base(GAMEHIT_TYPE type);
	CHit_Base(const CHit_Base& other);
	~CHit_Base(void);

	void Initialize(void);
	void UpdatePosition(XMFLOAT3 position);
	void Highlight(void);

	GAMEHIT_TYPE GetHitType(void);
	XMFLOAT3 GetPosition(void);
	CGameObjectBase* GetEntity(void);

	virtual void Render() = 0;
	virtual CGameObjectBase* CheckHit(CHit_Base *pHit, GAMEHIT_TYPE objType) = 0;
	virtual CGameObjectBase* CheckBoxHit(CHit_Base *pBoxHit) = 0;
	virtual CGameObjectBase* CheckSphereHit(CHit_Base *pSphereHit) = 0;
	virtual bool CheckStage(void) = 0;
};

#endif
