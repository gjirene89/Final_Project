//************************************************************************//
//	Main.cpp
//	2016-12-16
//	Irene Gersenowies
//************************************************************************//

# include "SystemClass.h"

//==============================================================================
//  �֐���		 WinMain	
//  ����			 �G���g���|�C���g
//------------------------------------------------------------------------------
//	����
//          HINSTANCE   hInstance        �C���X�^���X�n���h��
//          HINSTANCE   hPrevInstance  �@����NULL\
//          LPSTR       lpScmdline       �N�����̈���������
//	�@�@�@�@ int         iCmdshow         �E�C���h�E�\�����[�h
//	�߂�l
//          int         TRUE : �����I�� / FALSE : ���s�I��
//==============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpScmdline, int iCmdshow)
{
	CSystem* System;
	bool result;

	//SystemObject����
	System = new CSystem;
	if (!System)
	{
		return 0;
	}

	//SystemObject������
	result = System->Initialize();
	if (result)
	{
		System->Run();
	}

	//SystemObject�̍폜
	System->Shutdown();
	delete System;
	System = 0;
	
	return 0;
}