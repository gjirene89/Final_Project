//************************************************************************//
//	PlayerState.h
//	2017-01-22
//	Irene Gersenowies
//************************************************************************//

#ifndef __GM31_PLAYER_STATE__
#define __GM31_PLAYER_STATE__

//=======================================================================//
//		インクルード
//=======================================================================//
# include "PlayerClass.h"
//# include "input.h"
# include <stdio.h>
# include "HitManager.h"
# include "Macros.h"

//=======================================================================//
//	クラス名		PlayerState
//=======================================================================//
class PlayerState : public SackStateBase
{

public:
	PlayerState(void);
	PlayerState(const PlayerState& other) {};
	PlayerState(SACK_STATE state) : SackStateBase(state){};
	virtual ~PlayerState(void);								//デストラクタ
	
	SackStateBase* GetState(SACK_STATE stateName);

private:

	static SackStateBase* m_normalState;
	static SackStateBase* m_fallingState;
	static SackStateBase* m_dashState;
	static SackStateBase* m_moveState;
	static SackStateBase* m_jumpState;
	static SackStateBase* m_flipState;
	
	static bool m_isInitializedPlayer;

};

#endif
//******************************************************************************
//	End of file.
//******************************************************************************