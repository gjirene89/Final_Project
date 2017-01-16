//************************************************************************//
//	CameraClass.cpp
//	2016-11-08
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//   インクルード
//=======================================================================//
#include "CameraClass.h"

//==============================================================================
//  関数名        CCamera	
//  説明          CCameraクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CCamera::CCamera()
{
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_fPosZ = 0.0f;

	m_fRotX = 0.0f;
	m_fRotY = 0.0f;
	m_fRotZ = 0.0f;
}

//==============================================================================
//  関数名        CCamera	
//  説明          CCameraクラスのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          CCamera& other			CCameraのインスタンス
//	戻り値
//          なし
//==============================================================================
CCamera::CCamera(const CCamera& other)
{
	//空
}

//==============================================================================
//  関数名        ～CCamera	
//  説明          CCameraクラスのデストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CCamera::~CCamera()
{
	//空
}

//==============================================================================
//  関数名        SetPostion	
//  説明			  カメラの位置をセットする関数
//------------------------------------------------------------------------------
//	引数
//			float fPosX			X軸位置
//			float fPosY			y軸位置
//			float fPosZ			z軸位置
//	戻り値
//          なし
//==============================================================================
void CCamera::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	m_fPosX = fPosX;
	m_fPosY = fPosY;
	m_fPosZ = fPosZ;

	return;
}

//==============================================================================
//  関数名        SetRotation	
//  説明			  カメラの回転度をセットする関数
//------------------------------------------------------------------------------
//	引数
//			float fRotX			X軸回転
//			float fRotY			y軸回転
//			float fRotZ			z軸回転
//	戻り値
//          なし
//==============================================================================
void CCamera::SetRotation(float fRotX, float fRotY, float fRotZ)
{
	m_fRotX = fRotX;
	m_fRotY = fRotY;
	m_fRotZ = fRotZ;

	return;
}

//==============================================================================
//  関数名        GetPosition	
//  説明	          カメラの位置をゲットする
//------------------------------------------------------------------------------
//	引数
//			float& fPosX			X軸位置
//			float& fPosY			y軸位置
//			float& fPosZ			z軸位置
//	戻り値
//          なし
//==============================================================================
void CCamera::GetPosition(float& fPosX, float& fPosY, float& fPosZ)
{
	fPosX = m_fPosX;
	fPosY = m_fPosY;
	fPosZ = m_fPosZ;

	return;
}

//==============================================================================
//  関数名        GetPosition	
//  説明	          カメラの位置をゲットする
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          XMFLOAT3       position          カメラの位置
//==============================================================================
XMFLOAT3 CCamera::GetPosition()
{
	return XMFLOAT3(m_fPosX, m_fPosY, m_fPosZ);
}

//==============================================================================
//  関数名        GetRotation	
//  説明	          カメラの回転度をゲットする
//------------------------------------------------------------------------------
//	引数
//			float& fRotX			X軸回転
//			float& fRotY			y軸回転
//			float& fRotZ			z軸回転
//	戻り値
//          なし
//==============================================================================
void CCamera::GetRotation(float& fRotX, float& fRotY, float& fRotZ)
{
	fRotX = m_fRotX;
	fRotY = m_fRotY;
	fRotZ = m_fRotZ;

	return;
}

//==============================================================================
//  関数名        Render	
//  説明	         カメラ行列を作成する関数
//------------------------------------------------------------------------------
//	引数
//			なし
//	戻り値
//          なし
//==============================================================================
void CCamera::Render()
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	//上向きのベクトルを定義する
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	//XMVECTORへの変換
	upVector = XMLoadFloat3(&up);

	//カメラの位置をベクトルにセットする
	position.x = m_fPosX;
	position.y = m_fPosY;
	position.z = m_fPosZ;

	//XMVECTORへの変換
	positionVector = XMLoadFloat3(&position);

	//カメラの向いている位置を設定する
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	//XMVECTORへの変換
	lookAtVector = XMLoadFloat3(&lookAt);

	//yaw (Y軸), pitch (X軸), roll (Z軸) をラジアンに変換する
	pitch = m_fRotX * XM_PI / 180.0f;
	yaw   = m_fRotY * XM_PI / 180.0f;
	roll  = m_fRotZ * XM_PI / 180.0f;

	//yaw, pitch, rollで回転行列を作成する
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	//lookAtベクトルと上向きベクトルを回転する
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	//カメラを移動する
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	//view行列を作成する
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}

