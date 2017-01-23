//************************************************************************//
//	SackStateBaseHeaders.h
//	2017-01-22
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
# include "SackStateBaseHeaders.h"

//=======================================================================//
//		�O���[�o���ϐ�
//=======================================================================//
SackStateBase* SackStateBase::m_normalState = nullptr;
SackStateBase* SackStateBase::m_fallingState = nullptr;
SackStateBase* SackStateBase::m_dashState = nullptr;
SackStateBase* SackStateBase::m_moveState = nullptr;
SackStateBase* SackStateBase::m_jumpState = nullptr;

bool SackStateBase::m_isInitialized = false;

SackStateBase::SackStateBase(void)
{
	if (m_isInitialized)	return;
	m_isInitialized = true;

	m_normalState = new NormalStateBase();
	m_fallingState = new FallingStateBase();
	m_dashState = new DashingStateBase();
	m_moveState = new MoveStateBase();
	m_jumpState = new JumpingStateBase();

	return;
}

SackStateBase::~SackStateBase()
{
	//��Ԃ̃|�C���^���������
	if (m_normalState != nullptr)	delete m_normalState;
	if (m_fallingState != nullptr)	delete m_fallingState;
	if (m_dashState != nullptr)		delete m_dashState;
	if (m_moveState != nullptr)		delete m_moveState;
	if (m_jumpState != nullptr)		delete m_jumpState;

	return;
}

SackStateBase* SackStateBase::GetState(SACK_STATE stateName)
{
	switch (stateName)
	{
	case SACK_NORMAL:	return m_normalState;
	case SACK_FALL:     return m_fallingState;
	case SACK_DASH:		return m_dashState;
	case SACK_JUMP:		return m_jumpState;
	case SACK_MOVE:		return m_moveState;
	}

	return this;
}
