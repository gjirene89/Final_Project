//************************************************************************//
//	GameScene.cpp
//	2017-01-14
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		インクルード
//=======================================================================//
# include "GameScene.h"


//==============================================================================
//	関数名		CGameScene
//	説明	        ゲームシーンのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CGameScene::CGameScene()
{
	sceneName = SCENE_GAME;

	objArray = nullptr;

	return;
}


//==============================================================================
//	関数名		Initialize
//	説明	        シーンのゲームオブジェクトの初期化を呼ぶ出す
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//			bool	true 成功　　　false 失敗
//==============================================================================
bool CGameScene::Initialize()
{
	m_Camera->SetPosition(50, 50, -50);

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
CScene* CGameScene::ChangeScene(bool isChange)
{
	if (!isChange)
		return this;
	
	return GetScene(SCENE_CLEAR);
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
bool CGameScene::LoadScene(void)
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
	objArray = new CStage();
	if (objArray == nullptr)
	{
		//error message
		return false;
	}

	objArray->SetNextObj(new CPlayer(4,5));
	tempObj = objArray->GetNextObj();
	if(tempObj == nullptr)
	{
		//error message
		return false;
	}
		
	//objArray->LoadColorMap(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "Resources/Texture/sun.tga");

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