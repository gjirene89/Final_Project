//******************************************************************************
//	mathutil.cpp
//  数学系のユーティリティ関数群
//	2017-01-16
//	Irene Gersenowies
//******************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダー
//-----------------------------------------------------------------------------
//#include <d3dx9.h>
//#include "SideCamera.h"
#include "MathUtility.h"

//-----------------------------------------------------------------------------
//	グローバル変数
//-----------------------------------------------------------------------------
//D3DXMATRIX			g_MatProjection;			// プロジェクション変換行列

//==============================================================================
//!	@fn		MakeWorldMatrix
//!	@brief	角度と平行移動量から行列を作る
//!	@param　行列（出力）　　	
//!	@param　角度（入力）
//!	@param　平行移動量（入力）
//!	@retval	なし
//==============================================================================
void MakeWorldMatrix(XMMATRIX& mat, const XMFLOAT3& angle, const XMFLOAT3& trans)
{
	XMMATRIX matX, matY, matZ, matTrans;

	matX = XMMatrixRotationX(XM_PI*angle.x / 180.0f);
	matY = XMMatrixRotationY(XM_PI*angle.y / 180.0f);
	matZ = XMMatrixRotationZ(XM_PI*angle.z / 180.0f);
	mat = matX*matY*matZ;
	matTrans = XMMatrixTranslation(trans.x, trans.y, trans.z);

	mat = mat * matTrans;
}

//==============================================================================
//!	@fn		MakeWorldMatrix
//!	@brief	角度と平行移動量から行列を作る(積算行列を計算)
//!	@param　行列（出力）　　	
//!	@param　積算行列（出力）　　	
//!	@param　角度（入力）
//!	@param　平行移動量（入力）
//!	@retval	なし
//==============================================================================
void MakeWorldMatrix(XMMATRIX& mat, XMMATRIX& mattotal, const XMFLOAT3& angle, const XMFLOAT3& trans)
{
	XMMATRIX matX, matY, matZ, matTrans;

	matX = XMMatrixRotationX(XM_PI*angle.x / 180.0f);			// X軸回転行列を生成
	matY = XMMatrixRotationY(XM_PI*angle.y / 180.0f);			// Y軸回転行列を生成
	matZ = XMMatrixRotationZ(XM_PI*angle.z / 180.0f);			// Z軸回転行列を生成
	mat = matX*matY*matZ;										// 合成

	matTrans = XMMatrixTranslation(trans.x, trans.y, trans.z);

	mat = mat*matTrans;

	mattotal = mat*mattotal;
}


void TranslateMatrix(XMMATRIX& mat, const XMFLOAT3 translate)
{
	XMFLOAT4X4 tempMat;

	XMStoreFloat4x4(&tempMat, mat);

	tempMat._41 = translate.x;
	tempMat._42 = translate.y;
	tempMat._43 = translate.z;

	mat = XMLoadFloat4x4(&tempMat);
}

void SetSizeMatrix(XMMATRIX& mat, const XMFLOAT3 size)
{
	XMFLOAT4X4 tempMat;

	XMStoreFloat4x4(&tempMat, mat);

	tempMat._11 = size.x;
	tempMat._12 = size.y;
	tempMat._13 = size.z;

	mat = XMLoadFloat4x4(&tempMat);
}
/*
void SetProjectionMatrix(D3DXMATRIX mat)
{
g_MatProjection = mat;
}

D3DXMATRIX GetProjectionMatrix(void)
{
return g_MatProjection;
}

XMFLOAT3 GetScreenCoords(const XMFLOAT3& pos)
{
XMMATRIX mat;
XMFLOAT3 ans;

mat = CCamera::GetActiveCamera()->GetMatrix() * g_MatProjection;

D3DXVec3TransformCoord(&ans, &pos, &mat);

return ans;
}
*/
XMFLOAT4 RotationArc(XMVECTOR& v0, XMVECTOR& v1, float& d)
{
	XMVECTOR axis;
	XMVECTOR dotProduct;
	XMFLOAT4 q;

	//正規化
	v0 = XMVector3Normalize(v0);
	v1 = XMVector3Normalize(v1);

	axis = XMVector3Cross(v0, v1);
	//3DXVec3Cross(&Axis, &v0, &v1);
	dotProduct = XMVector3Dot(v0, v1);
	d = XMVectorGetX(dotProduct);
	//d = D3DXVec3Dot(&v0, &v1);

	if (d > 1.0f) d = 1.0f;
	if (d < -1.0f) d = -1.0f;

	float s = (float)sqrt((1 + d) * 2);

	XMStoreFloat4(&q, axis);
	q.x = q.x / s;
	q.y = q.y / s;
	q.z = q.z / s;
	q.w = s / 2;

	return q;
}


float CalculateDistance(XMFLOAT3 origin, XMFLOAT3 destination)
{
	XMFLOAT3 res;

	res.x = destination.x - origin.x;
	res.y = destination.y - origin.y;
	res.z = destination.z - origin.z;

	float distance = pow(res.x, 2) + pow(res.y, 2) + pow(res.z, 2);
	distance = sqrt(distance);

	return distance;
}

float CalculateDistance(XMFLOAT2 origin, XMFLOAT2 destination)
{
	XMFLOAT2 res;

	res.x = destination.x - origin.x;
	res.y = destination.y - origin.y;

	float distance = pow(res.x, 2) + pow(res.y, 2);
	distance = sqrt(distance);

	return distance;
}

float CalculateAngle(XMFLOAT3 base, XMFLOAT3 direction)
{
	direction.x -= base.x;
	direction.y -= base.y;
	direction.z -= base.z;

	base = { 1.0f,0.0f,0.0f };

	XMVECTOR dirVec, baseVec;
	dirVec = XMLoadFloat3(&direction);
	baseVec = XMLoadFloat3(&base);

	XMVECTOR dot = XMVector3Dot(baseVec, dirVec);
	float magnitude = CalculateDistance({ 0.0f, 0.0f, 0.0f }, direction);

	float angle = XMVectorGetX(dot) / magnitude;

	angle = acos(angle);

	if (direction.y < 0.0f)
		return -XMConvertToDegrees(angle);

	return XMConvertToDegrees(angle);


}

float CalculateDistance(XMFLOAT3 origin, XMFLOAT3 destination, XMFLOAT3& direction)
{
	XMFLOAT3 res;
	XMVECTOR dirVec;

	res.x = destination.x - origin.x;
	res.y = destination.y - origin.y;
	res.z = destination.z - origin.z;

	float distance = pow(res.x, 2) + pow(res.y, 2) + pow(res.z, 2);
	distance = sqrt(distance);

	dirVec = XMLoadFloat3(&res);
	dirVec = XMVector3Normalize(dirVec);
	XMStoreFloat3(&direction, dirVec);
	//D3DXVec3Normalize(&res, &res);
	//direction = res;

	return distance;
}
//******************************************************************************
//	End of file.
//******************************************************************************
