//******************************************************************************
//	mathutil.h
//  数学系のユーティリティ関数群
//	2017-01-16
//	Irene Gersenowies
//******************************************************************************
#ifndef __MATH_UTILITY__
#define __MATH_UTILITY__

//==============================================================================
//		インクルード
//==============================================================================
//#include	<d3dx9.h>
# include <DirectXMath.h>

using namespace DirectX;
//==============================================================================
// マクロ定数
//==============================================================================


//==============================================================================
// プロトタイプ宣言
//==============================================================================
float CalculateDistance(XMFLOAT3 origin, XMFLOAT3 destination);
float CalculateDistance(XMFLOAT2 origin, XMFLOAT2 destination);
float CalculateAngle(XMFLOAT3 origin, XMFLOAT3 destination);
float CalculateDistance(XMFLOAT3 origin, XMFLOAT3 destination, XMFLOAT3& angle);

void MakeWorldMatrix(XMMATRIX& mat, const XMFLOAT3& angle, const XMFLOAT3& trans);
void MakeWorldMatrix(XMMATRIX& mat, XMMATRIX& mattotal, const XMFLOAT3& angle, const XMFLOAT3& trans);
void TranslateMatrix(XMMATRIX& mat, const XMFLOAT3 translate);
void SetSizeMatrix(XMMATRIX& mat, const XMFLOAT3 scale);

//void SetProjectionMatrix(XMMATRIX mat);
//XMMATRIX GetProjectionMatrix(void);
//XMFLOAT3 GetScreenCoords(const XMFLOAT3& pos);
XMFLOAT4 RotationArc(XMVECTOR& v0, XMVECTOR& v1, float& d);

#endif
//******************************************************************************
//	End of file.
//******************************************************************************
