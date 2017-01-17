//************************************************************************//
//	StageClass.h
//	2017-01-14
//	Irene Gersenowies
//************************************************************************//

#ifndef __STAGE_CLASS_H__
#define __STAGE_CLASS_H__

//=============================================================================
//		インクルード
//=============================================================================
# include "BlockClass.h"
//# include "C3DObject.h"
//# include "CDirectxGraphics.h"

//=============================================================================
//	マクロ定数
//=============================================================================
# define MAX_BLOCKS_W	45
# define MAX_BLOCKS_H	10

//=============================================================================
//!	@class	CStage
//!	@brief ステージクラス
//=============================================================================
class CStage :  public CGameObjectBase
{
public:

	//ステージＩＤ
	enum STAGE
	{
		STAGE_1,		//ステージ１

		STAGE_MAX		//ステージ最大数
	};
	
	CStage(void);			//コンストラクタ
	CStage(const CStage& other) {};
	~CStage(void);			//デストラクタ

	bool InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Shutdown();

	void Initialize(void);		//初期化関数
	void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix); //描画関数
	void Action(void);		//処理関数
	void PostAction(void);	//後処理関数

	static STAGE currStage;								//現在のステージ
	static bool isThereBlock(float PosX, float PosY);		//特定ところにブロックがあるかどうかを戻す
	static void setCurrStage();							//現在ステージをセットする関数
	static void ClearBlock(int PosX, int PosY);			//ブロックをハイライトする
	static void CleanNumbers(float* posX, float* posY);

private:
	static CBlock *redBlock;				//赤ブロックのインスタンス
	static CBlock *invisibleBlock;			//見えない壁のインスタンス
	static CBlock *greenBlock;			//緑ブロックのインスタンス
	
	static CBlock *stage[MAX_BLOCKS_H][MAX_BLOCKS_W];	//ステージ１

};

#endif