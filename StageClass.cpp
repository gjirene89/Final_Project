//************************************************************************//
//	StageClass.cpp
//	2017-01-14
//	Irene Gersenowies
//************************************************************************//

//=============================================================================
//		インクルード
//=============================================================================
# include "StageClass.h"
//# include "CDirectxGraphics.h"

//=============================================================================
//	グローバル変数
//=============================================================================
CStage::STAGE CStage::currStage;						//現在のステージ
CBlock* CStage::stage[MAX_BLOCKS_H][MAX_BLOCKS_W];
int stageBase[MAX_BLOCKS_H][MAX_BLOCKS_W] =			//ステージブロック配列
{
	{ 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

CBlock* CStage::redBlock;
CBlock* CStage::invisibleBlock;
CBlock* CStage::greenBlock;

//==============================================================================
//!	@fn		CStage
//!	@brief	ステージのデストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CStage::CStage() : CGameObjectBase(GOBJ_NONE)
{
	//現在のステージ
	currStage = STAGE_1;
}


//==============================================================================
//!	@fn		~CStage
//!	@brief	ステージのデストラクタ
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
CStage::~CStage()
{
	//今は空
}

bool CStage::InitializeObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	bool result;
	//ブロックのインスタンスを作る
	if (redBlock == nullptr)
	{
		redBlock = new CBlock(CBlock::BLOCK_COLOR::BLOCK_RED);
		if (!redBlock)
		{
			return false;
		}

		result = redBlock->InitializeObject(device, deviceContext);
		if (!result)
		{
			return false;
		}
	}

	if (invisibleBlock == nullptr) {

		invisibleBlock = new CBlock(CBlock::BLOCK_COLOR::BLOCK_INVISIBLE);
		if (!invisibleBlock)
		{
			return false;
		}

		/*
		result = invisibleBlock->InitializeObject(device, deviceContext);
		if (!result)
		{
		return false;
		}
		*/
	}

	if (greenBlock == nullptr) {

		greenBlock = new CBlock(CBlock::BLOCK_COLOR::BLOCK_GREEN);
		if (!greenBlock)
		{
			return false;
		}

		result = greenBlock->InitializeObject(device, deviceContext);
		if (!result)
		{
			return false;
		}
	}

	return true;
}

void CStage::Shutdown()
{
	//インスタンスのメモリを解放する
	if (redBlock != nullptr)
	{
		redBlock->Shutdown();
		delete redBlock;
		redBlock = nullptr;
	}

	if (greenBlock != nullptr)
	{
		greenBlock->Shutdown();
		delete greenBlock;
		greenBlock = nullptr;
	}

	if (invisibleBlock != nullptr)
	{
		invisibleBlock->Shutdown();
		delete invisibleBlock;
		invisibleBlock = nullptr;
	}
}

//==============================================================================
//!	@fn		Init
//!	@brief	ステージの初期化
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CStage::Initialize(void)
{
	for (int block_h = 0; block_h < MAX_BLOCKS_H; block_h++)
		for (int block_w = 0; block_w < MAX_BLOCKS_W; block_w++)
		{
			switch (stageBase[block_h][block_w])
			{
			case CBlock::BLOCK_NONE:
				stage[block_h][block_w] = nullptr;
				break;
			case CBlock::BLOCK_RED:
				stage[block_h][block_w] = redBlock;
				break;
			case CBlock::BLOCK_GREEN:
				stage[block_h][block_w] = greenBlock;
				break;
			case CBlock::BLOCK_INVISIBLE:
				stage[block_h][block_w] = invisibleBlock;
				break;

			}
		}

}

//==============================================================================
//!	@fn		Render
//!	@brief	ステージの描画
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void  CStage::Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPosition, CLight* light)
{
	//ブロックを描画する
	for (int block_h = 0; block_h < MAX_BLOCKS_H; block_h++)
		for (int block_w = 0; block_w < MAX_BLOCKS_W; block_w++)
		{
			if (stage[block_h][block_w] == nullptr)	continue;

			float PosX, PosY;

			PosX = (int)(BLOCK_SIZE / 2.0f + block_w * BLOCK_SIZE);
			PosY = (int)((MAX_BLOCKS_H - 1 - block_h) * BLOCK_SIZE + BLOCK_SIZE / 2.0f);

			stage[block_h][block_w]->SetPosition(PosX, PosY, 0.0f);
			stage[block_h][block_w]->Render(deviceContext, worldMatrix, viewMatrix, projectionMatrix, cameraPosition, light);
		}
}


//==============================================================================
//!	@fn		Action
//!	@brief	ステージの処理関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CStage::Action(void)
{
	//今は空
}


//==============================================================================
//!	@fn		PostAction
//!	@brief	ステージの後処理関数
//!	@param	なし
//!	@retval	なし
//!	@note	
//==============================================================================
void CStage::PostAction(void)
{
	//今は空
}


//==============================================================================
//!	@fn		isThereBlock
//!	@brief	特定ところにブロックがあるかどうか
//!	@param	int	PosX		位置 X軸
//!	@param	int	PosY		位置 Y軸
//!	@retval bool			true :	ブロックがある　false : ブロックがない
//!	@note	
//==============================================================================
bool CStage::isThereBlock(float PosX, float PosY)
{

	//ワールド座標を配列単位に変える
	int x = PosX / BLOCK_SIZE;
	int y = PosY / BLOCK_SIZE;


	//上
	if (y >= MAX_BLOCKS_H)	return false;

	//範囲外だったらブラックがないを返す
	if (x >= MAX_BLOCKS_W || PosX < 0 || PosY < 0)
		return true;

	//ブロックがない場合
	if (stage[MAX_BLOCKS_H - y - 1][x] == nullptr)
		return false;

	return true;

}

void CStage::ClearBlock(int PosX, int PosY)
{
	int x = PosX / BLOCK_SIZE;
	int y = PosY / BLOCK_SIZE;

	if (x >= MAX_BLOCKS_W || x < 0 ||
		y >= MAX_BLOCKS_H || y < 0)
		return;

	if (stage[MAX_BLOCKS_H - y - 1][x] == nullptr)
		return;

	return;
}

void CStage::CleanNumbers(float* posX, float* posY)
{
	if (posX != nullptr) *posX = (int)(*posX / BLOCK_SIZE) * BLOCK_SIZE;
	if (posY != nullptr) *posY = (int)(*posY / BLOCK_SIZE) * BLOCK_SIZE;

}

//******************************************************************************
//	End of file.
//******************************************************************************