//*****************************************************************************
//!	@file	Macros.h
//!	@brief	マクロ定数の集まり
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	マクロ定数
//-----------------------------------------------------------------------------

//**********************************//
//				環境用				//
//**********************************//
# define AIR_FRICTION		(0.20f)
# define FRICTION			( 0.8f)
# define GRAVITY			(-9.8f)
# define BLOCK_SIZE			(10.0f)

//**********************************//
//			プレイヤー用			//
//**********************************//
# define PLAYER_RADIUS		( 4.0f)
# define JUMP_FORCE			( 7.0f)
# define CLIMB_FORCE		(15.5f)
# define MOVE_FORCE			( 4.5f)
# define DASH_FORCE			(15.0f)

//**********************************//
//				蹴鞠用				//
//**********************************//
# define SACK_RADIUS		( 4.0f)
# define ROPE_LENGHT		(SACK_RADIUS * 4.0f)

# define SPRING_COEFFICIENT (13.0f)
# define BEAD_LENGHT		(0.50f)
# define BEAD_RADIUS		(1.0f)
# define BEAD_MASS			(1.0f)
# define BEAD_SIZE			(1.0f)
# define BEAD_NO			(5)