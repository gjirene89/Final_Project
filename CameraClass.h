//************************************************************************//
//	CameraClass.h
//	2016-11-08
//  2016-11-28 revisited
//	Irene Gersenowies
//************************************************************************//

#ifndef __CAMERA_CLASS_H__
#define __CAMERA_CLASS_H__

//=======================================================================//
//		インクルード
//=======================================================================//
# include <DirectXMath.h>
using namespace DirectX;

//=======================================================================//
//	クラス名		CCamera
//=======================================================================//
class CCamera
{
public:
	CCamera(void);
	CCamera(const CCamera& other);
	~CCamera(void);

	void SetPosition(float fPosX, float fPosY, float fPosZ);
	void SetRotation(float fRotX, float fRotY, float fRotZ);

	void GetPosition(float& fPosX, float& fPosY, float& fPosZ);
	XMFLOAT3 GetPosition();
	void GetRotation(float& fRotX, float& fRotY, float& fRotZ);

	void Render(void);
	void GetViewMatrix(XMMATRIX& viewMatrix);

	void RenderReflectionMatrix(float fHeight);
	void GetReflectionViewMatrix(XMMATRIX& reflectionMatrix);

	void RenderBaseViewMatrix(void);
	void GetBaseViewMatrix(XMMATRIX& viewMatrix);

private:
	float m_fPosX, m_fPosY, m_fPosZ;
	float m_fRotX, m_fRotY, m_fRotZ;

	XMMATRIX m_viewMatrix;
	XMMATRIX m_reflectionViewMatrix;
	XMMATRIX m_baseViewMatrix;
};


#endif // !__CAMERA_CLASS_H__

//******************************************************************************
//	End of file.
//******************************************************************************
