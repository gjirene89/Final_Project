//*****************************************************************************
//  SceneManager.h
//  2016-12-20
//  Irene Gersenowies
//*****************************************************************************

#ifndef __SCENE_MNG__
#define __SCENE_MNG__

//=======================================================================//
//		インクルード
//=======================================================================//
# include "GameObjectsList.h"
# include "D3DClass.h"
# include "CameraClass.h"

//=======================================================================//
//	グローバル変数
//=======================================================================//
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 1.0f;
const int SHADOW_MAP_WIDTH = 2048;
const int SHADOW_MAP_HEIGHT = 2048;
const float SHADOW_MAP_DEPTH = 5000.0f;
const float SHADOW_MAP_NEAR = 1.0f;

//=======================================================================//
//	クラス名		CSceneManager
//=======================================================================//
class CScene
{
public:

	enum SCENE_NAME				//シーン名
	{
		SCENE_TITLE,			//タイトルシーン
		SCENE_STAGESELECT,		//ステージセレクト
		SCENE_GAME,				//ゲームシーン
		SCENE_OVER,				//ゲームオーバーシーン
		SCENE_CLEAR,			//ゲームクリアシーン

		SCENE_MAX				//最大シーン数
	};

public:
	static bool InitializeSceneManager(int screenWidth, int screenHeight, HWND hwnd);	//シーン管理者の初期化関数
	static void Shutdown(void);
	void ShutdownSceneObjects(void);

	virtual bool Initialize  (void);			//初期化関数
	virtual void Input       (void);			//入力関数
	virtual bool Render      (void);			//描画関数
	virtual void Action      (void);			//処理関数
	virtual void PostAction  (void);			//後処理関数
	virtual bool LoadScene   (void) = 0;			//シーンのオブジェクトをロードする

	virtual CScene* ChangeScene(bool isChange)=0;
	static CScene* GetScene(SCENE_NAME sceneName);
	
	//SCENE_NAME GetSceneName(void) { return sceneName; };
	
protected :
	CScene(void) {};							//コンストラクタ
	CScene(const CScene& other) {};
	~CScene(void) {};							//デストラクタ

	SCENE_NAME sceneName;
	CCamera* m_Camera;
	
	CGameObjectBase* objArray;

	static CDirect3D* m_Direct3D;

private:

	static CScene* m_titleScene;
	static CScene* m_gameScene;
	static CScene* m_gameClearScene;

	//static bool isStageClear;
};


#endif

//******************************************************************************
//	End of file.
//******************************************************************************
