//************************************************************************//
//	PositionClass.h
//	2016-11-23
//	Irene Gersenowies
//************************************************************************//
#ifndef __POSITION_CLASS_H__
#define __POSITION_CLASS_H__

//=======================================================================//
//		インクルード
//=======================================================================//
#include <math.h>

//=======================================================================//
//		クラス名 : CPosition
//=======================================================================//
class CPosition
{
public:
	CPosition(void);
	CPosition(const CPosition& other);
	~CPosition(void);

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	void GetPosition(float& x, float& y, float& z);
	void GetRotation(float& x, float& y, float& z);

	void SetFrameTime(float time);
	
	void MoveForwards(bool keydown);
	void MoveBackwards(bool keydown);
	void MoveUpwards(bool keydown);
	void MoveDownwards(bool keydown);
	void MoveRightwards(bool keydown);
	void MoveLeftwards(bool keydown);
	void TurnLeft(bool keydown);
	void TurnRight(bool keydown);
	void TurnUp(bool keydown);
	void TurnDown(bool keydown);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	float m_frameTime;

	float m_forwardSpeed, m_backwardSpeed;
	float m_upwardSpeed, m_downwardSpeed;
	float m_leftTurnSpeed, m_rightTurnSpeed;
	float m_lookUpSpeed, m_lookDownSpeed;
	float m_leftwardSpeed, m_rightwardSpeed;
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************