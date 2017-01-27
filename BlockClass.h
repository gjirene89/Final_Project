//******************************************************************************
//	BlockClass.h
//	2017-01-16
//	Irene Gersenowies
//******************************************************************************

#ifndef __CBLOCK_H__
#define __CBLOCK_H__

//==============================================================================
//		インクルード
//==============================================================================
//# include "C3DObject.h"
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
class CBlock : public CGameObjectBase
{
public:

	//ブロック色のＩＤ
	enum BLOCK_COLOR
	{
		BLOCK_NONE,
		BLOCK_GREEN,				//緑
		BLOCK_RED,					//赤
		BLOCK_INVISIBLE,			//見えない壁

		BLOCK_COLOR_MAX				//色の最大数

	};

	CBlock(void) {};
	CBlock(const CBlock& other) {};
	CBlock(BLOCK_COLOR color);		//コンストラクタ
	~CBlock(void);					//デストラクタ

	bool InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Shutdown();

	void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix); //描画関数
	
private:

	//BLOCK_COLOR m_color;
	XMFLOAT4 m_color;
	CModel* m_model;

	CTexture* m_colorTexture;
	CTexture* m_bumpTexture;

	void SetColor(BLOCK_COLOR color);	//ブロックの色を変える関数

};

#endif
//******************************************************************************
//	End of file.
//******************************************************************************