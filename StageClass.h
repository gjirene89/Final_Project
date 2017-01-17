//************************************************************************//
//	StageClass.h
//	2017-01-14
//	Irene Gersenowies
//************************************************************************//

#ifndef __STAGE_CLASS_H__
#define __STAGE_CLASS_H__

//=============================================================================
//		�C���N���[�h
//=============================================================================
# include "BlockClass.h"
//# include "C3DObject.h"
//# include "CDirectxGraphics.h"

//=============================================================================
//	�}�N���萔
//=============================================================================
# define MAX_BLOCKS_W	45
# define MAX_BLOCKS_H	10

//=============================================================================
//!	@class	CStage
//!	@brief �X�e�[�W�N���X
//=============================================================================
class CStage :  public CGameObjectBase
{
public:

	//�X�e�[�W�h�c
	enum STAGE
	{
		STAGE_1,		//�X�e�[�W�P

		STAGE_MAX		//�X�e�[�W�ő吔
	};
	
	CStage(void);			//�R���X�g���N�^
	CStage(const CStage& other) {};
	~CStage(void);			//�f�X�g���N�^

	bool InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Shutdown();

	void Initialize(void);		//�������֐�
	void Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix); //�`��֐�
	void Action(void);		//�����֐�
	void PostAction(void);	//�㏈���֐�

	static STAGE currStage;								//���݂̃X�e�[�W
	static bool isThereBlock(float PosX, float PosY);		//����Ƃ���Ƀu���b�N�����邩�ǂ�����߂�
	static void setCurrStage();							//���݃X�e�[�W���Z�b�g����֐�
	static void ClearBlock(int PosX, int PosY);			//�u���b�N���n�C���C�g����
	static void CleanNumbers(float* posX, float* posY);

private:
	static CBlock *redBlock;				//�ԃu���b�N�̃C���X�^���X
	static CBlock *invisibleBlock;			//�����Ȃ��ǂ̃C���X�^���X
	static CBlock *greenBlock;			//�΃u���b�N�̃C���X�^���X
	
	static CBlock *stage[MAX_BLOCKS_H][MAX_BLOCKS_W];	//�X�e�[�W�P

};

#endif