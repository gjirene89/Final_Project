//*****************************************************************************
//  GameClearScene.cpp
//  2017-01-14
//  Irene Gersenowies
//*****************************************************************************

//=======================================================================//
//		インクルード
//=======================================================================//
# include "GameClearScene.h"

//==============================================================================
//	関数名		CGameClearScene
//	説明	        ゲームクリアシーンのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CGameClearScene::CGameClearScene()
{
	sceneName = SCENE_CLEAR;

	objArray = nullptr;

	return;
}

//==============================================================================
//	関数名		Initialize
//	説明	        ゲームクリアシーンの初期化
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CGameClearScene::Initialize(void)
{
	m_Camera->SetPosition(0, 0, -10);

	CScene::Initialize();

	return true;
}

//==============================================================================
//	関数名		ChangeScene
//	説明	        シーン遷移
//------------------------------------------------------------------------------
//	引数
//          bool    isChange		遷移するかどうかを示すフラグ
//	戻り値
//			CScene*	　              新しいシーン
//==============================================================================
CScene* CGameClearScene::ChangeScene(bool isChange)
{
	if (!isChange)
		return this;

	return GetScene(SCENE_TITLE);
}

//==============================================================================
//	関数名		LoadScene
//	説明	        シーンのオブジェクトをロードする
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CGameClearScene::LoadScene(void)
{
	bool result;
	CGameObjectBase* tempObj;

	//カメラオブジェクトの生成
	m_Camera = new CCamera;
	if (!m_Camera)
	{
		return false;
	}

	//オブジェクトの追加
	objArray = new CPlane(10, 10);
	if (!objArray)
	{
		return false;
	}

	//板ポリのテクスチャ追加
	result = ((CPlane*)objArray)->LoadColorTexture(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "Resources/Texture/wallColor.tga", 10, 10);
	if (!result)
	{
		return false;
	}


	//オブジェクトの初期化
	tempObj = objArray;
	while (tempObj)
	{
		result = tempObj->InitializeObject(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext());
		if (!result)
		{
			//error message
			return false;
		}
		tempObj = tempObj->GetNextObj();
	}

	return true;
}

//******************************************************************************
//	End of file.
//******************************************************************************