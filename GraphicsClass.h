//************************************************************************//
//	graphicsClass.h
//	2016-11-02
//	Irene Gersenowies
//************************************************************************//
#ifndef __GRAPHICSCLASS_H__
#define __GRAPHICSCLASS_H__

//=======================================================================//
//		インクルード
//=======================================================================//
#include "D3DClass.h"
#include "CameraClass.h"
//#include "TextClass.h"
//#include "ModelClass.h"//nclude "Player.h"
//#include "LightClass.h"
//#include "ShaderManagerClass.h"
//#include "RenderTextureClass.h"
//#include "OrthoWindowClass.h"

//=======================================================================//
//	グローバル変数
//=======================================================================//
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 1.0f;
const int SHADOW_MAP_WIDTH = 2048;
const int SHADOW_MAP_HEIGHT = 2048;
const int SHADOW_MAP_DEPTH = 5000.0f;
const int SHADOW_MAP_NEAR = 1.0f;

//=======================================================================//
//	クラス名		CGraphics
//=======================================================================//
class CGraphics
{
public:
	CGraphics(void);
	CGraphics(const CGraphics& other);
	~CGraphics(void);

	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
	void Shutdown(void);
	bool Frame(int FPS, int CPU, float PosX, float PosY, float PosZ);

private:
	bool Render(void);
	bool RenderSceneToTexture(void);
	bool RenderBlackWhiteTexture(void);
	bool RenderHorizontalBlurTexture(void);
	bool RenderVerticalBlurTexture(void);
	bool RenderUpSampleTexture(void);
	bool RenderDownSampleTexture(void);

private:
	CDirect3D*  m_Direct3D;
	CCamera*    m_Camera;
	/*
	CLight*     m_SunLight;

	CText*      m_TextFps;
	CText*      m_TextCPU;

	CModel*     m_Block;
	//CModel*	    m_Sack;
	CPlayer*    m_Player;
	CModel*     m_Hook;
	CModel*		m_Wall;

	CRenderTexture* m_RenderTexture, *m_BlackWhiteRenderTexture;
	CRenderTexture* m_DownSampleTexture, *m_UpSampleTexture;
	CRenderTexture* m_HorizontalBlurTexture, *m_VerticalBlurTexture;
	COrthoWindow* m_SmallWindow, *m_FullScreenWindow;

	CShaderManager* m_ShaderManager;
	*/
};

#endif

//******************************************************************************
//	End of file.
//******************************************************************************