//==============================================================================
//  関数名        GetViewMatrix	
//  説明	         View行列をゲットする関数
//------------------------------------------------------------------------------
//	引数
//			XMMATRIX& viewMatrix		View行列
//	戻り値
//          なし
//==============================================================================
void CCamera::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;

	return;
}

//==============================================================================
//  関数名        RenderBaseViewMatrix
//  説明	         平行投影描画用のView行列
//------------------------------------------------------------------------------
//	引数
//			なし
//	戻り値
//          なし
//==============================================================================
void CCamera::RenderBaseViewMatrix()
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float radians;
	XMMATRIX rotationMatrix;

	//上向きのベクトルを定義する
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	//XMVECTORへの変換
	upVector = XMLoadFloat3(&up);

	//カメラの位置をベクトルにセットする
	position.x = m_fPosX;
	position.y = m_fPosY;
	position.z = m_fPosZ;

	//XMVECTORへの変換
	positionVector = XMLoadFloat3(&position);

	//Calculate the rotation in radians
	radians = m_fRotY * XM_PI / 180.0f;

	//カメラの向いている位置を設定する
	lookAt.x = sinf(radians) + m_fPosX;
	lookAt.y = m_fPosY;
	lookAt.z = cosf(radians) + m_fPosZ;

	//XMVECTORへの変換
	lookAtVector = XMLoadFloat3(&lookAt);

	//view行列を作成する
	m_baseViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}

//==============================================================================
//  関数名       GetBaseViewMatrix	
//  説明	         平行投影描画用のView行列をゲットする関数
//------------------------------------------------------------------------------
//	引数
//			XMMATRIX& viewMatrix		View行列
//	戻り値
//          なし
//==============================================================================
void CCamera::GetBaseViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_baseViewMatrix;

	return;
}

//==============================================================================
//  関数名       RenderReflectionMatrix	
//  説明	         反射用のView行列を生成する関数
//------------------------------------------------------------------------------
//	引数
//			float height		高さ
//	戻り値
//          なし
//==============================================================================
void CCamera::RenderReflectionMatrix(float fHeight)
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	//上向きのベクトルを定義する
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	//XMVECTORへの変換
	upVector = XMLoadFloat3(&up);

	//カメラの位置をベクトルにセットする
	//反射の場合、Y軸の位置を反転する
	position.x =  m_fPosX;
	position.y = -m_fPosY + (fHeight * 2.0f);
	position.z =  m_fPosZ;

	//XMVECTORへの変換
	positionVector = XMLoadFloat3(&position);

	//カメラの向いている位置を設定する
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	//XMVECTORへの変換
	lookAtVector = XMLoadFloat3(&lookAt);

	//yaw (Y軸), pitch (X軸), roll (Z軸) をラジアンに変換する
	pitch = m_fRotX * XM_PI / 180.0f;
	yaw   = m_fRotY * XM_PI / 180.0f;
	roll  = m_fRotZ * XM_PI / 180.0f;

	//yaw, pitch, rollで回転行列を作成する
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	//lookAtベクトルと上向きベクトルを回転する
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	//カメラを移動する
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	//反射用のビュー行列を作成する
	m_reflectionViewMatrix = XMMatrixLookAtLH(positionVector, upVector, lookAtVector);

	return;
}

//==============================================================================
//  関数名       GetReflectionViewMatrix	
//  説明	        反射用のView行列をゲットする関数
//------------------------------------------------------------------------------
//	引数
//			XMMATRIX& reflectionMatrix          反射View行列
//	戻り値
//          なし
//==============================================================================
void CCamera::GetReflectionViewMatrix(XMMATRIX& reflectionMatrix)
{
	reflectionMatrix = m_reflectionViewMatrix;

	return;
}

//******************************************************************************
//	End of file.
//******************************************************************************