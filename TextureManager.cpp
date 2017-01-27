//*****************************************************************************
//!	@file	TextureManager.cpp
//!	@brief	テクスチャー管理クラスの関数群
//!	@note	
//!	@author	イレネ　ヘルセノウイス
//*****************************************************************************

//-----------------------------------------------------------------------------
//	ヘッダ－
//-----------------------------------------------------------------------------
# include "TextureManager.h"
# include "CDirectxGraphics.h"
# include <string>

//-----------------------------------------------------------------------------
//	グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 TexManager::texture[TexManager::TEX_MAX];

//==============================================================================
//!	@fn		TexManager
//!	@brief	テクスチャ管理クラスのコンストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
TexManager::TexManager()
{
	//ポインタを初期化する
	for (int texNo = 0; texNo < TEX_MAX; texNo++)
	{
		texture[texNo] = nullptr;
	}

	//テクスチャ名を入力する
	LPCSTR tempTex[TEX_MAX];
	tempTex[TEX_TITLE]				= "assets/textures/title.jpg"; 
	tempTex[TEX_GAMEOVER]			= "assets/textures/gameOver.jpg";
	tempTex[TEX_GAMECLEAR]			= "assets/textures/gameClear.jpg";
	tempTex[TEX_BACKGROUND]			= "assets/textures/clothBase.jpg";
	tempTex[TEX_CLOUD_0]			= "assets/textures/cloud0.tga";
	tempTex[TEX_CLOUD_1]			= "assets/textures/cloud1.tga";
	tempTex[TEX_SUN]				= "assets/textures/sun.tga";
	tempTex[TEX_PLAYER_COLOR]		= "assets/textures/PlayerColor.tga";
	tempTex[TEX_PLAYER_BUMP]		= "assets/textures/PlayerBump.png";
	tempTex[TEX_SACK_COLOR_BLUE]	= "assets/textures/SackColorBlue.tga";
	tempTex[TEX_SACK_COLOR_PURPLE]	= "assets/textures/SackColorPurple.tga";
	tempTex[TEX_SACK_COLOR_GREEN]	= "assets/textures/SackColorGreen.tga";

	//クラスの変数にコピーする
	memcpy(texName, tempTex, sizeof(LPCSTR)*TEX_MAX);
	
}

//==============================================================================
//!	@fn		~TexManager
//!	@brief	テクスチャ管理クラスのデストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
TexManager::~TexManager()
{
	//テクスチャの情報を解放する
	for (int texNo = 0; texNo < TEX_MAX; texNo++)
	{
		if (texture[texNo] != nullptr)
		{
			texture[texNo]->Release();
			texture[texNo] = nullptr;
		}
	}
}

//==============================================================================
//!	@fn		Init
//!	@brief	テクスチャ管理クラスの初期関数
//!	@param	HWND	ウインドーハンドル
//!	@retval	なし
//!	@note	
//==============================================================================
bool TexManager::Init(HWND hwnd)
{
	//テクスチャをロードする
	for (int texNo = 0; texNo < TEX_MAX; texNo++)
	{
		//見つからない場合、エラーメッセージを出す
		if (FAILED(D3DXCreateTextureFromFile(CDirectXGraphics::GetDXDevice(), texName[texNo], &texture[texNo])))
		{
			char error[128];
			strcpy_s(error, (char *)texName[texNo]);
			strcat_s(error, " was not found!");
			MessageBox(hwnd, error, "ERROR!!", MB_OK);
			return false;
		}

	}
	return true;
}

//==============================================================================
//!	@fn		GetTexture
//!	@brief	テクスチャのポインタを戻す関数
//!	@param	なし
//!	@retval	LPDIRECT3DTEXTURE　　テクスチャポインタ
//!	@note	
//==============================================================================
LPDIRECT3DTEXTURE9 TexManager::GetTexture(TEX_ID texId)
{
	return texture[texId];
}
//******************************************************************************
//	End of file.
//******************************************************************************
