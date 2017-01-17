# include "SackStateBaseHeaders.h"

SackStateBase* SackStateBase::normalState = nullptr;
SackStateBase* SackStateBase::fallingState = nullptr;
SackStateBase* SackStateBase::dashState = nullptr;
SackStateBase* SackStateBase::moveState = nullptr;
SackStateBase* SackStateBase::jumpState = nullptr;

bool SackStateBase::isInitialized = false;

SackStateBase::~SackStateBase()
{
	//èÛë‘ÇÃÉ|ÉCÉìÉ^Çâï˙Ç∑ÇÈ
	if (normalState != nullptr)	delete normalState;
	if (fallingState != nullptr)	delete fallingState;
	if (dashState != nullptr)	delete dashState;
	if (moveState != nullptr)	delete moveState;
	if (jumpState != nullptr)	delete jumpState;
}

SackStateBase* SackStateBase::GetState(SACK_STATE stateName)
{
	InitializeStates();
	switch (stateName)
	{
		case SACK_NORMAL:	return normalState;
		case SACK_FALL:     return fallingState;
		case SACK_DASH:		return dashState;
		case SACK_JUMP:		return jumpState;
		case SACK_MOVE:		return moveState;
	}

	return this;
}

void SackStateBase::InitializeStates(void)
{
	if (isInitialized)	return;
	isInitialized = true;

	normalState = new NormalStateBase();
	fallingState = new FallingStateBase();
	dashState = new DashingStateBase();
	moveState = new MoveStateBase();
	jumpState = new JumpingStateBase();

}