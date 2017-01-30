//************************************************************************//
//	SceneManager.cpp
//	2016-12-05
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		インクルード
//=======================================================================//
# include "SceneManager.h"
# include "TitleScene.h"
# include "GameScene.h"
# include "GameClearScene.h"
# include "ShaderManager.h"

//=======================================================================//
//		グローバル変数
//=======================================================================//
CScene* CScene::m_titleScene     = nullptr;
CScene* CScene::m_gameScene      = nullptr;
CScene* CScene::m_gameClearScene = nullptr;

CDirect3D*  CScene::m_Direct3D = nullptr;

//==============================================================================
//	関数名		InitializeSceneManager
//	説明	        シーン管理者の初期化
//------------------------------------------------------------------------------
//	引数
//          int		screenWidth			画面の幅
//			int		screenHeight		画面の高さ
//			HWND	hwnd				ウインドウハンドル
//	戻り値
//          なし
//==============================================================================
bool CScene::InitializeSceneManager(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	//DirectX　オブジェクト生成
	m_Direct3D = new CDirect3D;
	if (!m_Direct3D)
	{
		return false;
	}

	//DirectX　オブジェクトの初期化
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	//シェーダー管理者の初期化
	CShaderManager::getInstance().Initialize(m_Direct3D->GetDevice(), hwnd);

	return true;
}

//==============================================================================
//	関数名		Initialize
//	説明	        ゲームオブジェクトの初期化を呼び出す
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
bool CScene::Initialize()
{
	CGameObjectBase* tempObj;
	
	tempObj = objArray;
	while (tempObj)
	{
		tempObj->Initialize();
		tempObj = tempObj->GetNextObj();
	}

	m_Camera->Initialize();

	return true;
}

//==============================================================================
//	関数名		Input
//	説明	        ゲーム中の入力
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CScene::Input(CInput* input)
{
	CGameObjectBase* tempObj;
	tempObj = objArray;

	while (tempObj)
	{
		tempObj->Input(input);
		tempObj = tempObj->GetNextObj();
	}
	return;
}

//==============================================================================
//	関数名		Render
//	説明	        ゲームオブジェクトの描画を呼び出す
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          bool		true 成功          false　失敗
//==============================================================================
bool CScene::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	XMFLOAT3 cameraPosition;
	CGameObjectBase* tempObj;

	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_Camera->Render();
	
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	cameraPosition = m_Camera->GetPosition();

	tempObj = objArray;
	while (tempObj)
	{
		tempObj->Render(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, cameraPosition, m_Light);
		tempObj = tempObj->GetNextObj();
	}

	m_Direct3D->EndScene();

	return true;
}

//==============================================================================
//	関数名		Action
//	説明	        ゲームオブジェクトの処理関数を呼び出す
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CScene::Action()
{
	CGameObjectBase* tempObj;
	
	m_Camera->Action();

	tempObj = objArray;
	while (tempObj)
	{
		tempObj->Action();
		tempObj = tempObj->GetNextObj();
	}

	return;
}

//==============================================================================
//	関数名		PostAction
//	説明	        ゲームオブジェクトの後処理関数を呼び出す
//------------------------------------------------------------------------------
//	引数
//          なし
//	戻り値
//          なし
//==============================================================================
void CScene::PostAction()
{
	CGameObjectBase* tempObj;
	tempObj = objArray;

	while (tempObj)
	{
		tempObj->PostAction();
		tempObj = tempObj->GetNextObj();
	}

	return;
}

//==============================================================================
//	関数名		GetScene
//	説明	        現在のシーンへのポインタを戻す
//------------------------------------------------------------------------------
//	引数
//          SCENE_NAME   sceneName      シーン名
//	戻り値
//          CScene*      シーンへのポインタ
//==============================================================================
CScene* CScene::GetScene(SCENE_NAME sceneName)
{
	bool result;
	//シーンのポインタを戻す。シーンが存在しない場合、生成する
	switch (sceneName)
	{
		case SCENE_TITLE : 
			if (m_titleScene == nullptr)
			{
				m_titleScene = new CTitleScene();
				result = m_titleScene->LoadScene();
				if (!result)	return nullptr;
			}
			return m_titleScene;

		case SCENE_GAME  : 
			if (m_gameScene == nullptr)
			{
				m_gameScene = new CGameScene();
				result = m_gameScene->LoadScene();
				if (!result)	return nullptr;
			}
			return m_gameScene;

		case SCENE_CLEAR : 
			if (m_gameClearScene == nullptr)
			{
				m_gameClearScene = new CGameClearScene();
				result = m_gameClearScene->LoadScene();
				if (!result)	return nullptr;
			}
			return m_gameClearScene;
	}

	return nullptr;
}

//==============================================================================
//	関数名		Shutdown
//	説明	        シーンを解放する
//------------------------------------------------------------------------------
//	引数
//          SCENE_NAME   sceneName      シーン名
//	戻り値
//          CScene*      シーンへのポインター
//==============================================================================
void CScene::Shutdown()
{
	CShaderManager::getInstance().Shutdown();

	//DirectXのオブジェクトを解放する
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = nullptr;
	}
	
	//シーンへのポインターを解放
	if (m_titleScene != nullptr)
	{
		m_titleScene->ShutdownSceneObjects();
		delete m_titleScene;
	}

	if (m_gameScene != nullptr)
	{
		m_gameScene->ShutdownSceneObjects();
		delete m_gameScene;
	}

	if (m_gameClearScene != nullptr)
	{
		m_gameClearScene->ShutdownSceneObjects();
		delete m_gameClearScene;
	}


	return;

}

void CScene::ShutdownSceneObjects(void)
{
	CGameObjectBase* nextObj;

	while (objArray)
	{
		nextObj = objArray->GetNextObj();
		delete objArray;
		objArray = nextObj;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = nullptr;
	}

	if (m_Light)
	{
		delete m_Light;
		m_Light = nullptr;
	}
}

//******************************************************************************
//	End of file.
//******************************************************************************