//************************************************************************//
//	TimerClass.h
//	2016-11-23
//	Irene Gersenowies
//************************************************************************//

#ifndef __TIMER_CLASS_H__
#define __TIMER_CLASS_H__

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
#include <Windows.h>

//=======================================================================//
//		�N���X��: TimerClass
//=======================================================================//
class CTimer
{
public:
	CTimer(void);
	CTimer(const CTimer& other);
	~CTimer(void);

	bool Initialize(void);
	void Frame(void);

	float GetTime(void);

private:
	INT64 m_frequency;
	float m_ticksPerMs;
	INT64 m_startTime;
	float m_frameTime;
};

#endif // !__TIMER_CLASS_H__

//******************************************************************************
//	End of file.
//******************************************************************************