//************************************************************************//
//	LightClass.h
//	2016-11-09
//  2016-11-28 revisited
//	Irene Gersenowies
//************************************************************************//

#ifndef __LIGHT_CLASS_H__
#define __LIGHT_CLASS_H__

//=======================================================================//
//		インクルード
//=======================================================================//
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

//=======================================================================//
//	クラス名		CLight
//=======================================================================//
class CLight
{
public:
	CLight();
	CLight(const CLight& other);
	~CLight();

	void SetAmbientColor(float red, float green, float blue, float alpha);
	void SetDiffuseColor(float red, float green, float blue, float alpha);
	void SetPosition(float x, float y, float z);
	void SetLookAt(float x, float y, float z);
	void SetDirection(float x, float y, float z);
	void SetSpecularColor(float red, float green, float blue, float alpha);
	void SetSpecularPower(float power);

	XMFLOAT4 GetAmbientColor();
	XMFLOAT4 GetDiffuseColor();
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetDirection();
	XMFLOAT4 GetSpecularColor();
	float GetSpecularPower();

	void GenerateViewMatrix();
	void GenerateProjectionMatrix(float screenDepth, float screenNear);
	void GenerateOrthoMatrix(float width, float height, float depthPlane, float nearPlane);

	void GetViewMatrix(XMMATRIX& viewMatrix);
	void GetProjectionMatrix(XMMATRIX& projectionMatrix);
	void GetOrthoMatrix(XMMATRIX& orthoMatrix);

private:
	XMMATRIX m_viewMatrix;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_orthoMatrix;

	XMFLOAT3 m_position;
	XMFLOAT3 m_lookAt;
	XMFLOAT3 m_direction;

	XMFLOAT4 m_ambientColor;
	XMFLOAT4 m_diffuseColor;

	XMFLOAT4 m_specularColor;
	float m_specularPower;

	
};

#endif