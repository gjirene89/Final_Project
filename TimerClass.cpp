//************************************************************************//
//	TimerClass.cpp
//	2016-11-23
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		インクルード
//=======================================================================//
#include "TimerClass.h"

//==============================================================================
//  関数名        CTimer	
//  説明          CTimerクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CTimer::CTimer()
{
	//空
}

//==============================================================================
//  関数名        CTimer	
//  説明          CTimerクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          CTimer& other			CTimerのインスタンス
//	戻り値
//          なし
//==============================================================================
CTimer::CTimer(const CTimer& other)
{
	//空
}

//==============================================================================
//  関数名        〜CTimer	
//  説明          CTimerクラスのデストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CTimer::~CTimer()
{
	//空
}

//==============================================================================
//  関数名        Initialize
//  説明          CTimerの初期関数
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CTimer::Initialize()
{
	//高パーフォーマンス タイマーを利用できる事を調べる
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if (m_frequency == 0)
	{
		return false;
	}

	//ミリ秒ごとのtick数を取得する
	m_ticksPerMs = (float)(m_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}

//==============================================================================
//  関数名        Frame
//  説明          CTimerの毎フレーム更新
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CTimer::Frame()
{
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	timeDifference = (float)(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;

	return;
}

//==============================================================================
//  関数名        Frame
//  説明          CTimerの毎フレーム更新
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          float    m_frameTime　　　　　　　　１フレームのミリ秒数
//==============================================================================
float CTimer::GetTime()
{
	return m_frameTime;
}

//******************************************************************************
//	End of file.
//******************************************************************************