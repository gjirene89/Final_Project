//************************************************************************//
//	PositionClass.cpp
//	2016-11-23
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		インクルード
//=======================================================================//
#include "PositionClass.h"

//==============================================================================
//  関数名        CPosition	
//  説明          CPositionクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CPosition::CPosition()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_frameTime = 0.0f;

	m_forwardSpeed = 0.0f;
	m_backwardSpeed = 0.0f;
	m_upwardSpeed = 0.0f;
	m_downwardSpeed = 0.0f;
	m_leftTurnSpeed = 0.0f;
	m_rightTurnSpeed = 0.0f;
	m_lookUpSpeed = 0.0f;
	m_lookDownSpeed = 0.0f;
	m_rightwardSpeed = 0.0f;
	m_leftwardSpeed = 0.0f;
}

//==============================================================================
//  関数名        CPosition	
//  説明          CPositionクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          CPosition& other			CPositionのインスタンス
//	戻り値
//          なし
//==============================================================================
CPosition::CPosition(const CPosition& other)
{
	//空
}

//==============================================================================
//  関数名        ～CPosition	
//  説明          CPositionクラスのデストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CPosition::~CPosition()
{
	//空
}

//==============================================================================
//  関数名        SetPosition
//  説明          位置をセットする
//------------------------------------------------------------------------------
//	引数
//          float         x           位置（X軸）
//          float         y           位置（Y軸）
//          float         z           位置（Z軸）
//	戻り値
//          なし
//==============================================================================
void CPosition::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;

	return;
}

//==============================================================================
//  関数名        SetRotation
//  説明          回転度をセットする
//------------------------------------------------------------------------------
//	引数
//          float         x           回転度（X軸）
//          float         y           回転度（Y軸）
//          float         z           回転度（Z軸）
//	戻り値
//          なし
//==============================================================================
void CPosition::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;

	return;
}

//==============================================================================
//  関数名        GetPosition
//  説明          位置をゲットする
//------------------------------------------------------------------------------
//	引数
//          float&         x           位置（X軸）
//          float&         y           位置（Y軸）
//          float&         z           位置（Z軸）
//	戻り値
//          なし
//==============================================================================
void CPosition::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;

	return;
}

//==============================================================================
//  関数名        GetRotation
//  説明          回転度をゲットする
//------------------------------------------------------------------------------
//	引数
//          float&         x           回転度（X軸）
//          float&         y           回転度（Y軸）
//          float&         z           回転度（Z軸）
//	戻り値
//          なし
//==============================================================================
void CPosition::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;

	return;
}

//==============================================================================
//  関数名        SetFrameTime
//  説明          1フレームの時間を設定する
//------------------------------------------------------------------------------
//	引数
//          float         time         １フレームの秒数
//	戻り値
//          なし
//==============================================================================
void CPosition::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}

