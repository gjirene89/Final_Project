//************************************************************************//
//	PlayerState.cpp
//	2017-01-22
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		インクルード
//=======================================================================//
# include "PlayerStateHeader.h"

//=======================================================================//
//		グローバル変数
//=======================================================================//
SackStateBase* PlayerState::m_normalState = nullptr;
SackStateBase* PlayerState::m_fallingState = nullptr;
SackStateBase* PlayerState::m_dashState = nullptr;
SackStateBase* PlayerState::m_moveState = nullptr;
SackStateBase* PlayerState::m_jumpState = nullptr;
SackStateBase* PlayerState::m_flipState = nullptr;

bool PlayerState::m_isInitializedPlayer = false;


PlayerState::PlayerState(void)
{
	if (m_isInitializedPlayer) return;
	m_isInitializedPlayer = true;

	m_normalState = new NormalState();
	m_fallingState = new FallingState();
	m_dashState = new DashingState();
	m_moveState = new MoveState();
	m_jumpState = new JumpingState();
	m_flipState = new FlipState();
}


PlayerState::~PlayerState()
{
	//状態のポインタを解放する
	if (m_normalState != nullptr)	delete m_normalState;
	if (m_fallingState != nullptr)	delete m_fallingState;
	if (m_dashState != nullptr)	delete m_dashState;
	if (m_moveState != nullptr)	delete m_moveState;
	if (m_jumpState != nullptr)	delete m_jumpState;
	if (m_flipState != nullptr)	delete m_flipState;
}

SackStateBase* PlayerState::GetState(SACK_STATE stateName)
{
	switch (stateName)
	{
	case SACK_NORMAL:	return m_normalState;
	case SACK_FALL:     return m_fallingState;
	case SACK_DASH:		return m_dashState;
	case SACK_JUMP:		return m_jumpState;
	case SACK_MOVE:		return m_moveState;
	case SACK_FLIP:		return m_flipState;
	}

	return this;
}

//******************************************************************************
//	End of file.
//******************************************************************************