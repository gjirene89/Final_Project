//*****************************************************************************
//  TitleScene.h
//  2017-01-14
//  Irene Gersenowies
//*****************************************************************************

//=======================================================================//
//		インクルード
//=======================================================================//
# include "TitleScene.h"


//==============================================================================
//	関数名		CTitleScene
//	説明	        タイトルシーンのコンストラクタ
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
CTitleScene::CTitleScene()
{
	//シーン名を設定する
	sceneName = SCENE_TITLE;

	//オブジェクトリストの初期化
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
bool CTitleScene::Initialize()
{
	m_Camera->SetPosition(150, 50, -200);

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
CScene* CTitleScene::ChangeScene(bool isChange)
{
	if (!isChange)
		return this;
	
	return GetScene(SCENE_GAME);
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
bool CTitleScene::LoadScene(void)
{
	bool result;

	//カメラオブジェクトの生成
	m_Camera = new CCamera;
	if (!m_Camera)
	{
		return false;
	}

	////オブジェクトの追加
	//objArray = new CStage();

	//result = objArray->InitializeObject(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext());// , "Resources/Model/square.txt");
	//if (!result)
	//{
	//	//error message
	//	return false;
	//}
	////objArray->LoadColorMap(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "Resources/Texture/sun.tga");

	
	return true;
}


//******************************************************************************
//	End of file.
//******************************************************************************