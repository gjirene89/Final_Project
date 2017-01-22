//************************************************************************//
//	GameObjectBase.cpp
//	2017-01-14
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		インクルード
//=======================================================================//
#include "GameObjectBase.h"
#include "ShaderManagerClass.h"

//==============================================================================
//  関数名        CGameObjectBase	
//  説明          CGameObjectBaseクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CGameObjectBase::CGameObjectBase()
{
	m_objType = GOBJ_NONE;
	m_isHidden = false;
	m_pNextObj = nullptr;

	m_positionX = 0;
	m_positionY = 0;
	m_positionZ = 0;

	m_rotationX = 0;
	m_rotationY = 0;
	m_rotationZ = 0;

}

CGameObjectBase::CGameObjectBase(GAMEOBJTYPE objType)
{
	
	m_objType = objType;
	m_isHidden = false;
	m_pNextObj = nullptr;

	m_positionX = 0;
	m_positionY = 0;
	m_positionZ = 0;

	m_rotationX = 0;
	m_rotationY = 0;
	m_rotationZ = 0;
}

//==============================================================================
//  関数名        CGameObjectBase	
//  説明          CGameObjectBaseクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          CGameObjectBase& other			CGameObjectBaseのインスタンス
//	戻り値
//          なし
//==============================================================================
CGameObjectBase::CGameObjectBase(const CGameObjectBase& other)
{
	//空
}

//==============================================================================
//  関数名        ～CGameObjectBase	
//  説明          CGameObjectBaseクラスのデストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CGameObjectBase::~CGameObjectBase()
{
	//空
}


void CGameObjectBase::Initialize()
{
	return;
}

void CGameObjectBase::Input()
{
	//今は空
}

void CGameObjectBase::Action()
{

}

void CGameObjectBase::PostAction()
{

}


//==============================================================================
//  関数名        SetPosition
//  説明          モデルの位置をセットする関数
//------------------------------------------------------------------------------
//	引数
//          float      x            X軸
//          float      y            Y軸
//          float      z            Z軸
//	戻り値
//          なし
//==============================================================================
void CGameObjectBase::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;

	return;
}

//==============================================================================
//  関数名        SetRotation
//  説明          モデルの回転をセットする関数
//------------------------------------------------------------------------------
//	引数
//          float      x            X軸
//          float      y            Y軸
//          float      z            Z軸
//	戻り値
//          なし
//==============================================================================
void CGameObjectBase::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;

	return;
}


//==============================================================================
//  関数名        GetPosition
//  説明          モデルの位置を戻す関数
//------------------------------------------------------------------------------
//	引数
//          float&      x            X軸
//          float&      y            Y軸
//          float&      z            Z軸
//	戻り値
//          なし
//==============================================================================
void CGameObjectBase::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;

	return;
}

//==============================================================================
//  関数名        GetRotation
//  説明          モデルの位置を戻す関数
//------------------------------------------------------------------------------
//	引数
//          float&      x            X軸回転
//          float&      y            Y軸回転
//          float&      z            Z軸回転
//	戻り値
//          なし
//==============================================================================
void CGameObjectBase::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;

	return;
}

//==============================================================================
//  関数名        CalculateWorldMatrix
//  説明          ワールド配列を計算する関数
//------------------------------------------------------------------------------
//	引数
//          float&      x            X軸回転
//          float&      y            Y軸回転
//          float&      z            Z軸回転
//	戻り値
//          なし
//==============================================================================
void CGameObjectBase::CalculateWorldMatrix(XMMATRIX& worldMatrix)
{
	float yaw, pitch, roll;
	XMMATRIX translationMatrix, rotationMatrix;

	//yaw (Y軸), pitch (X軸), roll (Z軸) をラジアンに変換する
	pitch = m_rotationX * XM_PI / 180.0f;
	yaw = m_rotationY * XM_PI / 180.0f;
	roll = m_rotationZ * XM_PI / 180.0f;

	//yaw, pitch, rollで回転行列を作成する
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	//移動行列
	translationMatrix = XMMatrixTranslation(m_positionX, m_positionY, m_positionZ);

	//ワールド行列を求める
	worldMatrix = rotationMatrix * translationMatrix;

	return;
}
//*****************************************************************************
//		取得関数群
//*****************************************************************************

//==============================================================================
//!	@fn		SetNextObj
//!	@brief	次のゲームオブジェクトのポインタをセットする
//!	@param	なし
//!	@retval	なし
//==============================================================================
void CGameObjectBase::SetNextObj(CGameObjectBase* nextObj)
{
	//次のオブジェクトのポインタをセットする
	m_pNextObj = nextObj;
}


//==============================================================================
//!	@fn		GetNextObj
//!	@brief	次のゲームオブジェクトのポインタを戻す関数
//!	@param	なし
//!	@retval	なし
//==============================================================================
CGameObjectBase* CGameObjectBase::GetNextObj(void)
{
	//次のオブジェクトのポインタを戻す
	return m_pNextObj;
}



//******************************************************************************
//	End of file.
//******************************************************************************