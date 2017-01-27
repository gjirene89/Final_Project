//*****************************************************************************
//!	@file	TextureManager.h
//!	@brief	テクスチャ管理関数
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

# ifndef __GM31_TEX_MANAGER__
# define __GM31_TEX_MANAGER__

//-----------------------------------------------------------------------------
//	ヘッダ－
//-----------------------------------------------------------------------------
#include	<d3d9.h>
#include	<d3dx9.h>

//=============================================================================
//!	@class	TexManager
//!	@brief	テクスチャ管理クラス
//=============================================================================
class TexManager
{
public:

	//テクスチャのID
	enum TEX_ID
	{
		TEX_TITLE,				//タイトルの画面
		TEX_GAMEOVER,			//ゲームオーバーの画面
		TEX_GAMECLEAR,			//ゲームクリアの画面
		TEX_BACKGROUND,			//背景ベース
		TEX_CLOUD_0,			//雲バーション１
		TEX_CLOUD_1,			//雲バーション２
		TEX_SUN,				//太陽
		TEX_PLAYER_COLOR,		//プレイヤーの色
		TEX_PLAYER_BUMP,		//バンプマップ
		TEX_SACK_COLOR_BLUE,	
		TEX_SACK_COLOR_PURPLE,
		TEX_SACK_COLOR_GREEN,

		TEX_MAX					//テクスチャの最大数
	};

	~TexManager(void);				//デストラクタ
	
	bool Init(HWND hwnd);		//初期化関数
	static LPDIRECT3DTEXTURE9 GetTexture(TEX_ID texId);	//テクスチャ情報の取得関数

private:

	TexManager(void);				//コンストラクタ

	static LPDIRECT3DTEXTURE9 texture[TEX_MAX];			//テクスチャ配列
	LPCSTR texName[TEX_MAX];							//テクスチャのファイル名配列
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************