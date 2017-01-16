//************************************************************************//
//	Main.cpp
//	2016-12-16
//	Irene Gersenowies
//************************************************************************//

# include "SystemClass.h"

//==============================================================================
//  関数名		 WinMain	
//  説明			 エントリポイント
//------------------------------------------------------------------------------
//	引数
//          HINSTANCE   hInstance        インスタンスハンドル
//          HINSTANCE   hPrevInstance  　いつもNULL\
//          LPSTR       lpScmdline       起動時の引数文字列
//	　　　　 int         iCmdshow         ウインドウ表示モード
//	戻り値
//          int         TRUE : 成功終了 / FALSE : 失敗終了
//==============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpScmdline, int iCmdshow)
{
	CSystem* System;
	bool result;

	//SystemObject生成
	System = new CSystem;
	if (!System)
	{
		return 0;
	}

	//SystemObject初期化
	result = System->Initialize();
	if (result)
	{
		System->Run();
	}

	//SystemObjectの削除
	System->Shutdown();
	delete System;
	System = 0;
	
	return 0;
}