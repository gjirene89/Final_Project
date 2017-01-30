//******************************************************************************
//	PlaneClass.h
//	2017-01-30
//	Irene Gersenowies
//******************************************************************************

#ifndef __PLANE_CLASS_H__
#define __PLANE_CLASS_H__

//==============================================================================
//		インクルード
//==============================================================================
# include "GameObjectBase.h"
# include "Macros.h"
# include "ModelClass.h"
# include "TextureClass.h"

//==============================================================================
//	マクロ定数
//==============================================================================

//==============================================================================
//	クラス名		CBlock
//==============================================================================
class CPlane : public CGameObjectBase
{
public:

	CPlane(void) {};
	CPlane(const CPlane& other) {};
	CPlane(float sizeX, float sizeY);		//コンストラクタ
	~CPlane(void);					//デストラクタ

	bool InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Shutdown();

	bool LoadColorTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename, int repeatU, int repeatV);
	bool LoadBumpTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename, int repeatU, int repeatV);
	void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition, CLight* light); //描画関数

private:

	CModel* m_model;

	CTexture* m_colorTexture;
	CTexture* m_bumpTexture;

	float m_sizeX;
	float m_sizeY;
};

#endif
//******************************************************************************
//	End of file.
//******************************************************************************