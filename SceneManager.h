//*****************************************************************************
//  SceneManager.h
//  2016-12-20
//  Irene Gersenowies
//*****************************************************************************

#ifndef __SCENE_MNG__
#define __SCENE_MNG__

//=======================================================================//
//		�C���N���[�h
//=======================================================================//
# include "GameObjectsList.h"
# include "D3DClass.h"
# include "CameraClass.h"

//=======================================================================//
//	�O���[�o���ϐ�
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
//	�N���X��		CSceneManager
//=======================================================================//
class CScene
{
public:

	enum SCENE_NAME				//�V�[����
	{
		SCENE_TITLE,			//�^�C�g���V�[��
		SCENE_STAGESELECT,		//�X�e�[�W�Z���N�g
		SCENE_GAME,				//�Q�[���V�[��
		SCENE_OVER,				//�Q�[���I�[�o�[�V�[��
		SCENE_CLEAR,			//�Q�[���N���A�V�[��

		SCENE_MAX				//�ő�V�[����
	};

public:
	static bool InitializeSceneManager(int screenWidth, int screenHeight, HWND hwnd);	//�V�[���Ǘ��҂̏������֐�
	static void Shutdown(void);
	void ShutdownSceneObjects(void);

	virtual bool Initialize  (void);			//�������֐�
	virtual void Input       (void);			//���͊֐�
	virtual bool Render      (void);			//�`��֐�
	virtual void Action      (void);			//�����֐�
	virtual void PostAction  (void);			//�㏈���֐�
	virtual bool LoadScene   (void) = 0;			//�V�[���̃I�u�W�F�N�g�����[�h����

	virtual CScene* ChangeScene(bool isChange)=0;
	static CScene* GetScene(SCENE_NAME sceneName);
	
	//SCENE_NAME GetSceneName(void) { return sceneName; };
	
protected :
	CScene(void) {};							//�R���X�g���N�^
	CScene(const CScene& other) {};
	~CScene(void) {};							//�f�X�g���N�^

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
