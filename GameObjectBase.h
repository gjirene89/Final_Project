//************************************************************************//
//	GameObjectBase.h
//	2017-01-14
//	Irene Gersenowies
//************************************************************************//

#ifndef __GAME_OBJECT_BASE_H__
#define __GAME_OBJECT_BASE_H__

//=======================================================================//
//		インクルード
//=======================================================================//
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>

using namespace std;
using namespace DirectX;


//=======================================================================//
//	マクロ定数
//=======================================================================//
enum GAMEOBJTYPE
{
	GOBJ_NONE,
	GOBJ_CAMERA,			//カメラ　オブジェクト
	GOBJ_PLAYER,			//プレイヤー　オブジェクト
	GOBJ_UI,				//UI
	GOBJ_BOUNDS,			//境界球　オブジェクト
	GOBJ_BLOCK,				//すてージブロック
	GOBJ_SACK,
	GOBJ_GOAL,
	GOBJ_BEAD,
	GOBJ_SKYDOME,

	GAMEOBJ_MAX				//オブジェクトの最大数
};

/*
//オブジェクトの状態
enum OBJ_STATE
{
	STATE_ALIVE,			//生きている
	STATE_DEAD,				//死んでいる

	STATE_MAX				//最大状態数

};
*/

//=======================================================================//
//	クラス名		CGameObjectBase
//=======================================================================//
class CGameObjectBase
{

public: 
	CGameObjectBase(void);
	CGameObjectBase(GAMEOBJTYPE objType);
	CGameObjectBase(const CGameObjectBase& other);
	~CGameObjectBase(void);


	virtual bool InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext) = 0;
	virtual void Shutdown() = 0;

	virtual void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)=0;
	//virtual void Render(ID3D11DeviceContext* deviceContext, ID3D11Buffer* vertexBuffer);

	virtual void Initialize(void);
	virtual void Input(void);
	virtual void Action(void);
	virtual void PostAction(void);

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	void GetPosition(float& x, float& y, float& z);
	void GetRotation(float& x, float& y, float& z);

	void CalculateWorldMatrix(XMMATRIX& worldMatrix);

	//ポインタ用

	CGameObjectBase* GetNextObj();						//次のオブジェクトのデータを戻す関数
	void SetNextObj(CGameObjectBase* nextObj);			//次のオブジェクトのポインタをセットする関数

private: 


protected:
	GAMEOBJTYPE			m_objType;							//ゲームオブジェクトの種類
	bool				m_isHidden;						//true: 描画しない		false：描画する
	CGameObjectBase*	m_pNextObj;						//次のオブジェクトへのポインタ

	float m_positionX;
	float m_positionY;
	float m_positionZ;

	float m_rotationX;
	float m_rotationY;
	float m_rotationZ;
};

#endif


//******************************************************************************
//	End of file.
//******************************************************************************
