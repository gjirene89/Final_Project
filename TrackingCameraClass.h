//************************************************************************//
//	TrackingCameraClass.h
//	2017-01-30
//	Irene Gersenowies
//************************************************************************//

#ifndef __TRACKING_CAMERA_CLASS_H__
#define __TRACKING_CAMERA_CLASS_H__

//=======================================================================//
//		インクルード
//=======================================================================//
# include "CameraClass.h"
# include "GameObjectBase.h"
# include <DirectXMath.h>
using namespace DirectX;

//=======================================================================//
//	クラス名		CCamera
//=======================================================================//
class CTrackingCamera : public CCamera
{
public:
	CTrackingCamera(void);
	CTrackingCamera(const CTrackingCamera& other);
	~CTrackingCamera(void);

	void Initialize(void);
	void Action(void);
	void SetTarget(CGameObjectBase* target);

private:
	void UpdateTargetPosition(void);
	void UpdateCameraPosition(void);

private:
	CGameObjectBase* m_Target;

	bool m_startTracking;

	float m_targetX;
	float m_targetY;
	float m_targetZ;

	XMFLOAT3 m_velocity;
};

#endif