//==============================================================================
//  関数名        MoveForwards
//  説明          前移動
//------------------------------------------------------------------------------
//	引数
//          bool         keydown         キーが押されているかどうか
//	戻り値
//          なし
//==============================================================================
void CPosition::MoveForwards(bool keydown)
{
	float radians;

	//キーが押されたら、スピードを加速
	if (keydown)
	{
		m_forwardSpeed += m_frameTime * 0.001f;

		if (m_forwardSpeed > (m_frameTime * 0.03f))
		{
			m_forwardSpeed = m_frameTime * 0.03f;
		}
	}
	//押されていければ、スピードを減速
	else
	{
		m_forwardSpeed -= m_frameTime * 0.0007f;

		if (m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}

	radians = m_rotationY * 0.0174532925f;

	//位置更新
	m_positionX += sinf(radians) * m_forwardSpeed;
	m_positionZ += cosf(radians) * m_forwardSpeed;

	return;
}

//==============================================================================
//  関数名        MoveBackwards
//  説明          後ろ移動
//------------------------------------------------------------------------------
//	引数
//          bool         keydown         キーが押されているかどうか
//	戻り値
//          なし
//==============================================================================
void CPosition::MoveBackwards(bool keydown)
{
	float radians;

	//キーが押されたら、スピードを加速
	if (keydown)
	{
		m_backwardSpeed += m_frameTime * 0.001f;

		if (m_backwardSpeed > (m_frameTime * 0.03f))
		{
			m_backwardSpeed = m_frameTime * 0.03f;
		}
	}
	//押されていければ、スピードを減速
	else
	{
		m_backwardSpeed -= m_frameTime * 0.0007f;

		if (m_backwardSpeed < 0.0f)
		{
			m_backwardSpeed = 0.0f;
		}
	}

	radians = m_rotationY * 0.0174532925f;

	//位置更新
	m_positionX -= sinf(radians) * m_backwardSpeed;
	m_positionZ -= cosf(radians) * m_backwardSpeed;

	return;
}

//==============================================================================
//  関数名        MoveUpwards
//  説明          上移動
//------------------------------------------------------------------------------
//	引数
//          bool         keydown         キーが押されているかどうか
//	戻り値
//          なし
//==============================================================================
void CPosition::MoveUpwards(bool keydown)
{
	//キーが押されたら、スピードを加速
	if (keydown)
	{
		m_upwardSpeed += m_frameTime * 0.003f;

		if (m_upwardSpeed > (m_frameTime * 0.03f))
		{
			m_upwardSpeed = m_frameTime * 0.03f;
		}
	}
	//押されていければ、スピードを減速
	else
	{
		m_upwardSpeed -= m_frameTime * 0.002f;

		if (m_upwardSpeed < 0.0f)
		{
			m_upwardSpeed = 0.0f;
		}
	}

	//位置更新
	m_positionY += m_upwardSpeed;

	return;
}

//==============================================================================
//  関数名        MoveDownwards
//  説明          下移動
//------------------------------------------------------------------------------
//	引数
//          bool         keydown         キーが押されているかどうか
//	戻り値
//          なし
//==============================================================================
void CPosition::MoveDownwards(bool keydown)
{
	//キーが押されたら、スピードを加速
	if (keydown)
	{
		m_downwardSpeed += m_frameTime * 0.003f;

		if (m_downwardSpeed > (m_frameTime * 0.03f))
		{
			m_downwardSpeed = m_frameTime * 0.03f;
		}
	}
	//押されていければ、スピードを減速
	else
	{
		m_downwardSpeed -= m_frameTime * 0.002f;

		if (m_downwardSpeed < 0.0f)
		{
			m_downwardSpeed = 0.0f;
		}
	}

	//位置更新
	m_positionY -= m_downwardSpeed;

	return;
}

//==============================================================================
//  関数名        MoveLeftwards
//  説明          左移動
//------------------------------------------------------------------------------
//	引数
//          bool         keydown         キーが押されているかどうか
//	戻り値
//          なし
//==============================================================================
void CPosition::MoveLeftwards(bool keydown)
{
	float radians;

	//キーが押されたら、スピードを加速
	if (keydown)
	{
		m_leftwardSpeed += m_frameTime * 0.003f;

		if (m_leftwardSpeed > (m_frameTime * 0.03f))
		{
			m_leftwardSpeed = m_frameTime * 0.03f;
		}
	}
	//押されていければ、スピードを減速
	else
	{
		m_leftwardSpeed -= m_frameTime * 0.002f;

		if (m_leftwardSpeed < 0.0f)
		{
			m_leftwardSpeed = 0.0f;
		}
	}

	radians = m_rotationY * 0.0174532925f;
	//位置更新
	m_positionX -= cosf(radians) * m_leftwardSpeed;
	m_positionZ -= sinf(radians) * m_leftwardSpeed;


	return;
}

//==============================================================================
//  関数名        MoveRightwards
//  説明          右移動
//------------------------------------------------------------------------------
//	引数
//          bool         keydown         キーが押されているかどうか
//	戻り値
//          なし
//==============================================================================
void CPosition::MoveRightwards(bool keydown)
{
	float radians;

	//キーが押されたら、スピードを加速
	if (keydown)
	{
		m_rightwardSpeed += m_frameTime * 0.003f;

		if (m_rightwardSpeed > (m_frameTime * 0.03f))
		{
			m_rightwardSpeed = m_frameTime * 0.03f;
		}
	}
	//押されていければ、スピードを減速
	else
	{
		m_rightwardSpeed -= m_frameTime * 0.002f;

		if (m_rightwardSpeed < 0.0f)
		{
			m_rightwardSpeed = 0.0f;
		}
	}

	radians = m_rotationY * 0.0174532925f;
	//位置更新
	m_positionX += cosf(radians) * m_rightwardSpeed;
	m_positionZ += sinf(radians) * m_rightwardSpeed;

	return;
}

//==============================================================================
//  関数名        TurnLeft
//  説明          左回転
//------------------------------------------------------------------------------
//	引数
//          bool         keydown         キーが押されているかどうか
//	戻り値
//          なし
//==============================================================================
void CPosition::TurnLeft(bool keydown)
{
	//キーが押されたら、回転スピードを加速
	if (keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.01f;
		if (m_leftTurnSpeed > (m_frameTime * 0.15f))
		{
			m_leftTurnSpeed = m_frameTime * 0.15f;

		}
	}
	//押されていければ、回転スピードを減速
	else
	{
		m_leftTurnSpeed -= m_frameTime * 0.005f;

		if (m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	//回転更新
	m_rotationY -= m_leftTurnSpeed;
	if (m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}

	return;
}

//==============================================================================
//  関数名        TurnRight
//  説明          右回転
//------------------------------------------------------------------------------
//	引数
//          bool         keydown         キーが押されているかどうか
//	戻り値
//          なし
//==============================================================================
void CPosition::TurnRight(bool keydown)
{
	//キーが押されたら、回転スピードを加速
	if (keydown)
	{
		m_rightTurnSpeed += m_frameTime * 0.01f;
		if (m_rightTurnSpeed > (m_frameTime * 0.15f))
		{
			m_rightTurnSpeed = m_frameTime * 0.15f;

		}
	}
	//押されていければ、回転スピードを減速
	else
	{
		m_rightTurnSpeed -= m_frameTime * 0.005f;

		if (m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	//回転更新
	m_rotationY += m_rightTurnSpeed;
	if (m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}

	return;

}

//==============================================================================
//  関数名        TurnUp
//  説明          上回転
//------------------------------------------------------------------------------
//	引数
//          bool         keydown         キーが押されているかどうか
//	戻り値
//          なし
//==============================================================================
void CPosition::TurnUp(bool keydown)
{
	//キーが押されたら、回転スピードを加速
	if (keydown)
	{
		m_lookUpSpeed += m_frameTime * 0.01f;
		if (m_lookUpSpeed > (m_frameTime * 0.15f))
		{
			m_lookUpSpeed = m_frameTime * 0.15f;

		}
	}
	//押されていければ、回転スピードを減速
	else
	{
		m_lookUpSpeed -= m_frameTime * 0.005f;

		if (m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	//回転更新
	m_rotationX -= m_lookUpSpeed;
	if (m_rotationX > 90.0f)
	{
		m_rotationX = 90.0f;
	}

	return;
}

//==============================================================================
//  関数名        TurnDown
//  説明          下回転
//------------------------------------------------------------------------------
//	引数
//          bool         keydown         キーが押されているかどうか
//	戻り値
//          なし
//==============================================================================
void CPosition::TurnDown(bool keydown)
{
	//キーが押されたら、回転スピードを加速
	if (keydown)
	{
		m_lookDownSpeed += m_frameTime * 0.01f;
		if (m_lookDownSpeed > (m_frameTime * 0.15f))
		{
			m_lookDownSpeed = m_frameTime * 0.15f;

		}
	}
	//押されていければ、回転スピードを減速
	else
	{
		m_lookDownSpeed -= m_frameTime * 0.005f;

		if (m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}

	//回転更新
	m_rotationX += m_lookDownSpeed;
	if (m_rotationX < -90.0f)
	{
		m_rotationX = -90.0f;
	}

	return;
}

//******************************************************************************
//	End of file.
//******************************************************************************