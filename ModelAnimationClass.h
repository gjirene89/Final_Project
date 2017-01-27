#pragma once

# include "ModelClass.h"

class CModelAnimation
{
public:
	CModelAnimation(void);
	CModelAnimation(const CModelAnimation& other);
	~CModelAnimation(void);

	bool Initialize(ID3D11Device* device, CModel* startModel);
	void Shutdown();

	void SetCurrent(CModel* currModel);
	void SetTarget(CModel* targetModel, int endTime);
	void InterpolateModels();
	ID3D11Buffer* GetVertexBuffer(ID3D11DeviceContext* deviceContext);
	void UpdateBuffer(ID3D11DeviceContext* deviceContext);

private:
	bool InitializeBuffer(ID3D11Device* device);
	void ShutdownBuffer();

private:
	
	//int m_startTime;
	int m_endTime;
	int m_currTime;

	int m_vertexCnt;

	CModel::ModelType* m_startModel;
	CModel::ModelType* m_currModel;
	CModel::ModelType* m_targetModel;

	ID3D11Buffer* m_vertexBuffer;
};